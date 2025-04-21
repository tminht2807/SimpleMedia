#include "ControllerList.hpp"

void ControllerList::Show(){
    view.Show_Screen(list.get()->Get_List_Names());
}

ViewList* ControllerList::Get_View(){
    return &view;
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