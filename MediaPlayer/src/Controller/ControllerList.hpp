#pragma once
#include "../Model/List.hpp"
#include "../View/ViewList.hpp"

class ControllerList {
protected:
    std::shared_ptr<List> list;  // **Shared model reference**

    ViewList view;
public:
    ControllerList(std::shared_ptr<List> _list) : list(_list) {
        // Initialize the controller with the model
    }
    ~ControllerList() = default;

    void Show();

    ViewList* Get_View();

    std::shared_ptr<List> Get_List();

    void Set_List(std::shared_ptr<List> _list);

    void Set_View(ViewList _view);
};