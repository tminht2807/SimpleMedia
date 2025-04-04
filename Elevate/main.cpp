#include "IController.hpp"
#include <iostream>
#include <string>

void DisplayMenu() {
    std::cout << "\nSimple Media Player\n";
    std::cout << "1. Play Media\n";
    std::cout << "2. Pause/Resume Media\n";
    std::cout << "3. Next Media\n";
    std::cout << "4. Previous Media\n";
    std::cout << "5. Update Directory\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    try {
        IController controller;

        int choice;
        while (true) {
            DisplayMenu();
            std::cin >> choice;

            switch (choice) {
                case 1: {
                    int index;
                    std::cout << "Enter media index to play: ";
                    std::cin >> index;
                    if (!controller.PlayMedia(index)) {
                        std::cerr << "Failed to play media.\n";
                    }
                    break;
                }
                case 2:
                    if (!controller.PauseResumeMedia()) {
                        std::cerr << "Failed to pause/resume media.\n";
                    }
                    break;
                case 3:
                    if (!controller.NextMedia()) {
                        std::cerr << "Failed to play next media.\n";
                    }
                    break;
                case 4:
                    if (!controller.PrevMedia()) {
                        std::cerr << "Failed to play previous media.\n";
                    }
                    break;
                case 5: {
                    std::string folderPath;
                    std::cout << "Enter folder path to update directory: ";
                    std::cin.ignore(); // Clear input buffer
                    std::getline(std::cin, folderPath);
                    controller.UpdateCurrentDirectory(folderPath);
                    break;
                }
                case 6:
                    std::cout << "Exiting program.\n";
                    return 0;
                default:
                    std::cerr << "Invalid choice. Please try again.\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
