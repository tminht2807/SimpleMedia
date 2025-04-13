#include "ViewPlayList.hpp"

void ViewPlayList::ShowCurrentPlayList(){
    std::cout << "ViewPlayList::ShowCurrentPlayList()" << std::endl;
    std::cout << "Current PlayList: "  
    << model.get_CurrentPlayList().get()->get_PlayList_Name()
    << std::endl;
    // If current PlayList is empty
    if (model.get_CurrentPlayList().get()->get_Files().empty()) {
        std::cout << "No media in current PlayList" << std::endl;
        return;
    }
    else { // print name For every file in the current PlayList
        for (size_t i = 0; i < model.get_CurrentPlayList().get()->get_Files().size(); i++) {
            std::cout << i << ". "  
            << model.get_CurrentPlayList().get()->get_Files()[i]->getMetadata().Title
            << std::endl;
        }
    }

    std::cout << std::endl;
}
