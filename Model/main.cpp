#include "File.hpp"

int main(){
    File demo("KhoiThuocDoiCho-JimmiiNguyen-7990799.mp3");
    demo.Play();
    std::cout << "Threading successfully" << std::endl;
    char cmd;

    while (true) {
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