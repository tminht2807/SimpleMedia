#include "IView.hpp"

void IView::Reset_Page(){
    page = 0;
}

void IView::Set_Page(size_t _page){
    this->page = _page;
}

size_t IView::Get_Page(){
    return page;
}

void IView::Set_Console(std::string _temp_console){
    this->console = _temp_console;
}

void IView::Reset_Console(){
    this->console = "";
}

void IView::Show_Screen(){
    std::cout << "Command prompt:" << std::endl;
    std::cout << ">> Console: " << console << std::endl;
    std::cout << ">> User: " ;
}