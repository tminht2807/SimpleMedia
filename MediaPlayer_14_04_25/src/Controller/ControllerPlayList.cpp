#include "ControllerPlayList.hpp"

void ControllerPlayList::Set_Current_PlayList_Index(const size_t _playlist_index){
    this->current_playlist_Index = _playlist_index;
}

void ControllerPlayList::Show(){
    view.Show_Screen(   playlist.get()->Get_List_Names(),
                        playlist.get()->Get_PlayList_Name(), 
                        current_playlist_Index);
}

std::shared_ptr<PlayList> ControllerPlayList::Get_PlayList(){
    return playlist;
}

std::shared_ptr<ViewPlayList> ControllerPlayList::Get_View(){
    return std::make_shared<ViewPlayList>(view);
}

void ControllerPlayList::Set_PlayList(std::shared_ptr<PlayList> _playlist, size_t _playlist_index){
    this->playlist = _playlist;
    this->current_playlist_Index = _playlist_index;
}

void ControllerPlayList::Set_View(ViewPlayList _view){
    this->view = _view;
}