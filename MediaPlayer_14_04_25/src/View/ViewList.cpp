#include "ViewList.hpp"

void ViewList::Show_Screen(std::vector<std::string> _PlayList_Names){
    system("clear"); // Clear the console

    std::cout << "=============================================== MEDIA PLAYER ===============================================" << std::endl;
    std::cout << "List of PlayList:" << std::endl;
    
    for (size_t i = 0 ; i <= 9; i++){
        std::cout << "    '" << i << "'. " ;
        if (i + page*10 < _PlayList_Names.size()){
            std::cout << _PlayList_Names[i + page*10]
            << std::endl;
        }
        else std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "    'k': Next page" << std::endl;
    std::cout << "    'j': Previous page" << std::endl;
    std::cout <<std::endl;
    std::cout << "    'a': Add new PlayList" << std::endl;
    std::cout << "    'd': Delete a PlayList" << std::endl;
    std::cout << "    'c': Change current directory" << std::endl;
    std::cout <<std::endl;
    std::cout << "    's': Play a PlayList above" << std::endl;
    std::cout <<std::endl;
    std::cout << "    'e': Exit" << std::endl;
    std::cout <<std::endl;
}