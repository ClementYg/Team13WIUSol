#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Base scene (burning town, static parts)
const char* baseScene[] = {
R"(                                  |>>>                      |>>>                            )",
R"(                                  |                         |                              )",
R"(                              _  _|_  _                 _  _|_  _                          )",
R"(                             |;|_|;|_|;|               |;|_|;|_|;|                         )",
R"(                             \\.    .  /               \\.    .  /                         )",
R"(                              \\:  .  /                 \\:  .  /                          )",
R"(                               ||:   |                   ||:   |                           )",
R"(                               ||:.  |                   ||:.  |                           )",
R"(                            __ ||_   | __             __ ||_   | __                         )",
R"(                           (  )| |  (  )|           (  )| |  (  )|                          )",
R"(                           | ||_| |_|| |           | ||_| |_|| |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                    /   | |  | |  | |  |           | |  | |  | |  | |   \                 )",
R"(                   /____|_|__|_|__|_|__\         /_|__|_|__|_|__|_|____\                )",
R"(                                                                                      )",
R"(~~~~~~~~~~~~~~~~~~~~~~   Burning town square chaos    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)",
R"(                                                                                      )",
R"(                                    FOREST                                           )"
};

const int baseSceneLines = sizeof(baseScene) / sizeof(baseScene[0]);

// Hero running frames
const string heroRunFrames[4][3] = {
    { "  O  ", " /|\\ ", " / \\ " },
    { "  O  ", " /|\\ ", "  /\\ " },
    { "  O  ", " /|\\ ", " /   " },
    { "  O  ", " /|\\ ", "  \\  " }
};

const int heroHeight = 3;
const int heroStartLine = 12; // adjust to match ground level

// Random flames (for animation)
vector<string> flameVariants = { "^^^", "~~~", "***", "'''" };

// Random screams/shouts
vector<string> chaosCries = {
    "HELP US!!",
    "Nooo!!",
    "The soldiers are here!",
    "Please spare us!",
    "Fire!!",
    "Get out!!"
};

// Draw scene with flames + hero
void printSceneWithHero(int x, int frame) {
    system("cls");

    for (int i = 0; i < baseSceneLines; i++) {
        // Hero line override
        if (i >= heroStartLine && i < heroStartLine + heroHeight) {
            cout << string(x, ' ') << heroRunFrames[frame][i - heroStartLine] << endl;
        }
        else {
            string line = baseScene[i];

            // Insert random flames in upper rows
            if (i >= 2 && i <= 8 && rand() % 4 == 0) {
                int pos = 30 + rand() % 20;
                if (pos < (int)line.size() - 3)
                    line.replace(pos, 3, flameVariants[rand() % flameVariants.size()]);
            }

            cout << line << endl;
        }
    }

    // Random begging or soldier shouts (sometimes shows under the scene)
    if (rand() % 3 == 0) {
        cout << chaosCries[rand() % chaosCries.size()] << endl;
    }
}

// Simple intro beep
void introBeeps() {
    int notes[] = { 523, 587, 659, 698, 783 };
    int durations[] = { 150, 150, 150, 150, 300 };
    for (int i = 0; i < 5; ++i) {
        Beep(notes[i], durations[i]);
        Sleep(50);
    }
}

// Animate hero running
void animateHeroRun() {
    int heroX = 5;
    int maxX = 50;
    int frame = 0;
    while (heroX <= maxX) {
        printSceneWithHero(heroX, frame);
        Beep(500, 40); // footstep
        Sleep(120);
        heroX += 2;
        frame = (frame + 1) % 4;
    }

    system("cls");
    cout << string(50, '*') << "\n";
    cout << "*           The Hero has escaped into the forest!           *\n";
    cout << string(50, '*') << "\n\n";
}

// Main function to play scene
void playTownsquareBurning() {
    srand((unsigned)time(0));
    introBeeps();
    printSceneWithHero(5, 0);
    cout << "\nPress 'R' to run into the forest...\n";

    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (tolower(ch) == 'r') {
                animateHeroRun();
                break; // exit scene after running
            }
        }
        Sleep(50);
    }
}

