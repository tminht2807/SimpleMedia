#include "IView.hpp"

void IView::resetPage(){
    page = 0;
}

void IView::ShowScreen(){
    Default1();
    // Optional part

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
    
    Default2();
}

void IView::setConsole(std::string _temp_console){
    this->console = _temp_console;
}

void IView::Default2(){
    std::cout << std::endl;
    std::cout << "'0'. Exit/Return" << std::endl;
    std::cout << std::endl;
    std::cout << "Console:" << console << std::endl;
    std::cout << ">> Enter command: ";
}

void IView::Default1(){
    // system("clear"); // Clear the console

    std::cout << "=============================================== MEDIA PLAYER ===============================================" << std::endl;

    // show current media playing
    std::cout << "Current PlayList: "
    << model.getCurrentPlayListIndex() << ". "
    << model.get_CurrentPlayList().get()->get_PlayList_Name()
    << std::endl;
    std::cout << "Current File: "
    << model.getCurrentFileIndex() << ". "
    << model.get_CurrentPlayList().get()->get_Files()[model.getCurrentFileIndex()]->getMetadata().Title
    << std::endl;
    std::cout << "Duration: " << model.get_CurrentPlayList().get()->get_Files()[model.getCurrentFileIndex()]->getMetadata().Duration
    << std::endl;

    
}