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
                size_t playList_Index_choose = cmd - '0' + (controllerList.Get_View().get()->Get_Page())*10;
                if (playList_Index_choose + 1   >   controllerList.Get_List().get()->Get_List().size()) {
                    viewConsole.get()->Set_Console("Invalid playlist!");
                }
                else {
                    controllerPlayList.Set_PlayList(controllerList.Get_List().get()->Get_A_PlayList(playList_Index_choose),playList_Index_choose);
                    viewConsole.get()->Set_Console("Entered a Playlist!");
                    controllerList.Get_View().get()->Reset_Page();
    
                    change_run_on_playlist_mode();
                }
                break;
            }
            case NEXT_PAGE:{
                if (controllerList.Get_View().get()->Get_Page()*10 + 10 > controllerList.Get_List().get()->Get_List().size()){
                    viewConsole.get()->Set_Console("Last page already! No next page!");
                }
                else controllerList.Get_View().get()->Set_Page(controllerList.Get_View().get()->Get_Page() + 1);
                break;
            }
            case PREV_PAGE:{
                if (controllerList.Get_View().get()->Get_Page() == 0) {
                    viewConsole.get()->Set_Console("First page already! No previous page!");
                }
                else controllerList.Get_View().get()->Set_Page(controllerList.Get_View().get()->Get_Page() - 1);
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
                    else if (temp == "e") break;
                    else {
                        // CHeck if temp is a valid directory
                        if () {///////////////////////////////////////
                            viewConsole.get()->Set_Console("Invalid directory!");
                        }
                        else{
                            viewConsole.get()->Set_Console("Changed directory successfully!");
                            controllerList.Get_List().get()->Get_A_PlayList(0).get()->Clear_PlayList();

                            temp = "Current directory: " + temp; 
                            controllerList.Get_List().get()->Get_A_PlayList(0).get()->Set_PlayList_Name(temp);
                            //////////////////////////////////////////
                        } 
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
                    else if (temp == "e") break;
                    else {
                        if (!controllerList.Get_List().get()->Add_PlayList(temp)) 
                            viewConsole.get()->Set_Console("Playlist with this name already exists!");
                        else viewConsole.get()->Set_Console("Added PlayList succesfully!");
                    }
                } while (temp == "n" || temp == "p" || temp == "b");
                break;
            }
            case DEL_FROM:{
                viewConsole.get()->Set_Console("Enter PlayList number on screen to delete it!");
                controllerList.Show();
                controllerMediaPlay.Show();
                viewConsole.get()->Show_Screen();
                size_t temp;
                std::cin >> temp;
                controllerList.Get_List().get()->Remove_PlayList(temp);
                viewConsole.get()->Reset_Console();
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
                break;
            }
            default:{
                viewConsole.get()->Set_Console("Invalid input!");
                break;
            }
        }
    } while (cmd != EXIT_RETURN);
}