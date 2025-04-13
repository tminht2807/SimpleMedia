#include "ControllerMediaPlay.hpp"

void ControllerMediaPlay::HandleCases(size_t mode) {
    switch (mode) {
        case 0: // Play
            ControlPlayMedia(0 , 0);
            break;
        case 1: // Pause/Resume
            ControlPauseResumeMedia();
            break;
        case 2: // Next
            ControlNextMedia();
            break;
        case 3: // Previous
            ControlPreviousMedia();
            break;
        default:
            std::cout << "Invalid command!" << std::endl;
    }
}

void ControllerMediaPlay::ControlPlayMedia(size_t _chooseFileIndex, size_t _choosePlayListIndex) {
    // Play the media
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