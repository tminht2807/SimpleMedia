#include "../Model/Model.hpp"

#include "../View/IView.hpp"
#include "../View/ViewMediaPlay.hpp"
#include "../View/ViewPlayList.hpp"
#include "../View/ViewList.hpp"

#include "ControllerList.hpp"
#include "ControllerMediaPlay.hpp"
#include "ControllerPlayList.hpp"
#include "IController.hpp"

enum {
    PAUSE_RESUME_MEDIA = 'p',
    NEXT_MEDIA = 'n',
    PREV_MEDIA = 'b',
    NEXT_PAGE = 'k',
    PREV_PAGE = 'j',
    CHANGE_DIR = 'c'
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
    void run();
};
