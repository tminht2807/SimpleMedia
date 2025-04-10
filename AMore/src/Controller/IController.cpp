#include "IController.hpp"
#include "ControllerList.hpp"
#include "ControllerMediaPlay.hpp"
#include "ControllerPlayList.hpp"

#include "../View/ViewList.hpp" 
#include "../View/ViewMediaPlay.hpp"
#include "../View/ViewPlayList.hpp"

IController* IController::toControllerList(Model& _model) {
    instance.reset(new ControllerList(_model, std::make_shared<ViewList>()));
    return instance.get();
}

IController* IController::toControllerMediaPlay(Model& _model) {
    instance.reset(new ControllerMediaPlay(_model, std::make_shared<ViewMediaPlay>()));
    return instance.get();
}

IController* IController::toControllerPlayList(Model& _model) {
    instance.reset(new ControllerPlayList(_model, std::make_shared<ViewPlayList>()));
    return instance.get();
}

IController* IController::toIController(Model& _model) {
    instance.reset(new IController(_model, std::make_shared<IView>()));
    return instance.get();
}

void IController::updateView(Model& _model) {
    centerView->ShowScreen(_model);
}