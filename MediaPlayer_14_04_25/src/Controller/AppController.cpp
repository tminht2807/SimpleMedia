#include "AppController.hpp"

void AppController::run(){
    // Main loop for the application
    controllerMediaPlay.Set_PlayList(controllerList.Get_List().get()->Get_A_PlayList(0),0);
    controllerMediaPlay.ControlPlayMedia();
    char cmd;
    do {
        controllerList.Show();
        controllerMediaPlay.Show();
        viewConsole.get()->Show_Screen();
        std::cin >> cmd;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
        switch (cmd){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {
                size_t playList_Index_choose = cmd - '0' + (controllerList.Get_View()->Get_Page())*10;
                if (playList_Index_choose + 1   >   controllerList.Get_List().get()->Get_List().size()) {
                    viewConsole.get()->Set_Console("Invalid playlist!");
                }
                else {
                    controllerPlayList.Set_PlayList(controllerList.Get_List().get()->Get_A_PlayList(playList_Index_choose),playList_Index_choose);
                    viewConsole.get()->Set_Console("Entered a Playlist!");
                    controllerList.Get_View()->Reset_Page();
    
                    change_run_on_playlist_mode();
                }
                break;
            }
            case NEXT_PAGE:{
                if (controllerList.Get_View()->Get_Page()*10 + 10 >= controllerList.Get_List().get()->Get_List().size()){
                    viewConsole.get()->Set_Console("Last page already! No next page!");
                }
                else {
                    size_t temp = controllerList.Get_View()->Get_Page();
                    controllerList.Get_View()->Set_Page(temp + 1);
                    // viewConsole.get()->Set_Console("Page" + std::to_string(temp + 1) + "! page var" + std::to_string(controllerList.Get_View()->Get_Page()));
                }
                break;
            }
            case PREV_PAGE:{
                if (controllerList.Get_View()->Get_Page() == 0) {
                    viewConsole.get()->Set_Console("First page already! No previous page!");
                }
                else {
                    size_t temp = controllerList.Get_View()->Get_Page();
                    controllerList.Get_View()->Set_Page(temp - 1);
                }
                break;
            }
            case CHANGE_DIR:{
                std::string temp;
                do {
                    viewConsole.get()->Set_Console("Enter new directory!");
                    controllerList.Show();
                    controllerMediaPlay.Show();
                    viewConsole.get()->Show_Screen();
                    std::cin >> temp;
                    if      (temp == "n") controllerMediaPlay.ControlNextMedia();
                    else if (temp == "p") controllerMediaPlay.ControlPauseResumeMedia();
                    else if (temp == "b") controllerMediaPlay.ControlPreviousMedia();
                    else if (temp == "e") { viewConsole.get()->Set_Console("Canceled directory change!"); break;}
                    else {
                        std::filesystem::path path(temp);
                        if (std::filesystem::is_directory(path)) {                         // Check if temp is a valid folder directory
                            controllerList.Get_List().get()->Get_A_PlayList(0).get()->Clear_PlayList();
                            controllerList.Get_List().get()->Get_A_PlayList(0).get()->Add_By_Directory(path);
                            viewConsole.get()->Set_Console("Changed directory successfully!");
                            temp = "Current directory: " + temp; 
                            controllerList.Get_List().get()->Get_A_PlayList(0).get()->Set_PlayList_Name(temp);

                            controllerMediaPlay.Set_PlayList(controllerList.Get_List().get()->Get_A_PlayList(0),0);
                            controllerMediaPlay.ControlPlayMedia();
                        }
                        // else if (std::filesystem::is_regular_file(path)){                  // Check if temp is a valid file
                        //     if (path.extension() != ".mp3"){
                        //         viewConsole.get()->Set_Console("Invalid file type! Only .mp3 files are allowed!");
                        //     }
                        //     else{
                        //         auto file = std::make_shared<File>(temp);
                        //         controllerList.Get_List().get()->Get_A_PlayList(0).get()->Add_File(file);
                        //         viewConsole.get()->Set_Console("Added file successfully!");
                        //     }
                        // }
                    }
                } while (temp == "n" || temp == "p" || temp == "b");
                break;
            }
            case ADD_NEW:{
                std::string temp;
                do {
                    viewConsole.get()->Set_Console("Enter new PlayList Name!");
                    controllerList.Show();
                    controllerMediaPlay.Show();
                    viewConsole.get()->Show_Screen();
                    std::cin >> temp;
                    if      (temp == "n") controllerMediaPlay.ControlNextMedia();
                    else if (temp == "p") controllerMediaPlay.ControlPauseResumeMedia();
                    else if (temp == "b") controllerMediaPlay.ControlPreviousMedia();
                    else if (temp == "e") { viewConsole.get()->Set_Console("Canceled directory change!"); break;}
                    else {
                        if (!controllerList.Get_List().get()->Add_PlayList(temp)) 
                            viewConsole.get()->Set_Console("Playlist with this name already exists!");
                        else viewConsole.get()->Set_Console("Added PlayList succesfully!");
                    }
                } while (temp == "n" || temp == "p" || temp == "b");
                break;
            }
            case DEL_FROM:{
                char temp;
                do {
                    viewConsole.get()->Set_Console("Enter the number of PlayList to delete!");
                    controllerList.Show();
                    controllerMediaPlay.Show();
                    viewConsole.get()->Show_Screen();
                    std::cin >> temp;
                    if      (temp == NEXT_MEDIA) controllerMediaPlay.ControlNextMedia();
                    else if (temp == PAUSE_RESUME_MEDIA) controllerMediaPlay.ControlPauseResumeMedia();
                    else if (temp == PREV_MEDIA) controllerMediaPlay.ControlPreviousMedia();
                    else if (temp == EXIT_RETURN) { viewConsole.get()->Set_Console("Canceled playlist delete!"); break;}
                    else if (temp == '0' || temp == '1' || temp == '2' || temp == '3' || temp == '4' || temp == '5' || temp == '6' || temp == '7' || temp == '8' || temp == '9') {
                        size_t _del_playlist_index = temp - '0' + (controllerList.Get_View()->Get_Page())*10;
                        if (_del_playlist_index >= controllerList.Get_List().get()->Get_List().size()) {
                            viewConsole.get()->Set_Console("Invalid playlist!");
                        }
                        else {
                            controllerList.Get_List().get()->Remove_PlayList(_del_playlist_index);
                            if (controllerMediaPlay.Get_Current_PlayList_Index() > _del_playlist_index){
                                controllerMediaPlay.Set_Current_PlayList_Index(controllerMediaPlay.Get_Current_PlayList_Index() - 1);
                            }
                            else if (controllerMediaPlay.Get_Current_PlayList_Index() == _del_playlist_index){
                                controllerMediaPlay.ControlPlayMedia(controllerList.Get_List().get()->Get_A_PlayList(_del_playlist_index), _del_playlist_index, 0);
                            ////////////////////////////
                            
                            }
                            viewConsole.get()->Set_Console("Deleted PlayList successfully!");
                        }
                    }
                } while (temp == NEXT_MEDIA || temp == PAUSE_RESUME_MEDIA || temp == PREV_MEDIA);
                break;
            }
            case START_PLAY:{
                char temp;
                do {
                    viewConsole.get()->Set_Console("Enter the number of PlayList to play!");
                    controllerList.Show();
                    controllerMediaPlay.Show();
                    viewConsole.get()->Show_Screen();
                    std::cin >> temp;
                    if      (temp == NEXT_MEDIA) controllerMediaPlay.ControlNextMedia();
                    else if (temp == PAUSE_RESUME_MEDIA) controllerMediaPlay.ControlPauseResumeMedia();
                    else if (temp == PREV_MEDIA) controllerMediaPlay.ControlPreviousMedia();
                    else if (temp == EXIT_RETURN) { viewConsole.get()->Set_Console("Canceled play new playlist!"); break;}
                    else if (temp == '0' || temp == '1' || temp == '2' || temp == '3' || temp == '4' || temp == '5' || temp == '6' || temp == '7' || temp == '8' || temp == '9') {
                        size_t _play_Playlist_Index = temp - '0' + (controllerList.Get_View()->Get_Page())*10;
                        if (_play_Playlist_Index >= controllerList.Get_List().get()->Get_List().size()) {
                            viewConsole.get()->Set_Console("Invalid playlist!");
                        }
                        else {
                            controllerMediaPlay.ControlPlayMedia(controllerList.Get_List().get()->Get_A_PlayList(_play_Playlist_Index),_play_Playlist_Index,0);
                        }
                    }
                } while (temp == NEXT_MEDIA || temp == PAUSE_RESUME_MEDIA || temp == PREV_MEDIA);
                break;
            }
            case PAUSE_RESUME_MEDIA:{
                controllerMediaPlay.ControlPauseResumeMedia();
                break;
            }
            case NEXT_MEDIA:{
                controllerMediaPlay.ControlNextMedia();
                break;
            }
            case PREV_MEDIA:{
                controllerMediaPlay.ControlPreviousMedia();
                break;
            }
            case EXIT_RETURN:{
                std::cout << "Exiting Program!" << std::endl;
                break;
            }
            default:{
                viewConsole.get()->Set_Console("Invalid input!");
                break;
            }
        }
    } while (cmd != EXIT_RETURN); 
}

void AppController::change_run_on_playlist_mode(){
    char cmd;
    do{
        controllerPlayList.Show();
        controllerMediaPlay.Show();
        viewConsole.get()->Show_Screen();
        std::cin >> cmd;
        switch (cmd){
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': {

                break;
            }
            case NEXT_PAGE:{
                if (controllerPlayList.Get_View()->Get_Page()*10 + 10 >= controllerPlayList.Get_PlayList().get()->Get_PlayList().size()){
                    viewConsole.get()->Set_Console("Last page already! No next page!");
                }
                else {
                    size_t temp = controllerPlayList.Get_View()->Get_Page();
                    controllerPlayList.Get_View()->Set_Page(temp + 1);
                }
                break;
            }
            case PREV_PAGE:{
                if (controllerPlayList.Get_View()->Get_Page() == 0) {
                    viewConsole.get()->Set_Console("First page already! No previous page!");
                }
                else {
                    size_t temp = controllerPlayList.Get_View()->Get_Page();
                    controllerPlayList.Get_View()->Set_Page(temp - 1);
                }
                break;
            }
            case ADD_NEW:{
                std::string temp;
                do {
                    viewConsole.get()->Set_Console("Enter directory to files/folders to add!");
                    controllerPlayList.Show();
                    controllerMediaPlay.Show();
                    viewConsole.get()->Show_Screen();
                    std::cin >> temp;
                    if      (temp == "n") controllerMediaPlay.ControlNextMedia();
                    else if (temp == "p") controllerMediaPlay.ControlPauseResumeMedia();
                    else if (temp == "b") controllerMediaPlay.ControlPreviousMedia();
                    else if (temp == "e") { viewConsole.get()->Set_Console("Canceled adding file(s)!"); break;}
                    else {
                        std::filesystem::path path(temp);
                        if (std::filesystem::is_directory(path)) {                         // Check if temp is a valid folder directory
                            controllerPlayList.Get_PlayList().get()->Add_By_Directory(path);
                            viewConsole.get()->Set_Console("Added media files in folder");
                        }
                        else if (std::filesystem::is_regular_file(path)){                  // Check if temp is a valid file
                            if (path.extension() != ".mp3"){
                                viewConsole.get()->Set_Console("Invalid file type! Only .mp3 files are allowed!");
                            }
                            else{
                                auto file = std::make_shared<File>(temp);
                                controllerPlayList.Get_PlayList().get()->Add_By_File_Path(temp);
                                viewConsole.get()->Set_Console("Added file successfully!");
                            }
                        }
                    }
                } while (temp == "n" || temp == "p" || temp == "b");
                break;
            }
            case DEL_FROM:{
                char temp;
                do {
                    viewConsole.get()->Set_Console("Enter number of above file to delete!");
                    controllerPlayList.Show();
                    controllerMediaPlay.Show();
                    viewConsole.get()->Show_Screen();
                    std::cin >> temp;
                    if      (temp == NEXT_MEDIA) controllerMediaPlay.ControlNextMedia();
                    else if (temp == PAUSE_RESUME_MEDIA) controllerMediaPlay.ControlPauseResumeMedia();
                    else if (temp == PREV_MEDIA) controllerMediaPlay.ControlPreviousMedia();
                    else if (temp == EXIT_RETURN) { viewConsole.get()->Set_Console("Canceled deleting file!"); break;}
                    else {
                        size_t _file_index = temp - '0' + controllerPlayList.Get_View()->Get_Page()*10;
                        controllerPlayList.Get_PlayList().get()->Remove_File(_file_index);
                    }
                } while (temp == NEXT_MEDIA || temp == PAUSE_RESUME_MEDIA || temp == PREV_MEDIA);
                break;
            }
            case START_PLAY:{

                break;
            }
            case PAUSE_RESUME_MEDIA:{
                controllerMediaPlay.ControlPauseResumeMedia();
                break;
            }
            case NEXT_MEDIA:{
                controllerMediaPlay.ControlNextMedia();
                break;
            }
            case PREV_MEDIA:{
                controllerMediaPlay.ControlPreviousMedia();
                break;
            }
            case EXIT_RETURN:{
                viewConsole.get()->Set_Console("Returned to list of playlists!");
                controllerPlayList.Get_View()->Reset_Page();
                break;
            }
            default:{
                viewConsole.get()->Set_Console("Invalid input!");
                break;
            }
        }
    } while (cmd != EXIT_RETURN);
}