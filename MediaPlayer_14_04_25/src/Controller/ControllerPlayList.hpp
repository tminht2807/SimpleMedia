#pragma once
#include "../Model/PlayList.hpp"
#include "../View/ViewPlayList.hpp"

class ControllerPlayList {
protected:
    std::shared_ptr<PlayList> playlist;
    ViewPlayList view;
    size_t current_playlist_Index;
public:
    ControllerPlayList(std::shared_ptr<PlayList> _playlist) : playlist(_playlist),current_playlist_Index(0) {
        // Initialize the controller with the model
    }
    ~ControllerPlayList() = default;

    void Show();

    std::shared_ptr<PlayList> Get_PlayList();

    std::shared_ptr<ViewPlayList> Get_View();

    void Set_PlayList(std::shared_ptr<PlayList> _playlist);

    void Set_View(ViewPlayList _view);

    void Set_Current_PlayList_Index(const size_t _playlist_index);
};