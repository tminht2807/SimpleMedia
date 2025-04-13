#include "IView.hpp"

void IView::ShowScreen(){
    Default1();
    // Optional part
    OptionScreen();
    Default2();
}

void IView::Default1(){
    system("clear"); // Clear the console

    std::cout << "=============================================== MEDIA PLAYER ===============================================" << std::endl;
    std::cout << std::endl;
}
void IView::Default2(){
    std::cout << "=============================================== CURRENT MEDIA ===============================================" << std::endl;
    // Show current media playing 
    std::cout << "Current PlayList: "  
    << model.get_CurrentPlayList().get()->get_PlayList_Name()
    << std::endl;
    // If current PlayList is empty
    if (model.get_CurrentPlayList().get()->get_Files().empty()) {
    std::cout << "No media in current PlayList" << std::endl;
    return;
    }
    else {
    std::cout << "Current Media: "  
        << model.get_CurrentPlayList().get()->getFile(model.getCurrentFileIndex())->getFilePath()
        << std::endl;
    }
    std::cout << "Duration: "
    << model.get_CurrentPlayList().get()->getFile(model.getCurrentFileIndex())->getDuration()
    << std::endl;
    
    std::cout << std::endl;

    std::cout << ">> Enter your command: ";
}

void IView::OptionScreen(){
    std::cout << "'p'. Pause/Resume"<< std::endl;
    std::cout << "'n'. Next in PlayList" << std::endl;
    std::cout << "'b'. Previous in PlayList" << std::endl;
    std::cout << std::endl;
    std::cout << "'1'. Play from current directory (PlayList number 0)" << std::endl;
    std::cout << "'2'. Play a media in Current Playing List" << std::endl;
    std::cout << "'3'. Play a PlayList" << std::endl;
    std::cout << std::endl;
    std::cout << "'4'. Show current directory (PlayList number 0)" << std::endl;
    std::cout << "'5'. Show a PlayList from Media Library" << std::endl;
    std::cout << "'6'. Show Media Library" << std::endl;
    std::cout << std::endl;
    std::cout << "'7'. Delete a PlayList from Media Library" << std::endl;
    std::cout << "'8'. Add a PlayList to Media Library" << std::endl;
    std::cout << "'a'. add Media to PlayList in Media Library" << std::endl;
    std::cout << "'r'. remove Media from PlayList in Media Library" << std::endl;
    std::cout << "'c'. change current directory" << std::endl;
    std::cout << std::endl;
    std::cout << "'0'. Exit Media Player" << std::endl;
    std::cout << std::endl;
}