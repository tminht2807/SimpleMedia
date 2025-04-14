#pragma once
#include "../Model/Model.hpp"
#include "../View/ViewList.hpp"

class ControllerList {
protected:
    Model& model;  // **Shared model reference**

    std::shared_ptr<ViewList> centerView;
public:
    ControllerList(Model& m, std::shared_ptr<ViewList> v) : model(m), centerView(v) {
        // Initialize the controller with the model
    }
    ~ControllerList() = default;

    std::shared_ptr<ViewList> getView();

    Model& getModel();    
};