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
                PlayAPlayList();
                break;
            }
            case SHOW_CURRENT_DIRECTORY: {
                controllerPlayList.getView().get()->ShowCurrentPlayList();
                break;
            }
            case SHOW_PLAYLIST_FROM_MEDIA_LIBRARY: {
                Show_A_PlayList_From_Media_Library();
                break;
            }
            case SHOW_MEDIA_LIBRARY: {
                controllerList.getView().get()->Show_ListPlaylist();
                break;
            }
            case DELETE_PLAYLIST_FROM_MEDIA_LIBRARY: {
                Del_A_PlayList();
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

void AppController::Del_A_PlayList(){
    controllerList.getView().get()->Show_ListPlaylist();
    size_t choosePlayListIndex;
    std::cout << ">> Choose a PlayList index: ";
    std::cin >> choosePlayListIndex;
    while (choosePlayListIndex >= controllerPlayList.getModel().get_List_PlayList().size()) {
        std::cout << "Invalid PlayList index!" << std::endl;
        std::cout << "\n>>Choose a PlayList index: ";
        std::cin >> choosePlayListIndex;
    }
    controllerList.Remove_A_PlayList(choosePlayListIndex);
}

void AppController::Show_A_PlayList_From_Media_Library(){
    size_t choosePlayListIndex;
    do {
        controllerList.getView().get()->setConsole("Choose a PlayList index to show: ");
        controllerList.getView().get()->Show_ListPlaylist();
        std::cin >> choosePlayListIndex;

        if ( choosePlayListIndex == NUM_EXIT_OR_RETURN) {
            controllerList.getView().get()->setConsole("");
            break;
        }
        else if (choosePlayListIndex >= controllerList.getModel().get_List_PlayList().size()) {
            controllerList.getView().get()->setConsole("Invalid PlayList index!");
        }
        else {
            controllerPlayList.getView().get()->Show_A_PlayList(choosePlayListIndex);
        }
    } while (choosePlayListIndex != NUM_EXIT_OR_RETURN);

}

void AppController::PlayMediaInCurrentPlayList(){
    size_t chooseFileIndex;
    do {
        controllerPlayList.getView().get()->setConsole("Choose a file index: ");
        controllerPlayList.getView().get()->ShowCurrentPlayList();
        std::cin >> chooseFileIndex;

        if (chooseFileIndex == NUM_EXIT_OR_RETURN) {
            controllerPlayList.getView().get()->setConsole("");
            break;
        }
        else if (chooseFileIndex >= controllerPlayList.getModel().get_CurrentPlayList().get()->get_Files().size()) {
            controllerPlayList.getView().get()->setConsole("Invalid file index!");
            }
        else {
            controllerMediaPlay.ControlPlayMedia(chooseFileIndex - 1, 0);
            controllerPlayList.getView().get()->setConsole("Played media successfully");
        }       
    } while (chooseFileIndex != NUM_EXIT_OR_RETURN);
}

void AppController::PlayAPlayList(){
    size_t choosePlayListIndex;
    do {
        controllerList.getView().get()->setConsole("Choose a PlayList index: ");
        controllerList.getView().get()->Show_ListPlaylist();
        std::cin >> choosePlayListIndex;

        if (choosePlayListIndex == NUM_EXIT_OR_RETURN) {
            controllerList.getView().get()->setConsole("");
            break;
        }
        else if (choosePlayListIndex >= controllerPlayList.getModel().get_List_PlayList().size()) {
            controllerList.getView().get()->setConsole("Invalid PlayList index!");
        }
        else{
            controllerMediaPlay.ControlPlayMedia(0, choosePlayListIndex);
        }
    } while (choosePlayListIndex != NUM_EXIT_OR_RETURN);
}