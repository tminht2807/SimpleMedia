#include "IController.hpp"
#pragma once

class ControllerMediaPlay : public IController {
public:
    ControllerMediaPlay(Model& m, std::shared_ptr<IView> v) : IController(m, v) {}
    ~ControllerMediaPlay() override = default;
};