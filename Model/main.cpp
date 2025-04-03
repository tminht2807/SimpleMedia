#include "File.hpp"

int main() {
    File demo("1.mp3");
    demo.Play();

    char cmd;
    while (true) {
        // Print the input prompt
        std::cout << "> " << std::flush;

        // Read user input
        std::cin >> cmd;

        if (cmd == 'p') {
            demo.Pause();
        } else if (cmd == 'q') {
            demo.Stop(); // Ensure playback stops cleanly
            break;
        }
    }

    return 0;
}