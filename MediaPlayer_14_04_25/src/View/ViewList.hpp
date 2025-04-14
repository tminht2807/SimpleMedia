#include "IView.hpp"
#include "../Model/List.hpp"
#pragma once

class ViewList : public IView {
    std::shared_ptr<List> list;
public:
    ViewList(List& _list) : IView(), list(_list){};

    void Show_Screen();
};