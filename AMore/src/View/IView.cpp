#include "IView.hpp"

void IView::ShowScreen(Model& _model){
    system("clear"); // Clear the console

    std::cout << "IView::ShowScreen()" << std::endl;

    // Show current media playing 
    std::cout << "Current PlayList: "  
              << _model.getCurrentPlayList().get()->get_PlayList_Name()
              << std::endl;
    std::cout << "Current Media: "  
              << _model.getCurrentPlayList().get()->getFile(_model.getCurrentFileIndex())->getFilePath()
              << std::endl;
}