#include "../Model/Model.hpp"
#include "../View/IView.hpp"
#include "IController.hpp"

class AppController{
private:
    Model model;
    IController* controller;
public:
    AppController() : model(), controller(IController::toIController(model)) {
        // Initialize the controller with the model
    }
    
    void run() {
        // Main loop for the application
        char cmd;
        do {
            controller->updateView(model);
            std::cin >> cmd;

            switch (cmd) {
                
                default:
                    std::cout << "Invalid command!" << std::endl;
            }

            controller->updateView(model);
        } while (cmd != 'q');
    }

};
