#include "ControllerPlayList.hpp"

std::shared_ptr<PlayList> ControllerPlayList::Get_PlayList(){
    return playlist;
}

std::shared_ptr<ViewPlayList> ControllerPlayList::Get_View(){
    return std::make_shared<ViewPlayList>(view);
}

void ControllerPlayList::Set_PlayList(std::shared_ptr<PlayList> _playlist){
    this->playlist = _playlist;
}

void ControllerPlayList::Set_View(ViewPlayList _view){
    this->view = _view;
}