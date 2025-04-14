#include "IView.hpp"
#pragma once

class ViewPlayList : public IView {
public:
    ViewPlayList() : IView() {};

    void Show_Screen(std::vector<std::string> _Files_Title, 
                    std::string _PlayList_Name, size_t _PlayList_Index);
};