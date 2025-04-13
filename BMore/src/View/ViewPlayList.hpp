#include "IView.hpp"
#pragma once

class ViewPlayList : public IView {
public:
    ViewPlayList(Model& _model) : IView(_model) {};
    void OptionScreen() override;
};