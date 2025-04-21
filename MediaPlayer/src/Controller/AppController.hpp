#include "../Model/List.hpp"

#include "../View/IView.hpp"
#include "../View/ViewMediaPlay.hpp"
#include "../View/ViewPlayList.hpp"
#include "../View/ViewList.hpp"

#include "ControllerList.hpp"
#include "ControllerMediaPlay.hpp"
#include "ControllerPlayList.hpp"

enum {
    PAUSE_RESUME_MEDIA = 'p',
    NEXT_MEDIA = 'n',
    PREV_MEDIA = 'b',

    NEXT_PAGE = 'k',
    PREV_PAGE = 'j',

    CHANGE_DIR = 'c',
    ADD_NEW = 'a',
    DEL_FROM = 'd',

    START_PLAY = 's',

    EXIT_RETURN = 'e'
};

class AppController {
private:    
    // std::shared_ptr<List> list;

    std::shared_ptr<IView> viewConsole;

    ControllerMediaPlay controllerMediaPlay;
    ControllerPlayList controllerPlayList;
    ControllerList controllerList;

    uint8_t Program_Mode; // 0 - List; 1 - PlayList
public:
    AppController(std::shared_ptr<List> _list):
        // list(_list),
        controllerList(_list),
        Program_Mode(0)
    {
        std::thread shown(&AppController::UpdateView, this);
        shown.detach(); // Run in background
    }

    void run();
    void change_run_on_playlist_mode();

    void UpdateView();
};
