#include "IView.hpp"
#pragma once

class ViewList : public IView {
public:
    void ShowScreen(Model& _model) override;
};