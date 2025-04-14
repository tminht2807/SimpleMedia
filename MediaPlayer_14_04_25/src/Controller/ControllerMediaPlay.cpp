#include "ControllerMediaPlay.hpp"

std::shared_ptr<ViewMediaPlay> ControllerMediaPlay::Get_View(){
    return std::make_shared<ViewMediaPlay>(view);
}

std::shared_ptr<File> ControllerMediaPlay::Get_File(){
    return file;
}

void ControllerMediaPlay::Set_File(std::shared_ptr<File> _file){
    this->file = _file;
}
void ControllerMediaPlay::Set_View(ViewMediaPlay _view){
    this->view = _view;
}

void ControllerMediaPlay::ControlPlayMedia(){

}
void ControllerMediaPlay::ControlPauseResumeMedia(){

}
void ControllerMediaPlay::ControlNextMedia(){

}
void ControllerMediaPlay::ControlPreviousMedia(){

}