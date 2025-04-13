#include "IController.hpp"
#include "ControllerList.hpp"
#include "ControllerMediaPlay.hpp"
#include "ControllerPlayList.hpp"

#include "../View/ViewList.hpp" 
#include "../View/ViewMediaPlay.hpp"
#include "../View/ViewPlayList.hpp"

std::shared_ptr<IController> IController::toControllerList(Model& _model) {
    instance.reset(new ControllerList(_model, std::make_shared<ViewList>(_model)));
    return instance;
}

std::shared_ptr<IController> IController::toControllerMediaPlay(Model& _model) {
    instance.reset(new ControllerMediaPlay(_model, std::make_shared<ViewMediaPlay>(_model)));
    return instance;
}

std::shared_ptr<IController> IController::toControllerPlayList(Model& _model) {
    instance.reset(new ControllerPlayList(_model, std::make_shared<ViewPlayList>(_model)));
    return instance;
}

std::shared_ptr<IController> IController::toIController(Model& _model) {
    instance.reset(new IController(_model, std::make_shared<IView>(_model)));
    return instance;
}

void IController::updateView() {
    centerView->ShowScreen();
}

void IController::HandleCases(size_t mode) {
    // Default implementation, can be overridden by derived classes
    std::cout << "Handling cases in IController" << std::endl;
}