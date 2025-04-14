#include "ViewPlayList.hpp"

void ViewPlayList::ShowCurrentPlayList(){
    Show_A_PlayList(0);
}

void ViewPlayList::Show_A_PlayList(size_t _play_list_index){
    Default1();

    std::cout << "PlayList "  << _play_list_index << ". "
    << model.get_PlayList(_play_list_index).get()->get_PlayList_Name()
    << std::endl;
    // If current PlayList is empty
    if (model.get_PlayList(_play_list_index).get()->get_Files().empty()) {
        std::cout << "No media in current PlayList" << std::endl;
        return;
    }
    else { // print name For every file in the current PlayList
        for (size_t i = 0; i < model.get_PlayList(_play_list_index).get()->get_Files().size(); i++) {
            std::cout << i + 1 << ". "  
            << model.get_PlayList(_play_list_index).get()->get_Files()[i]->getMetadata().Title
            << std::endl;
        }
    }

    Default2();
}
