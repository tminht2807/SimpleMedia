#pragma once
#include "../View/IView.hpp"
#include "../Model/Model.hpp"

class IController {
protected:
    Model& model;  // **Shared model reference**

    std::shared_ptr<IView> centerView;
public:
    IController(Model& m, std::shared_ptr<IView> v) : model(m), centerView(v) {}
    ~IController() = default;

    std::shared_ptr<IView> getView();

    Model& getModel();
};
