#include "../Model/Model.hpp"
#pragma once
class IView {
protected:
    Model& model;  // **Shared model reference**

    size_t page;

    std::string console;
public:
    IView(Model& _model) : model(_model), page(0), console("") {};

    void ShowScreen();

    void Default1();
    void Default2();

    void resetPage();

    void setConsole(std::string _temp_console);

    virtual ~IView() = default;
};