#include "IView.hpp"
#include "../Model/List.hpp"
#pragma once

class ViewList : public IView {
public:
    ViewList() : IView(){};

    void Show_Screen(std::vector<std::string> _PlayList_Names);

    // void Set_Page(size_t _page) override;
};