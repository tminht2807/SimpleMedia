#include "IView.hpp"
#pragma once

class ViewPlayList : public IView {
public:
    ViewPlayList(Model& _model) : IView(_model) {};
    void ShowCurrentPlayList();
    void Show_A_PlayList(size_t _play_list_index);
};