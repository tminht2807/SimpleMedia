#include "ControllerList.hpp"

std::shared_ptr<ViewList> ControllerList::getView() {
    return centerView;
}

Model& ControllerList::getModel() {
    return model;
}

void ControllerList::Remove_A_PlayList(size_t _PlayList_index) {
    getModel().Remove_A_PlayList(_PlayList_index);
}