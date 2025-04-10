#include "../Model/Model.hpp"
#pragma once
class IView {
public:
    IView() = default;

    virtual void ShowScreen(Model& _model);

    virtual void OptionScreen(Model& _model);

    virtual ~IView() = default;
};