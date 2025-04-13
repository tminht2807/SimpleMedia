#include "IView.hpp"
#pragma once

class ViewList : public IView {
public:
    ViewList(Model& _model) : IView(_model) {};
    void Show_ListPlaylist();

    
};