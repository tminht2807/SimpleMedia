#include "IView.hpp"
#pragma once

class ViewMediaPlay : public IView {
public:
    ViewMediaPlay(Model& _model) : IView(_model) {};
    void ShowCurrentPlayList();
};