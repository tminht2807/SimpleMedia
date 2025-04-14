#include "IView.hpp"
#pragma once

class ViewPlayList : public IView {
    std::shared_ptr<PlayList> playlist;
public:
    ViewPlayList(std::shared_ptr<PlayList> _playlist ) : IView(), playlist(_playlist) {};

    void Show_Screen();
};