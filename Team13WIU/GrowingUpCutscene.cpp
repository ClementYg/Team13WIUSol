#include <iostream>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <chrono>
using namespace std;

// Simple beep for dramatic effect
void dramaticBeep(int freq = 400, int dur = 200) {
    Beep(freq, dur);
}

void clearScreenCutscene() {
    system("cls");
}

// ===================== Stage ASCII Art (2x bigger) =====================

// Stage 1: Innocent Child (village background, 2x bigger)
const string stage1Frames[2][28] = {
{
"==========================================================================",
"                      ~~~~~~~~~~~~        ^^        ~~~~~~~~~~~~         ",
"                   ~~~~~~~~~~~~~~      //    \\\\    ~~~~~~~~~~~~~~        ",
"                ~~~~~~~~~~~~~~~~    //        \\\\   ~~~~~~~~~~~~~~~~       ",
"             ==============      //     O      \\\\      ==============    ",
"            ||           ||    //     /||\\\\     \\\\    ||           ||   ",
"            ||   Hut     ||   //       /  \\\\       \\\\ ||  Village  ||   ",
"            ||___________||                               ||___________|| ",
"                                                                            ",
"                 Innocent Child: 'Hurt Child'                               ",
"=========================================================================="
},
{
"==========================================================================",
"                      ~~~~~~~~~~~~        ^^        ~~~~~~~~~~~~         ",
"                   ~~~~~~~~~~~~~~      //    \\\\    ~~~~~~~~~~~~~~        ",
"                ~~~~~~~~~~~~~~~~    //   \\O/   \\\\   ~~~~~~~~~~~~~~~~      ",
"             ==============      //     /||\\\\     \\\\   ==============   ",
"            ||           ||    //       /  \\\\       \\\\||           ||  ",
"            ||   Hut     ||   //                 \\\\     ||  Village  ||    ",
"            ||___________||                               ||___________||  ",
"                                                                            ",
"                 Innocent Child: 'Hurt Child'                               ",
"=========================================================================="
}
};

// Stage 2: Vengeful Teenager (battlefield flames, 2x bigger)
const string stage2Frames[2][28] = {
{
"==========================================================================",
"       (    )      (      )      (    )      (      )      (    )         ",
"     *   ) (   *  (    ) *   (   ) *   (   ) *    (   ) *   (   )         ",
"    ////   ////   ////   ////   ////   ////   ////   ////   ////           ",
"   ||           O    Vengeful Teenager        O           ||                   ",
"   ||          /||\\                          /||\\         ||                 ",
"   ||          /  \\                          /  \\         ||                 ",
"    \\\\    //////   ////    ///////   ////   //////   ////                  ",
"          * Flames rage across the battlefield *                              ",
"=========================================================================="
},
{
"==========================================================================",
"       (  * )      (  * )      (  * )      (  * )      (  * )               ",
"     *     ) (   *    ) (   *   ) (    *    ) (   *    ) (                 ",
"    ////   ////   ////   ////   ////   ////   ////   ////   ////           ",
"   ||        O         Vengeful Teenager     O          ||                    ",
"   ||       /||\\                           /||\\        ||                    ",
"   ||       /  \\                           /  \\         ||                    ",
"    \\\\    //////   ////    ///////   ////   //////   ////                  ",
"          * Flames flicker on the battlefield *                               ",
"=========================================================================="
}
};

// Stage 3: Evil Villain (dark throne room, 2x bigger)
const string stage3Frames[2][28] = {
{
"==========================================================================",
"                             _______________                               ",
"                            |               |                              ",
"                            |     EVIL      |                              ",
"                            |    THRONE     |                              ",
"                    ________|_______________|_________________                 ",
"                   /           O    Evil Villain        O    \\                  ",
"                  /          /||\\                     /||\\    \\              ",
"                 /           /  \\                     /  \\     \\             ",
"                /_______________________________________________\\            ",
"               //                                             \\\\           ",
"=========================================================================="
},
{
"==========================================================================",
"                             _______________                               ",
"                            |               |                              ",
"                            |     EVIL      |                              ",
"                            |    THRONE     |                              ",
"                    ________|_______________|_________________                     ",
"                   /        O    Evil Villain       O        \\                 ",
"                  /       /||\\                     /||\\       \\              ",
"                 /        /  \\                     /  \\        \\             ",
"                /_______________________________________________\\            ",
"               //         (dark energy pulses)             \\\\            ",
"=========================================================================="
}
};

// ===================== Display function with animation =====================

void displayHeroStage(int stage) {
    clearScreenCutscene();

    const string(*frames)[28] = nullptr;
    switch (stage) {
    case 0: frames = stage1Frames; break;
    case 1: frames = stage2Frames; break;
    case 2: frames = stage3Frames; break;
    }

    // Animate between two frames a few times
    for (int cycle = 0; cycle < 6; ++cycle) {
        clearScreenCutscene();
        int frameIndex = cycle % 2;
        for (int i = 0; i < 28; ++i) {
            cout << frames[frameIndex][i] << endl;
        }
        dramaticBeep(300 + stage * 100, 100);
        Sleep(400);
    }
}

// ===================== Cutscene =====================

void evilHeroCutscene() {
    clearScreenCutscene();
    cout << "The hero begins his journey..." << endl;
    Sleep(1500);

    cout << "Years pass..." << endl;
    Sleep(1500);

    for (int stage = 0; stage < 3; ++stage) {
        displayHeroStage(stage);
    }

    cout << "\nPress SPACE to continue your journey..." << endl;
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == ' ') break;
        }
        Sleep(50);
    }
}


