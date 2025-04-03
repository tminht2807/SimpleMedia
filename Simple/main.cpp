#include "IController.hpp"

int main() {
    IController controller;
    controller.InitAudio();

    char cmd;
    while (true) {
        std::cout << "> " << std::flush;
        std::cin >> cmd;

        if (cmd == 'p') {
            controller.PauseMedia();
        } else if (cmd == 's') {
            controller.StopMedia();
        } else if (cmd == '1') {
            controller.PlayMedia(0);
        } else if (cmd == '2') {
            controller.PlayMedia(1);
        } else if (cmd == '3') {
            controller.PlayMedia(2);
        } else if (cmd == 'n') {
            controller.Next();
        } else if (cmd == 'b') { // 'b' for "back"
            controller.Prev();
        } else if (cmd == 'q') {
            controller.StopMedia();
            break;
        }
    }

    return 0;
}