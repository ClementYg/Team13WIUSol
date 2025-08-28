#include <iostream>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

// Helper: simple beep for dramatic effect
void dramaticBeep(int freq = 400, int dur = 200) {
    Beep(freq, dur);
}

// ASCII hero stages (good → neutral → evil)
const string heroStages[3][4] = {
    { // stage 1: innocent hero
        "  O  ",
        " /|\\ ",
        " / \\ ",
        "Traumatised child"
    },
    { // stage 2: tempted
        "  O  ",
        " /|\\ ",
        " / \\  ",
        "Vengeful teen"
    },
    { // stage 3: dark/evil
        "  X  ",
        " /|\\ ",
        " / \\ ",
        "Evil villain"
    }
};

void clearScreenCutscene() {

    system("cls");

}

// Function to display one stage
void displayHeroStage(int stage) {
    clearScreenCutscene();
    cout << "\n";
    for (int i = 0; i < 4; ++i) {
        cout << "     " << heroStages[stage][i] << endl;
    }
    dramaticBeep(300 + stage * 100, 300);
    Sleep(1500);
}

// The cutscene function
void evilHeroCutscene() {
    clearScreenCutscene();
    cout << "The hero escapes into the forest...\n";
    Sleep(1500);

    cout << "Years pass...\n";
    Sleep(1500);

    // Show gradual transformation
    for (int stage = 0; stage < 3; ++stage) {
        displayHeroStage(stage);
    }

    cout << "\nPress SPACE to continue your journey...\n";
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') break;
        }
        Sleep(50);
    }
}
