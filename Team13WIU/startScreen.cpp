// startScreen.cpp
#include "startScreen.h"


std::atomic<bool> musicRunning{ true };

// Music thread
void beepMusicLoop() {
    while (musicRunning) {
        Beep(523, 150); // C5
        Beep(659, 150); // E5
        Beep(784, 150); // G5
        Beep(1046, 150); // C6
    }
}

// Console helpers
void setRed() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_RED | FOREGROUND_INTENSITY);
}
void setDefault() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void clearScreen() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    DWORD written{};
    GetConsoleScreenBufferInfo(h, &csbi);
    DWORD cells = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(h, ' ', cells, { 0,0 }, &written);
    FillConsoleOutputAttribute(h, csbi.wAttributes, cells, { 0,0 }, &written);
    SetConsoleCursorPosition(h, { 0,0 });
}

// Animated ASCII logo
void animateVortigen() {
    setRed();
    std::vector<std::string> lines = {
        "V     V   OOOOO    RRRRR    TTTTTTT  IIIII     GGGGG   EEEEEEE  N     N",
        "V     V  O     O   R    R      T       I     G     G  E         NN    N",
        "V     V  O     O   R    R      T       I     G        E         N N   N",
        " V   V   O     O   RRRRR       T       I     G  GGG   EEEEEE    N  N  N",
        "  V V    O     O   R R         T       I     G    G   E         N   N N",
        "   V     O     O   R  R        T       I     G    G   E         N    NN",
        "   V      OOOOO    R   R       T     IIIII     GGGG    EEEEEEE  N     N"
    };

    std::vector<std::string> display = lines;
    for (auto& line : display)
        for (auto& c : line) c = ' '; // start blank

    const int totalSteps = 100;
    for (int step = 0; step < totalSteps; ++step) {
        int r = rand() % lines.size();
        int c = rand() % lines[r].size();
        display[r][c] = lines[r][c];

        clearScreen();
        for (auto& line : display) std::cout << line << "\n";
        std::cout << "\n                     [ START ]\n\n";
        setDefault();
        std::cout << "Press SPACE to start, ESC to quit.\n";
        setRed();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    clearScreen();
    for (auto& line : lines) std::cout << line << "\n";
    std::cout << "\n                     [ START ]\n\n";
    setDefault();
    std::cout << "Press SPACE to start, ESC to quit.\n";
}

// Main start screen function
void startScreen() {
    SetConsoleTitleA("VORTIGEN - Start Screen");
    clearScreen();

    std::thread musicThread(beepMusicLoop); // start music
    animateVortigen();                       // animate logo

    // wait for SPACE or ESC
    while (true) {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 27) break; // ESC
            if (ch == ' ') break; // SPACE
        }
        Sleep(10);
    }

    musicRunning = false;
    musicThread.join();
    clearScreen();
    std::cout << "Starting VORTIGEN...\n";
    Sleep(1500);



    // Dark story narration after logo
    Sleep(1000);
    std::cout << "\n\n";

    std::cout << "\033[33mIn the dark ages, a Villain has arrived...\033[0m\n";
    Beep(400, 300); Sleep(400);

    std::cout << "\033[33mEvil King Vortigen still holds the throne...\033[0m\n";
    Beep(300, 500); Sleep(600);

    std::cout << "\033[33mThe townspeople suffer under heavy taxes...\033[0m\n";
    Beep(350, 250); Sleep(400);

    std::cout << "\033[33mSoldiers of the palace have set fire to the town square...\033[0m\n";
    Beep(500, 300); Sleep(500);

    std::cout << "\033[33mThe Villain now witnesses his people burned alive...\033[0m\n";
    Beep(450, 400); Sleep(800);

    std::cout << "\033[33mHis journey begins.\033[0m\n\n";
    Beep(600, 300); Sleep(1000);

}
