#include "../Model/Model.hpp"
#pragma once
class IView {
protected:
    Model& model;  // **Shared model reference**
public:
    IView(Model& _model) : model(_model) {};

    void ShowScreen();

    void Default1();
    void Default2();

    virtual ~IView() = default;
};