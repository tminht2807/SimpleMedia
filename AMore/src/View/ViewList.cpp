#include "ViewList.hpp"

void ViewList::Show_ListPlaylist(){
    for (size_t i = 0; i < model.get_List_PlayList().size(); i++) {
        std::cout << i << ". "  
        << model.get_List_PlayList()[i]->get_PlayList_Name()
        << std::endl;
    }
}