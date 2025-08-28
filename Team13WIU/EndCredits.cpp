#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

//  Full retro-style credits melody using Beep()
void play_credits_jingle() {
    int tempo = 200; // base duration (ms)

    // Simple melody (C5 scale upwards + return)
    Beep(523, tempo);   // C5
    Beep(587, tempo);   // D5
    Beep(659, tempo);   // E5
    Beep(698, tempo);   // F5
    Beep(783, tempo);   // G5
    Beep(880, tempo);   // A5
    Beep(987, tempo);   // B5
    Beep(1046, tempo * 2); // C6 hold

    // Descend
    Beep(987, tempo);
    Beep(880, tempo);
    Beep(783, tempo);
    Beep(698, tempo);
    Beep(659, tempo);
    Beep(587, tempo);
    Beep(523, tempo * 2); // End
}

//  ASCII credits scrolling + music together
void show_end_cutscene() {
    const char* credits[] = {
        "==================================================",
        "                THANK YOU FOR PLAYING!            ",
        "==================================================",
        "",
        "        A Retro Adventure Production",
        "        Powered by C++ Console",
        "",
        "        Programming:",
        "          Clement Yong",
        "          Wong Kai Zher",
        "          Amanda Joseph",
        "          Poh Yu Jie",
        "          Spencer Ang",
        "",
        "        Story:         Team 13",
        "        ASCII Art:     Retro Sprites",
        "        Music:         Windows Beep Orchestra",
        "",
        "        Special Thanks:",
        "        All brave adventurers who played!",
        "",
        "==================================================",
        "             See you in the next quest!           ",
        "=================================================="
    };

    int n = sizeof(credits) / sizeof(credits[0]);

    //  Run music in background while credits scroll
    thread musicThread(play_credits_jingle);

    for (int i = 0; i < n; i++) {
        cout << credits[i] << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // scroll speed
    }

    // Wait for the music to finish
    if (musicThread.joinable())
        musicThread.join();
}


