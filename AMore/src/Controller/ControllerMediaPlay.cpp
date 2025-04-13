#include "ControllerMediaPlay.hpp"

void ControllerMediaPlay::ControlPlayMedia(size_t _chooseFileIndex, size_t _choosePlayListIndex) {
    // Play the media
    // if (_choosePlayListIndex < model.get_List_PlayList().size()) {
    //     if (_chooseFileIndex < model.get_PlayList(_choosePlayListIndex)->get_Files().size()) {
    //         model.setCurrentFileIndex(_chooseFileIndex);
    //         model.setCurrentPlayListIndex(_choosePlayListIndex);
    //         model.playCurrentFile();
    //     }
    //     else {
    //         std::cerr << "Index out of bounds for current_File_Index" << std::endl;
    //     }
    // }
    // else {
    //     std::cerr << "Index out of bounds for current_PlayList_Index" << std::endl;
    // }
    model.setCurrentFileIndex(_chooseFileIndex);
    model.setCurrentPlayListIndex(_choosePlayListIndex);
    model.playCurrentFile();
}

void ControllerMediaPlay::ControlPauseResumeMedia() {
    // Pause or resume the media
    model.PauseResumeMedia();
}

void ControllerMediaPlay::ControlNextMedia() {
    // Play the next media
    model.NextMedia();
}

void ControllerMediaPlay::ControlPreviousMedia() {
    // Play the previous media
    model.PrevMedia();
}