#include "ViewPlayList.hpp"

void ViewPlayList::Show_Screen(){
    // system("clear"); // Clear the console

    std::cout << "=============================================== MEDIA PLAYER ===============================================" << std::endl;
    std::cout << "PlayList:" 
    << model.get_PlayList(_PlayList_Index) << ". " 
    << model.get_PlayList(_PlayList_Index).get()->get_PlayList_Name() <<std::endl;
    
    for (size_t i = 0 ; i <= 9; i++){
        std::cout << "    " << i << ". " ;
        if (i + page*10 < model.get_PlayList(_PlayList_Index).get()->get_Files().size()){
            std::cout << model.get_PlayList(_PlayList_Index).get()->get_Files()[i + page*10].get()->getTitle()
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
    std::cout << "    '0': Return" << std::endl;
    std::cout <<std::endl;

    std::cout << "=============================================== MEDIA PLAYER ===============================================" << std::endl;
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
