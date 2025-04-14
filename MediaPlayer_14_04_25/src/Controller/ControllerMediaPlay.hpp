#pragma once
#include "../Model/File.hpp"
#include "../View/ViewMediaPlay.hpp"

class ControllerMediaPlay  {
protected:
    std::shared_ptr<File> file;  // **Shared model reference**

    ViewMediaPlay view;
public:
    ControllerMediaPlay(std::shared_ptr<File> _file) : file(_file){
        // Initialize the controller with the model
    }
    ControllerMediaPlay();
    ~ControllerMediaPlay() = default;

    std::shared_ptr<ViewMediaPlay> Get_View();
    std::shared_ptr<File> Get_File();
    
    void Set_File(std::shared_ptr<File> _file);
    void Set_View(ViewMediaPlay _view);
    
    void ControlPlayMedia();
    void ControlPauseResumeMedia();
    void ControlNextMedia();
    void ControlPreviousMedia();
};