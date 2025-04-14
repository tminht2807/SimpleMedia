#pragma once
#include "../Model/PlayList.hpp"
#include "../View/ViewPlayList.hpp"

class ControllerPlayList {
protected:
    std::shared_ptr<PlayList> playlist;
    ViewPlayList view;
public:
    ControllerPlayList(std::shared_ptr<PlayList> _playlist) : playlist(_playlist) {
        // Initialize the controller with the model
    }
    ~ControllerPlayList() = default;

    std::shared_ptr<PlayList> Get_PlayList();

    std::shared_ptr<ViewPlayList> Get_View();

    void Set_PlayList(std::shared_ptr<PlayList> _playlist);

    void Set_View(ViewPlayList _view);
};