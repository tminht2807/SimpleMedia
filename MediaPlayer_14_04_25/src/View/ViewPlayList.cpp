#include "ViewPlayList.hpp"

void ViewPlayList::Show_Screen( std::vector<std::string> _Files_Title, 
                                std::string _PlayList_Name, size_t _PlayList_Index) {
    system("clear"); // Clear the console

    std::cout << "=============================================== MEDIA PLAYER ===============================================" << std::endl;
    std::cout << "PlayList:" 
    << _PlayList_Index << ". " 
    << _PlayList_Name << std::endl;
    
    for (size_t i = 0 ; i <= 9; i++){
        std::cout << "    '" << i << "'. " ;
        if (i + page*10 < _Files_Title.size()){
            std::cout << _Files_Title[i + page*10]
            << std::endl;
        }
        else std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "    'k': Next page" << std::endl;
    std::cout << "    'j': Previous page" << std::endl;
    std::cout <<std::endl;
    std::cout << "    'a': Add new Media file" << std::endl;
    std::cout << "    'd': Delete a Media file" << std::endl;
    std::cout <<std::endl;
    std::cout << "    's': Play a Media above" << std::endl;
    std::cout <<std::endl;
    std::cout << "    'e': Return" << std::endl;
    std::cout <<std::endl;
}

// void ViewPlayList::Set_Page(size_t _page) {
//     this->page = _page;
// }