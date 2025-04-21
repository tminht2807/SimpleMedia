#include "ViewList.hpp"

void ViewList::Show_Screen(std::vector<std::string> _PlayList_Names){

    std::cout << "=============================================== MEDIA PLAYER ===============================================" << std::endl;
    std::cout << "List of PlayList:" << std::endl;
    std::cout <<std::endl;

    for (size_t i = 0 ; i <= 9; i++){
        std::cout << "    '" << i << "'. " << i + page*10 << ". ";
        if (i + page*10 < _PlayList_Names.size()){
            std::cout << _PlayList_Names[i + page*10]
            << std::endl;
        }
        else std::cout << std::endl;
    }
    std::cout << std::endl;

    size_t total_page;
    if (_PlayList_Names.size() == 0) total_page = 1;
    else total_page =  (_PlayList_Names.size() - 1)/10 + 1 ;
    std::cout << "    'k': Next page    " << "Page: " << Get_Page() + 1 << " / "<< total_page <<"    'j': Previous page"<< std::endl;

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