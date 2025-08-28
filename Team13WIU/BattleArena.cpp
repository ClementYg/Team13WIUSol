

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include <thread>
#include <algorithm>
#include <cmath>
#include "Player.h"

using namespace std;

// ---------------- console helpers ----------------
static void moveCursor(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
static void setColor(WORD atr) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), atr); }

// Draw a full buffer to console (no colors)
static void drawBuffer(const vector<string>& buf) {
    moveCursor(0, 0);
    for (const auto& line : buf) {
        cout << line << '\n';
    }
}

// Write a single char with color at coordinates
static void putCharColor(int x, int y, char ch, WORD color) {
    COORD c = { (SHORT)x, (SHORT)y };
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h, c);
    SetConsoleTextAttribute(h, color);
    cout << ch;
    SetConsoleTextAttribute(h, 7); // reset
}

// ---------------- arena + visuals ----------------
static const int ARENA_W = 80;
static const int ARENA_H = 24;

static vector<string> initArenaBase() {
    vector<string> buf(ARENA_H, string(ARENA_W, ' '));
    // crowd top (gladiator stands)
    for (int r = 0; r < 3; ++r) buf[r] = string(ARENA_W, '^');
    // arena floor
    buf[ARENA_H - 4] = string(ARENA_W, '=');
    buf[ARENA_H - 3] = string(ARENA_W, '=');
    // put rocks and scattered stones
    for (int x = 8; x < ARENA_W - 8; x += 12) {
        int y = ARENA_H - 6 - (x % 2);
        if (y >= 3 && y < ARENA_H - 4) {
            buf[y].replace(x, 3, "(_)");
            if (y - 1 >= 0) buf[y - 1].replace(x + 1, 1, "'");
        }
    }
    // gladiator pit marks
    buf[ARENA_H - 6].replace(2, 6, "[====]");
    buf[ARENA_H - 6].replace(ARENA_W - 8, 6, "[====]");
    return buf;
}

// ---------------- sprites ---------------- 
// simple 3x3 hero sprite facing right
static vector<string> HERO_R = { "  O", " /|\\", " / \\" };
// mirrored left
static vector<string> HERO_L = { "O  ", "/|\\ ", "/ \\" };
// up / down small frames
static vector<string> HERO_U = { " O ", "/|\\", " | " };
static vector<string> HERO_D = { " | ", "\\|/", " O " };

// villain sprite (always same orientation; we draw enemy first so player overlaps)
static vector<string> VILLAIN = { " (V) ", " /|\\ ", " / \\ " };
static vector<string> VILLAIN_HURT = { " (X) ", " /|\\ ", " / \\ " };
static vector<string> VILLAIN_LUNGE = { " \\V/ ", " -|- ", " / \\ " };

// ---------------- sword attack sprites ----------------
// Right sword attack (3-frame swing)
static vector<vector<string>> HERO_R_ATTACK = {
    { "  O ", " /|\\", " / \\" }, // start swing
    { "  O ", " /|\\", " / \\" }, // mid swing
    { "  O ", " /|\\>", " / \\" }  // follow-through
};

// Left sword attack (mirror)
static vector<vector<string>> HERO_L_ATTACK = {
    { " \O  ", "/|\\ ", "/ \\" },
    { " O  ", "/|\\ ", "/ \\" },
    { " O ", "<|\\ ", "/ \\" }
};


// ---------------- stamping helpers ----------------
static void stamp(vector<string>& buf, const vector<string>& sprite, int x, int y) {
    for (int r = 0; r < (int)sprite.size(); ++r) {
        int by = y + r;
        if (by < 0 || by >= (int)buf.size()) continue;
        for (int c = 0; c < (int)sprite[r].size(); ++c) {
            int bx = x + c;
            if (bx < 0 || bx >= (int)buf[by].size()) continue;
            char ch = sprite[r][c];
            if (ch != ' ') buf[by][bx] = ch;
        }
    }
}

// stamp a 3-char wide slash effect (for visual)
static void stampEffect(vector<string>& buf, int x, int y, int dx, int dy, char mark) {
    for (int s = 1; s <= 3; ++s) {
        int px = x + dx * s;
        int py = y + dy * s;
        if (py >= 0 && py < (int)buf.size() && px >= 0 && px < (int)buf[py].size())
            buf[py][px] = mark;
    }
}

// ---------------- UI bars ----------------
static void printHealthBar(const string& label, int hp, int maxHP, int y) {
    moveCursor(0, y);
    string bar = "";
    for (int i = 0; i < hp; ++i) bar += '#';
    for (int i = hp; i < maxHP; ++i) bar += ' ';
    cout << label << " HP: [" << bar << "] " << hp << "/" << maxHP << "   ";
}

static void printManaBar(int mana, int maxMana, int y) {
    moveCursor(0, y);
    const int len = 20;
    int filled = (int)round((double)mana / maxMana * len);
    filled = max(0, min(len, filled));
    cout << "Mana: [";
    for (int i = 0; i < filled; ++i) cout << '|';
    for (int i = filled; i < len; ++i) cout << ' ';
    cout << "] " << mana << "/" << maxMana << "   ";
}

// ---------------- projectile ----------------
struct Projectile {
    int x, y;
    int dx;
    int dmg;
    char glyph;
    bool active;
    WORD color;
};

// ---------------- helpers for keyboard (handle arrows) ----------------
static int getKeyNonBlocking() {
    if (!_kbhit()) return -1;
    int c = _getch();
    if (c == 0 || c == 224) { // special
        int spec = _getch();
        return 1000 + spec; // offset special codes
    }
    return c;
}

// ---------------- main battle logic ----------------
//ADDED PLAYER REF TO SET UNIVERSAL HP AND MANA
void battleArenaScene(Player* playerRef) {
    playerRef->setPlayerX(10), playerRef->setPlayerY(ARENA_H - 7);
    int playerX = playerRef->getPlayerX();
    int playerY = playerRef->getPlayerY(); 
    int villainX = ARENA_W - 18, villainY = ARENA_H - 7; //this one not universal as its unique to enemy

    int MAX_HP = playerRef->getMaxHP();
    int MAX_MANA = playerRef->getMaxMana(); 

    int villainHP = 50;

    int playerMana = playerRef->getPlayerMana();
    const int MANA_COST_WATER = 25;

    // facing: 0=right,1=left,2=up,3=down
    int facing = 0;

    auto lastFrame = chrono::steady_clock::now();
    auto lastVillainMove = lastFrame;
    auto lastVillainLunge = lastFrame;
    auto lastVillainAttack = lastFrame;

    vector<Projectile> projectiles;
    const int FRAME_MS = 80;

    bool running = true;
    system("cls");

    while (running && playerRef->getPlayerHP() > 0 && villainHP > 0) {
        // timing
        auto now = chrono::steady_clock::now();
        double delta = chrono::duration<double>(now - lastFrame).count();
        lastFrame = now;

        // input (non-blocking)
        int key = getKeyNonBlocking();
        if (key != -1) {
            if (key >= 1000) {
                int spec = key - 1000;
                // arrow keys codes: 72=up, 75=left, 77=right, 80=down
                if (spec == 75) facing = 1;     // left
                else if (spec == 77) facing = 0; // right
                else if (spec == 72) facing = 2; // up
                else if (spec == 80) facing = 3; // down
            }
            else {
                char ch = (char)key;
                ch = tolower(ch);
                if (ch == 'w' && playerY > 3) playerY--;
                else if (ch == 's' && playerY < ARENA_H - 5) playerY++;
                else if (ch == 'a' && playerX > 0) playerX--;
                else if (ch == 'd' && playerX < ARENA_W - 4) playerX++;
                else if (ch == 'q') { running = false; break; }

                // ATTACKS:
                // H = Slash (3-tile wide in facing direction)
                else if (ch == 'h') {
                    // visual slash on buffer and damage if in range
                    vector<string> base = initArenaBase();
                    stamp(base, VILLAIN, villainX, villainY);
                    stamp(base, VILLAIN, villainX, villainY); // draw enemy so effect is visible beneath
                    // compute dx, dy for facing
                    int dx = 0, dy = 0;
                    if (facing == 0) dx = 1;
                    else if (facing == 1) dx = -1;
                    else if (facing == 2) dy = -1;
                    else dy = 1;
                    // stamp effect (3-wide) and check damage: slash hits a 3-tile wide arc orthogonal
                    // We'll mark three tiles forward and two adjacent (to look wide)
                    stampEffect(base, playerX, playerY, dx, dy, '*');
                    // render quick frames
                    drawBuffer(base);

                    printHealthBar("Player", playerRef->getPlayerHP(), MAX_HP, ARENA_H);
                    printHealthBar("Brave Knight", villainHP, MAX_HP, ARENA_H + 1);
                    printManaBar(playerRef->getPlayerMana(), MAX_MANA, ARENA_H + 2);

                    moveCursor(0, ARENA_H + 4); cout << "Slash (H) executed!";
                    Beep(700, 100);
                    this_thread::sleep_for(chrono::milliseconds(150));

                    // damage logic: if villain within 3 tiles in facing direction OR within lateral tiles, take 1 HP
                    bool hit = false;
                    for (int s = 1; s <= 3 && !hit; s++) {
                        int tx = playerX + dx * s;
                        int ty = playerY + dy * s;
                        // also check adjacent sideways to make it 3-wide
                        for (int side = -1; side <= 1; ++side) {
                            int sx = tx + (dy != 0 ? side : 0); // if vertical, shift x sideways
                            int sy = ty + (dx != 0 ? side : 0); // if horizontal, shift y
                            if (abs(sx - villainX) <= 1 && abs(sy - villainY) <= 1) { hit = true; break; }
                        }
                    }
                    if (hit && villainHP > 0) { villainHP = max(0, villainHP - playerRef->getWeaponDmg()); moveCursor(0, ARENA_H + 4); cout << "Slash hit!           "; Beep(800, 120); }
                    else { moveCursor(0, ARENA_H + 4); cout << "Slash missed!        "; }
                    this_thread::sleep_for(chrono::milliseconds(180));
                }

                // J = Lunge (player dashes up to 3 tiles forward with animation) 
                else if (ch == 'j') {
                    int dx = 0, dy = 0;
                    if (facing == 0) dx = 1;
                    else if (facing == 1) dx = -1;
                    else if (facing == 2) dy = -1;
                    else dy = 1;
                    // animate 3 small steps
                    for (int step = 0; step < 3; ++step) {
                        int nx = playerX + dx;
                        int ny = playerY + dy;
                        // bounds
                        if (nx < 0 || nx > ARENA_W - 4 || ny < 3 || ny > ARENA_H - 5) break;
                        // move
                        playerX = nx; playerY = ny;
                        // draw quick
                        vector<string> frame = initArenaBase();
                        stamp(frame, VILLAIN, villainX, villainY);
                        // player facing drawn last
                        if (facing == 0) stamp(frame, HERO_R, playerX, playerY);
                        else if (facing == 1) stamp(frame, HERO_L, playerX, playerY);
                        else if (facing == 2) stamp(frame, HERO_U, playerX, playerY);
                        else stamp(frame, HERO_D, playerX, playerY);
                        drawBuffer(frame);
                        printHealthBar("Player", playerRef->getPlayerHP(), MAX_HP, ARENA_H);
                        printHealthBar("Brave Knight", villainHP, MAX_HP, ARENA_H + 1);
                        printManaBar(playerRef->getPlayerMana(), MAX_MANA, ARENA_H + 2);

                        moveCursor(0, ARENA_H + 4); cout << "Lunging... ";
                        Beep(650, 80);
                        this_thread::sleep_for(chrono::milliseconds(100));
                        // if landed close to villain, damage
                        if (abs(playerX - villainX) <= 1 && abs(playerY - villainY) <= 1 && villainHP > 0) {
                            villainHP = max(0, villainHP - playerRef->getWeaponDmg());
                            moveCursor(0, ARENA_H + 4); cout << "Lunge hit! ";
                            Beep(900, 120);
                            break;
                        }
                    }
                }

                //Sword Hit

                else if (ch == 'g') {
                    auto& frames = (facing == 0 ? HERO_R_ATTACK : HERO_L_ATTACK);
                    for (auto& f : frames) {
                        vector<string> buf = initArenaBase();
                        stamp(buf, VILLAIN, villainX, villainY);      // draw villain first
                        stamp(buf, f, playerX, playerY);             // draw swinging hero
                        drawBuffer(buf);

                        printHealthBar("Player", playerRef->getPlayerHP(), MAX_HP, ARENA_H);
                        printHealthBar("Brave Knight", villainHP, MAX_HP, ARENA_H + 1);
                        printManaBar(playerRef->getPlayerMana(), MAX_MANA, ARENA_H + 2);
                        moveCursor(0, ARENA_H + 4);
                        cout << "Slash attack!       ";
                        Beep(700, 100);
                        this_thread::sleep_for(chrono::milliseconds(120));
                    }

                    // Damage detection (same logic as before)
                    bool hit = false;
                    int dx = (facing == 0 ? 1 : (facing == 1 ? -1 : 0));
                    int dy = (facing == 2 ? -1 : (facing == 3 ? 1 : 0));
                    for (int s = 1; s <= 3 && !hit; ++s) {
                        int tx = playerX + dx * s;
                        int ty = playerY + dy * s;
                        for (int side = -1; side <= 1; ++side) {
                            int sx = tx + (dy != 0 ? side : 0);
                            int sy = ty + (dx != 0 ? side : 0);
                            if (abs(sx - villainX) <= 1 && abs(sy - villainY) <= 1) hit = true;
                        }
                    }
                    if (hit) { villainHP = max(0, villainHP - playerRef->getWeaponDmg()); moveCursor(0, ARENA_H + 4); cout << "Slash hit!       "; Beep(800, 120); }
                }



                // K = water magic (projectile). Blue color
                else if (ch == 'k') {
                    if (playerRef->getPlayerMana() >= MANA_COST_WATER) {
                        playerRef->addPlayerMana(MANA_COST_WATER * -1);
                        int projDx = 0, projDy = 0;
                        if (facing == 0) projDx = 2;
                        else if (facing == 1) projDx = -2;
                        else if (facing == 2) projDy = -1;
                        else projDy = 1;
                        Projectile p;
                        p.x = playerX + (projDx > 0 ? 4 : (projDx < 0 ? -1 : 0));
                        p.y = playerY;
                        p.dx = (projDx != 0 ? (projDx > 0 ? 2 : -2) : (projDy != 0 ? (projDy > 0 ? 0 : 0) : 2));
                        // if vertical, dx=0 and dy set via glyph movement — but for simplicity we'll use dx only left/right,
                        // for up/down we simulate vertical by moving y each frame:
                        p.dmg = 10;
                        p.glyph = '~';
                        p.active = true;
                        p.color = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                        projectiles.push_back(p);
                        moveCursor(0, ARENA_H + 4); cout << "Cast water!           ";
                        Beep(550, 90);
                    }
                    else {
                        moveCursor(0, ARENA_H + 4); cout << "Not enough mana!      ";
                        Beep(300, 120);
                    }
                }
            }
        } // end input

        // enemy AI: follow in 4 directions (simple)
        if (chrono::duration_cast<chrono::milliseconds>(now - lastVillainMove).count() >= 160) {
            if (villainX < playerX) villainX++;
            else if (villainX > playerX) villainX--;
            if (villainY < playerY) villainY++;
            else if (villainY > playerY) villainY--;
            lastVillainMove = now;
        }

        // enemy lunge occasionally if near but not too near
        if (chrono::duration_cast<chrono::milliseconds>(now - lastVillainLunge).count() >= 1800) {
            int dist = abs(villainX - playerX) + abs(villainY - playerY);
            if (dist <= 8 && dist >= 3) {
                // lunge 3 steps toward player with animation
                for (int s = 0; s < 3; s++) {
                    if (villainX < playerX) villainX++;
                    else if (villainX > playerX) villainX--;
                    if (villainY < playerY) villainY++;
                    else if (villainY > playerY) villainY--;
                    // draw small frame so we can see lunge
                    auto f = initArenaBase();
                    stamp(f, VILLAIN_LUNGE, villainX, villainY);
                    if (facing == 0) stamp(f, HERO_R, playerX, playerY);
                    else if (facing == 1) stamp(f, HERO_L, playerX, playerY);
                    else if (facing == 2) stamp(f, HERO_U, playerX, playerY);
                    else stamp(f, HERO_D, playerX, playerY);
                    drawBuffer(f);

                    printHealthBar("Player", playerRef->getPlayerHP(), MAX_HP, ARENA_H);
                    printHealthBar("Brave Knight", villainHP, MAX_HP, ARENA_H + 1);
                    printManaBar(playerRef->getPlayerMana(), MAX_MANA, ARENA_H + 2);

                    Beep(400, 80);
                    this_thread::sleep_for(chrono::milliseconds(80));
                    // if overlap: damage AKA CHECK COLLISION
                    if (abs(villainX - playerX) <= 1 && abs(villainY - playerY) <= 1 && villainHP > 0) {
                        playerRef->addPlayerHP(-10); //reduce universal health 
                        moveCursor(0, ARENA_H + 4); cout << "Brave Knight lunges - You took 1 dmg! ";
                        Beep(450, 120);
                        this_thread::sleep_for(chrono::milliseconds(180));
                    }
                }
                lastVillainLunge = now;
            }
        }

        // update projectiles (move rightwards only for simplicity)
        for (auto& p : projectiles) {
            if (!p.active) continue;
            p.x += p.dx > 0 ? 1 : (p.dx < 0 ? -1 : 0);
            // collision
            if (abs(p.x - villainX) <= 1 && abs(p.y - villainY) <= 1 && villainHP > 0) {
                villainHP = max(0, villainHP - p.dmg);
                p.active = false;
                Beep(800, 100);
            }
            if (p.x < 0 || p.x >= ARENA_W - 1) p.active = false;
        }
        // erase inactive
        projectiles.erase(remove_if(projectiles.begin(), projectiles.end(), [](const Projectile& pp) { return !pp.active; }), projectiles.end());

        // villain attack when close (cooldown)
        if (abs(playerX - villainX) <= 1 && abs(playerY - villainY) <= 1 && villainHP > 0) {
            auto nowAtk = chrono::steady_clock::now();
            if (chrono::duration_cast<chrono::milliseconds>(nowAtk - lastVillainAttack).count() >= 900) {
                playerRef->addPlayerHP(-10);
                lastVillainAttack = nowAtk;
                moveCursor(0, ARENA_H + 4); cout << "Brave Knight hits you! -10 HP    ";
                Beep(450, 100);
            }
        }

        // BUILD frame with draw order: arena -> crowd/rocks -> villain -> projectiles (colored) -> player -> UI
        vector<string> frame = initArenaBase();

        // draw crowd markers (already in arena top)
        // draw villain first
        if (villainHP > 0) stamp(frame, VILLAIN, villainX, villainY);
        else stamp(frame, VILLAIN_HURT, villainX, villainY);

        // overlay non-colored projectiles into frame as glyphs (we will color when drawing)
        for (auto& p : projectiles) {
            if (!p.active) continue;
            int px = p.x;
            int py = p.y;
            if (py >= 0 && py < (int)frame.size() && px >= 0 && px < (int)frame[py].size()) {
                frame[py][px] = p.glyph;
            }
        }

        // draw player last so he appears on top
        if (facing == 0) stamp(frame, HERO_R, playerX, playerY);
        else if (facing == 1) stamp(frame, HERO_L, playerX, playerY);
        else if (facing == 2) stamp(frame, HERO_U, playerX, playerY);
        else stamp(frame, HERO_D, playerX, playerY);

        // draw base
        drawBuffer(frame);

        // now color projectiles (blue) by printing them individually with color to preserve player overwrite
        for (auto& p : projectiles) {
            if (!p.active) continue;
            if (p.x >= 0 && p.x < ARENA_W && p.y >= 0 && p.y < ARENA_H) {
                putCharColor(p.x, p.y, p.glyph, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
        }

        // UI
        printHealthBar("Player", playerRef->getPlayerHP(), MAX_HP, ARENA_H);
        printHealthBar("Brave Knight", villainHP, MAX_HP, ARENA_H + 1);
        printManaBar(playerRef->getPlayerMana(), MAX_MANA, ARENA_H + 2);
        moveCursor(0, ARENA_H + 5);
        cout << "WASD=move  Arrows=face  G=SwordHit  H=Slash  J=Lunge  K=Water  Q=Quit            ";

        this_thread::sleep_for(chrono::milliseconds(FRAME_MS));
    } // end loop

    moveCursor(0, ARENA_H + 6);
    if (playerRef->getPlayerHP() <= 0) cout << "\nYou have been defeated!\n";
    else if (villainHP <= 0) {
        std::cout << "Do you wish to spare this enemy? [Y/N]\n";
        bool validChoice = false;
        while (!validChoice) {
            char finalChoice = _getch();
            if (finalChoice == 'Y' || finalChoice == 'y') {
                playerRef->setMorale(playerRef->getMorale() + 20);
                validChoice = true;
            }
            else if (finalChoice == 'N' || finalChoice == 'n') { playerRef->setMorale(playerRef->getMorale() - 20); validChoice = true; }
        }
    }
    else cout << "\nExited.\n";
}

