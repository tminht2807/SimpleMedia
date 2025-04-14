#include "../Model/Model.hpp"
#pragma once
class IView {
protected:
    size_t page;

    std::string console;
public:
    IView(): page(0), console("") {};

    void Reset_Page();
    void Set_Page(size_t _page);
    size_t Get_Page();

    void Set_Console(std::string _temp_console);

    virtual ~IView() = default;
};