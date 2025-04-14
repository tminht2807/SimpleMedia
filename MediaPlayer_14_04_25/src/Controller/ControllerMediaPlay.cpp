#include "ControllerMediaPlay.hpp"

void ControllerMediaPlay::ControlPlayMedia(size_t _chooseFileIndex, size_t _choosePlayListIndex) {
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

std::shared_ptr<ViewMediaPlay> ControllerMediaPlay::getView() {
    return centerView;
}

Model& ControllerMediaPlay::getModel() {
    return model;
}