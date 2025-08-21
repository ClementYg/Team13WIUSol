#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

// Scene ASCII art lines (castle, town, forest)
const char* fullScene[] = {
R"(                                  |>>>                      |>>>                            )",
R"(                                  |                         |                              )",
R"(                              _  _|_  _                 _  _|_  _                          )",
R"(                             |;|_|;|_|;|               |;|_|;|_|;|                         )",
R"(                             \\.    .  /               \\.    .  /                         )",
R"(                              \\:  .  /                 \\:  .  /                          )",
R"(                               ||:   |                   ||:   |                           )",
R"(                               ||:.  |                   ||:.  |                           )",
R"(                               ||:  .|                   ||:  .|                           )",
R"(                               ||:   |                   ||:   |                           )",
R"(                               ||: , |                   ||: , |                           )",
R"(                               ||:   |                   ||:   |                           )",
R"(                               ||: . |                   ||: . |                           )",
R"(                            __ ||_   | __             __ ||_   | __                         )",
R"(                           (  )| |  (  )|           (  )| |  (  )|                          )",
R"(                           | ||_| |_|| |           | ||_| |_|| |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                           | |  | |  | |           | |  | |  | |                          )",
R"(                      __   | |  | |  | |           | |  | |  | |   __                     )",
R"(                     (  )  | |  | |  | |           | |  | |  | |  (  )                    )",
R"(                     | ||_| |  | |  | |           | |  | |  | |_|| |                    )",
R"(                     | |  | |  | |  | |           | |  | |  | |  | |                    )",
R"(                     | |  | |  | |  | |           | |  | |  | |  | |                    )",
R"(                     | |  | |  | |  | |           | |  | |  | |  | |                    )",
R"(                     | |  | |  | |  | |           | |  | |  | |  | |                    )",
R"(                     | |  | |  | |  | |           | |  | |  | |  | |                    )",
R"(                     | |  | |  | |  | |           | |  | |  | |  | |                    )",
R"(                     | |  | |  | |  | |           | |  | |  | |  | |                    )",
R"(                     | |  | |  | |  | |           | |  | |  | |  | |                    )",
R"(                     | |  | |  | |  | |           | |  | |  | |  | |                    )",
R"(                    /   | |  | |  | |  |           | |  | |  | |  | |   \                 )",
R"(                   /____|_|__|_|__|_|__\         /_|__|_|__|_|__|_|____\                )",
R"(                                                                                      )",
R"(          _O/        _O/           _O/       _O/        _O/            _O/            )",
R"(         <|          <|            <|        <|         <|             <|             )",
R"(         / \        / \           / \       / \        / \            / \             )",
R"(                                                                                      )",
R"(    (X_x)    (o_O)    (x_x)     (O_O)    (X_x)    (o_O)     (x_x)     (O_O)            )",
R"(    /|\\     /|\\     /|\\      /|\\     /|\\     /|\\      /|\\      /|\\              )",
R"(    / \      / \      / \       / \      / \      / \       / \       / \              )",
R"(                                                                                      )",
R"(~~~~~~~~~~~~~~~~~~~~~~   Burning town square chaos    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)",
R"(                                                                                      )",
R"(                         ^   ^   ^   ^   ^   ^   ^   ^                                 )",
R"(                        /|\ /|\ /|\ /|\ /|\ /|\ /|\ /|\                                )",
R"(                       /_|_\|_|_\|_|_\|_|_\|_|_\|_|_\|_|_\                              )",
R"(                        ||   ||   ||   ||   ||   ||   ||                                )",
R"(                                                                                      )",
R"(                                                                                      )",
R"(                                ~~~~~~~~~~~~~~~                                        )",
R"(                                ||  ||  ||  ||                                         )",
R"(                                ||  ||  ||  ||                                         )",
R"(                                ||  ||  ||  ||                                         )",
R"(                               FOREST                                                )"
};

// Number of lines in the scene
const int sceneLines = sizeof(fullScene) / sizeof(fullScene[0]);

// Hero ASCII art running frames (simple running animation)
const string heroRunFrames[4][3] = {
    {
        "  O  ",
        " /|\\ ",
        " / \\ "
    },
    {
        "  O  ",
        " /|\\ ",
        "  /\\ "
    },
    {
        "  O  ",
        " /|\\ ",
        " /   "
    },
    {
        "  O  ",
        " /|\\ ",
        "  \\  "
    }
};

const int heroHeight = 3;
const int heroStartLine = 38;

// Print scene with hero at horizontal position x and animation frame f
void printSceneWithHero(int x, int frame) {
    system("cls");
    for (int i = 0; i < sceneLines; i++) {
        if (i >= heroStartLine && i < heroStartLine + heroHeight) {
            // Print spaces before hero for horizontal positioning,
            // then print hero frame characters
            cout << string(x, ' ') << heroRunFrames[frame][i - heroStartLine] << endl;
        }
        else {
            cout << fullScene[i] << endl;
        }
    }
    cout << "\nPress 'R' to run the hero to the forest.\n";
    cout << "Press 'C' to view the scene again.\n";
    cout << "Press 'Q' to quit.\n";
}

// Beep melody intro before game starts
void introBeeps() {
    int notes[] = { 523, 587, 659, 698, 783, 880, 987 }; // C4 D4 E4 F4 G4 A4 B4
    int durations[] = { 200, 200, 200, 200, 200, 200, 400 };

    cout << "Welcome to Burning Kingdom Escape!\n\n";

    for (int i = 0; i < 7; ++i) {
        Beep(notes[i], durations[i]);
        Sleep(50);
    }
}

void animateHeroRun() {
    int heroX = 5;          // starting horizontal position (near town)
    int maxX = 50;          // forest position on right side
    int frame = 0;
    while (heroX <= maxX) {
        printSceneWithHero(heroX, frame);

        // Footstep beep (500Hz, 50ms)
        Beep(500, 50);

        Sleep(100);
        heroX += 2;
        frame = (frame + 1) % 4;  // cycle run frames
    }

    // Clear screen and print full screen message
    system("cls");
    cout << string(50, '*') << "\n";
    cout << "*                  You reached the forest!              *\n";
    cout << string(50, '*') << "\n\n";
    cout << "Press 'C' to view the scene again or 'Q' to quit.\n";
}


int main() {
    introBeeps();

    cout << "Press 'C' to view the scene.\n";
    cout << "Press 'R' to run the hero to the forest.\n";
    cout << "Press 'Q' to quit.\n";

    bool running = true;

    while (running) {
        if (_kbhit()) {
            char ch = _getch();
            switch (tolower(ch)) {
            case 'c':
                printSceneWithHero(5, 0);
                break;
            case 'r':
                animateHeroRun();
                break;
            case 'q':
                running = false;
                break;
            }
        }
        Sleep(50);
    }

    cout << "Thanks for playing!\n";
    return 0;
}
