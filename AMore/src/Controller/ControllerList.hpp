#include "IController.hpp"
#pragma once

class ControllerList : public IController {
public:
    ControllerList(Model& m, std::shared_ptr<IView> v) : IController(m, v) {}
    ~ControllerList() override = default;
};