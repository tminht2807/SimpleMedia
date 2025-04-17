#pragma once
#include "../Model/PlayList.hpp"
#include "../View/ViewPlayList.hpp"

class ControllerPlayList {
protected:
    std::shared_ptr<PlayList> playlist;
    ViewPlayList view;
    size_t current_playlist_Index;
public:
    ControllerPlayList() = default;
    ~ControllerPlayList() = default;

    void Show();

    std::shared_ptr<PlayList> Get_PlayList();

    ViewPlayList* Get_View();

    void Set_PlayList(std::shared_ptr<PlayList> _playlist, size_t _playlist_index);

    void Set_View(ViewPlayList _view);

    void Set_Current_PlayList_Index(const size_t _playlist_index);

    size_t Get_Current_PlayList_Index();
};