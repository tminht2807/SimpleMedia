#include "ViewList.hpp"

void ViewList::Show_Screen(){
    // system("clear"); // Clear the console

    std::cout << "=============================================== MEDIA PLAYER ===============================================" << std::endl;
    std::cout << "List of PlayList:" << std::endl;
    
    for (size_t i = 0 ; i <= 9; i++){
        std::cout << "    " << i << ". " ;
        if (i + page*10 < model.get_List_PlayList().size()){
            std::cout << model.get_List_PlayList()[i + page*10]->get_PlayList_Name()
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
    std::cout << "    '0': Exit" << std::endl;
    std::cout <<std::endl;

    std::cout << "=============================================== CURRENT MEDIA ===============================================" << std::endl;
    // show current media playing
    std::cout << "Current PlayList: "
    << model.getCurrentPlayListIndex() << ". "
    << model.get_CurrentPlayList().get()->get_PlayList_Name()
    << std::endl;

    std::cout << "Current File: "
    << model.getCurrentFileIndex() << ". "
    << model.get_CurrentPlayList().get()->get_Files()[model.getCurrentFileIndex()]->getMetadata().Title
    << std::endl;

    std::cout << "Duration: " << model.get_CurrentPlayList().get()->get_Files()[model.getCurrentFileIndex()]->getMetadata().Duration
    << std::endl;

    std::cout << "    'p': Pause/Resume new PlayList" << std::endl;
    std::cout << "    'n': Next Media in PlayList" << std::endl;
    std::cout << "    'b': Previous Media in PlayList" << std::endl;
    std::cout << std::endl;

    std::cout << "Console: " << console << std::endl;
    std::cout << ">> User: " ;
}