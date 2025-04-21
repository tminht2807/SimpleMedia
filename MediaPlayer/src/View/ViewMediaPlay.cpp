#include "ViewMediaPlay.hpp"


void ViewMediaPlay::Show_Screen(std::string _Current_PlayList_Name, size_t _Current_PlayList_Index,
                                std::string _Current_File_Title, size_t _Current_File_Index,
                                double _Duration, uint8_t _volume, bool _isConnected, bool _isPlaying) {
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
    
    if (_isPlaying == true ) std::cout << "Playing" ;
    else std::cout << "Paused";
    
    uint16_t temp = static_cast<uint16_t>(_volume * 100 / 62);
    std::cout << "          || Duration: " << _Duration  
              << "          || Volume: " << temp << std::endl;

    if (_isConnected) std::cout << "Connected to board" << std::endl;
    else std::cout << "Waiting for connection from board..." << std::endl;
    
    std::cout << std::endl;
    std::cout << "    'p': Pause/Resume current Media" << std::endl;
    std::cout << "    'n': Next Media in PlayList" << std::endl;
    std::cout << "    'b': Previous Media in PlayList" << std::endl;
    std::cout << std::endl;
}