#include "AppController.hpp"

void AppController::run(){
    // Main loop for the application
    controllerMediaPlay.ControlPlayMedia(0, 0);
    char cmd;

    do {
        icontroller.getView().get()->ShowScreen();
        std::cin >> cmd;

        switch (cmd) {
            case PAUSE_RESUME_MEDIA: {
                controllerMediaPlay.ControlPauseResumeMedia();
                break;
            }
            case NEXT_MEDIA: {
                controllerMediaPlay.ControlNextMedia();
                break;
            }
            case PREVIOUS_MEDIA: {
                controllerMediaPlay.ControlPreviousMedia();
                break;
            }
            case PLAY_FROM_CURRENT_DIRECTORY: {
                controllerMediaPlay.ControlPlayMedia(0,0);
                break;
            }
            case PLAY_MEDIA_IN_CURRENT_PLAYLIST: {
                PlayMediaInCurrentPlayList();
                break; // Added break to prevent fall-through
            }
            case PLAY_PLAYLIST: {
                PlayMediaInAPlayList();
                break;
            }
            case EXIT_OR_RETURN:{
                break;
            }
            default:
                std::cout << "Invalid command!" << std::endl;
        }

    } while (cmd != EXIT_OR_RETURN);
}

void AppController::PlayMediaInCurrentPlayList(){
    size_t chooseFileIndex;
    controllerPlayList.getView().get()->Default1();
    controllerPlayList.getView().get()->ShowCurrentPlayList();
    controllerPlayList.getView().get()->Default2();
    
    std::cout << "Choose a file to play: ";
    std::cin >> chooseFileIndex;
    
    while (chooseFileIndex >= controllerPlayList.getModel().get_CurrentPlayList().get()->get_Files().size()) {
        std::cout << "Invalid file index!" << std::endl;
        std::cout << "\nChoose a file to play: ";
        std::cin >> chooseFileIndex;
    }

    controllerMediaPlay.ControlPlayMedia(chooseFileIndex, 0);
}

void AppController::PlayMediaInAPlayList(){
    size_t choosePlayListIndex;
    controllerList.getView().get()->Default1();
    controllerList.getView().get()->Show_ListPlaylist();
    controllerList.getView().get()->Default2();
    
    std::cout << "Choose a PlayList to play: ";
    std::cin >> choosePlayListIndex;
    
    while (choosePlayListIndex >= controllerPlayList.getModel().get_List_PlayList().size()) {
        std::cout << "Invalid PlayList index!" << std::endl;
        std::cout << "\nChoose a PlayList to play: ";
        std::cin >> choosePlayListIndex;
    }

    controllerMediaPlay.ControlPlayMedia(0, choosePlayListIndex);
}