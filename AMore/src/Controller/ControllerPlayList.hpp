#pragma once
#include "../Model/Model.hpp"
#include "../View/ViewPlayList.hpp"

class ControllerPlayList {
protected:
    Model& model;  // **Shared model reference**

    std::shared_ptr<ViewPlayList> centerView;
public:
    ControllerPlayList(Model& m, std::shared_ptr<ViewPlayList> v) : model(m), centerView(v) {
        // Initialize the controller with the model
    }
    ~ControllerPlayList() = default;

    Model& getModel() {
        return model;
    }

    std::shared_ptr<ViewPlayList> getView(){
        return centerView;
    }
};