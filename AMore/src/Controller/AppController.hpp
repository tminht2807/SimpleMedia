#include "../Model/Model.hpp"

#include "../View/IView.hpp"
#include "../View/ViewMediaPlay.hpp"
#include "../View/ViewPlayList.hpp"
#include "../View/ViewList.hpp"

#include "ControllerList.hpp"
#include "ControllerMediaPlay.hpp"
#include "ControllerPlayList.hpp"
#include "IController.hpp"

#define PLAY_CONTROLER (char[]){'p', 'n', 'b'}


enum {
    PAUSE_RESUME_MEDIA = 'p',
    NEXT_MEDIA = 'n',
    PREVIOUS_MEDIA = 'b',
    PLAY_FROM_CURRENT_DIRECTORY = '1',
    PLAY_MEDIA_IN_CURRENT_PLAYLIST = '2',
    PLAY_PLAYLIST = '3',
    SHOW_CURRENT_DIRECTORY = '4',
    SHOW_PLAYLIST_FROM_MEDIA_LIBRARY = '5',
    SHOW_MEDIA_LIBRARY = '6',
    DELETE_PLAYLIST_FROM_MEDIA_LIBRARY = '7',
    ADD_PLAYLIST_TO_MEDIA_LIBRARY = '8',
    ADD_TO_PLAYLIST = 'a',
    REMOVE_FROM_PLAYLIST = 'r',
    EXIT_OR_RETURN = '0',
    CHANGE_CURRENT_DIRECTORY = 'c'
};

class AppController {
private:
    Model model;
    
    ControllerMediaPlay controllerMediaPlay;
    ControllerPlayList controllerPlayList;
    ControllerList controllerList;
    IController icontroller;
public:

    AppController() : model(), controllerMediaPlay(model, std::make_shared<ViewMediaPlay>(model)), 
                      controllerPlayList(model, std::make_shared<ViewPlayList>(model)), 
                      controllerList(model, std::make_shared<ViewList>(model)),
                      icontroller(model, std::make_shared<IView>(model)) {
        // Initialize the controller with the model
    }
    void PlayMediaInCurrentPlayList();
    void PlayMediaInAPlayList();
    
    void run();
};
