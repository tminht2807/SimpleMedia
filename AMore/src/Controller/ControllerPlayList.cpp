#include "ControllerPlayList.hpp"

Model& ControllerPlayList::getModel() {
    return model;
}

std::shared_ptr<ViewPlayList> ControllerPlayList::getView(){
    return centerView;
}