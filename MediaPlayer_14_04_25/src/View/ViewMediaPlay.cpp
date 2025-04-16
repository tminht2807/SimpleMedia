#include "ViewMediaPlay.hpp"


void ViewMediaPlay::Show_Screen(std::string _Current_PlayList_Name, size_t _Current_PlayList_Index,
                                std::string _Current_File_Title, size_t _Current_File_Index,
                                double _Duration) {
    std::cout << "=============================================== CURRENT MEDIA ===============================================" << std::endl;
    // show current media playing
    std::cout << "Current PlayList: "
    << _Current_PlayList_Index << ". "
    << _Current_PlayList_Name
    << std::endl;

    std::cout << "Current File: "
    << _Current_File_Index << ". "
    << _Current_File_Title
    << std::endl;

    std::cout << "Duration: " << _Duration << std::endl;

    std::cout << "    'p': Pause/Resume current Media" << std::endl;
    std::cout << "    'n': Next Media in PlayList" << std::endl;
    std::cout << "    'b': Previous Media in PlayList" << std::endl;
    std::cout << std::endl;
}