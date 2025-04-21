#include "../Model/List.hpp"
#pragma once
class IView {
protected:
    size_t page;

    inline static std::string console = "";
public:
    IView(): page(0) {};

    void Reset_Page();
    void Set_Page(size_t _page);
    size_t Get_Page();

    void Show_Screen();

    void Set_Console(std::string _temp_console);
    void Reset_Console();

    virtual ~IView() = default;
};