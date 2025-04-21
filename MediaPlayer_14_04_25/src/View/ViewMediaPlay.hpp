#include "IView.hpp"
#pragma once

class ViewMediaPlay : public IView {
public:
    ViewMediaPlay() : IView(){};
    
    void Show_Screen(   std::string _Current_PlayList_Name, size_t _Current_PlayList_Index,
                        std::string _Current_File_Title,    size_t _Current_File_Index,
                        double _Duration, uint8_t _volume, bool _isConnected, bool _isPlaying);

};