#include "IView.hpp"
#pragma once

class ViewMediaPlay : public IView {
public:
    void ShowScreen(Model& _model) override;
};