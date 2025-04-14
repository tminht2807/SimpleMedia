#include "ControllerList.hpp"

std::shared_ptr<ViewList> ControllerList::getView() {
    return centerView;
}

Model& ControllerList::getModel() {
    return model;
}