#include "../Model/Model.hpp"
#include "../View/IView.hpp"
#include "IController.hpp"

class AppController {
private:
    Model model;
    std::shared_ptr<IController> controller;

public:
    AppController() : model(), controller(IController::toControllerMediaPlay(model)) {
        // Initialize the controller with the model
    }

    void run() {
        // Main loop for the application
        controller->HandleCases(0);

        char cmd;

        do {
            controller = IController::toIController(model);
            controller->updateView();
            std::cin >> cmd;

            switch (cmd) {
                case 'p': {
                    controller = IController::toControllerMediaPlay(model);
                    controller->HandleCases(2);
                    break;
                }
                case 'n': {
                    controller = IController::toControllerMediaPlay(model);
                    controller->HandleCases(2);
                    break;
                }
                case 'b': {
                    controller = IController::toControllerMediaPlay(model);
                    controller->HandleCases(3);
                    break;
                }
                case '4': {
                    controller = IController::toIController(model);
                    break;
                }
                default:
                    std::cout << "Invalid command!" << std::endl;
            }

        } while (cmd != '0');
    }
};
