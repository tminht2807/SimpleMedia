#include "Model/Model.hpp"
#include "View/IView.hpp"
#include "Controller/IController.hpp"

int main() {
    Model The_model;
    std::shared_ptr<IView> The_view = std::make_shared<IView>();
    IController* controller = IController::getInstance();
    controller->HandleCases();
    controller->updateView(The_model);
    return 0;
}