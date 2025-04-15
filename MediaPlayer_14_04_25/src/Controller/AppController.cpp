#include "AppController.hpp"

void AppController::run(){
    // Main loop for the application
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
                controllerPlayList.Set_PlayList(controllerList.Get_List().get()->Get_A_PlayList(playList_Index_choose));
                controllerPlayList.Set_Current_PlayList_Index(playList_Index_choose);
                viewConsole.get()->Set_Console("Entered a Playlist!");
                controllerList.Get_View().get()->Reset_Page();

                change_run_on_playlist_mode();
            }
            case NEXT_PAGE:{
                controllerList.Get_View().get()->Set_Page(controllerList.Get_View().get()->Get_Page() + 1);
            }
            case PREV_PAGE:{
                if (controllerList.Get_View().get()->Get_Page() == 0) 

            }

            case EXIT_RETURN:{
                std::cout << "Exiting Program!" << std::endl;
            }
            default:{
                viewConsole.get()->Set_Console("Invalid input!");
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

            }
            case EXIT_RETURN:{
                std::cout << "Returned to list of playlists!" << std::endl;
            }
            default:{
                viewConsole.get()->Set_Console("Invalid input!");
            }
        }

    } while (cmd != EXIT_RETURN);
}