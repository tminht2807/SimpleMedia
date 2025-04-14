#include "IController.hpp"

std::shared_ptr<IView> IController::getView(){
    return centerView;
}

Model& IController::getModel() {
    return model;
}