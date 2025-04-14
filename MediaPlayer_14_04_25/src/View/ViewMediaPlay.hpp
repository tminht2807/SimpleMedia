#include "IView.hpp"
#pragma once

class ViewMediaPlay : public IView {
    std::shared_ptr<File> file;
public:
    ViewMediaPlay(std::shared_ptr<File> _file) : IView(), file(_file) {};
    
    void Show_Screen();

};