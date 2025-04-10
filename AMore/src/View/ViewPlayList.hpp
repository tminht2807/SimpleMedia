#include "IView.hpp"
#pragma once

class ViewPlayList : public IView {
public:
    void ShowScreen(Model& _model) override;
};