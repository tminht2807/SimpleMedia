#include <iostream>

void printtt(){
    std::cout << "Hello World 11!" << std::endl;
    std::cout << "Hello World 12!" << std::endl;
    std::cout << "Hello World 13!" << std::endl;
    std::cout << "Hello World 14!" << std::endl;
    std::cout << "Hello World 15!" << std::endl;
    std::cout << "Hello World 1!" << std::endl;
    std::cout << "Hello World 2!" << std::endl;
    std::cout << "Hello World 3!" << std::endl;
    std::cout << "Hello World 4!" << std::endl;
    std::cout << "Hello World 5!" << std::endl;
    std::cout << "Hello World 6!" << std::endl;
    std::cout << "Hello World 7!" << std::endl;
    std::cout << "Hello World 8!" << std::endl;
    std::cout << "Hello World 9!" << std::endl;
    std::cout << "Hello World 10!" << std::endl;
}

int main(){
    std::string etwas; 
    printtt();

    for (int i = 0; i < 10; i++) {
        // Move cursor up
        std::cout << "\033[F";        // or "\033[A"
        // Clear the line
        std::cout << "\033[2K";
    }
    std::cout.flush();
    return 0;
}