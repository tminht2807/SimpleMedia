#pragma once
#include "../Model/PlayList.hpp"
#include "../View/ViewPlayList.hpp"

class ControllerPlayList {
protected:
    std::shared_ptr<PlayList> playlist;
    ViewPlayList view;
public:
    ControllerPlayList(PlayList& pl, ViewPlayList v) : playlist(pl), view(v) {
        // Initialize the controller with the model
    }
    ~ControllerPlayList() = default;

    PlayList& Get_PlayList() ;

    ViewPlayList& Get_View();


};