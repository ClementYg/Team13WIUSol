#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>

using namespace std;

// Scene ASCII art (town burning )
const char* fullScene[] = {
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
R"(                                ~~~~~~~~~~~~~~~                                        )",
R"(                                ||  ||  ||  ||                                         )",
R"(                                ||  ||  ||  ||                                         )",
R"(                                ||  ||  ||  ||                                         )",
R"(                                    FOREST                                                )"
};

const int sceneLines = sizeof(fullScene) / sizeof(fullScene[0]);

// Hero running frames
const string heroRunFrames[4][3] = {
    { "  O  ", " /|\\ ", " / \\ " },
    { "  O  ", " /|\\ ", "  /\\ " },
    { "  O  ", " /|\\ ", " /   " },
    { "  O  ", " /|\\ ", "  \\  " }
};

const int heroHeight = 3;
const int heroStartLine = 16; // adjust to match scene

// Print scene with hero
void printSceneWithHero(int x, int frame) {
    system("cls");
    for (int i = 0; i < sceneLines; i++) {
        if (i >= heroStartLine && i < heroStartLine + heroHeight) {
            cout << string(x, ' ') << heroRunFrames[frame][i - heroStartLine] << endl;
        }
        else {
            cout << fullScene[i] << endl;
        }
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
        Beep(500, 50);
        Sleep(100);
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