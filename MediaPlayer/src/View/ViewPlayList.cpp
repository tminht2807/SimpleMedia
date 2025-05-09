#include "ViewPlayList.hpp"

void ViewPlayList::Show_Screen( std::vector<std::string> _Files_Title, 
                                std::string _PlayList_Name, size_t _PlayList_Index) {

    std::cout << "=============================================== MEDIA PLAYER ===============================================" << std::endl;
    std::cout << "PlayList: " 
    << _PlayList_Index << ". " 
    << _PlayList_Name << std::endl;
    std::cout <<std::endl;

    for (size_t i = 0 ; i <= 9; i++){
        std::cout << "    '" << i << "'. " << i + page*10 << ". ";
        if (i + page*10 < _Files_Title.size()){
            std::cout << _Files_Title[i + page*10]
            << std::endl;
        }
        else std::cout << std::endl;
    }
    std::cout << std::endl;

    size_t total_page;
    if (_Files_Title.size() == 0) total_page = 1;
    else total_page =  (_Files_Title.size() - 1)/10 + 1 ;
    std::cout << "    'k': Next page    " << "Page: " << Get_Page() + 1 << " / "<< total_page <<"    'j': Previous page"<< std::endl;    
    std::cout <<std::endl;
    
    std::cout << "    'a': Add new Media file" << std::endl;
    std::cout << "    'd': Delete a Media file" << std::endl;
    std::cout <<std::endl;
    std::cout <<std::endl;
    std::cout << "    's': Play a Media above" << std::endl;
    std::cout <<std::endl;
    std::cout << "    'e': Return" << std::endl;
    std::cout <<std::endl;
}