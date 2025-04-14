#include "ControllerList.hpp"

std::shared_ptr<ViewList> ControllerList::Get_View(){
    return std::make_shared<ViewList>(view);
}

std::shared_ptr<List> ControllerList::Get_List(){
    return list;
}    

void ControllerList::Set_List(std::shared_ptr<List> _list){
    this->list = _list;
}

void ControllerList::Set_View(ViewList _view){
    this->view = _view;
}