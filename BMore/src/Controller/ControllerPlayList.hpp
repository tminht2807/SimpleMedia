#include "IController.hpp"
#pragma once

class ControllerPlayList : public IController {
public:
    ControllerPlayList(Model& m, std::shared_ptr<IView> v) : IController(m, v) {}
    ~ControllerPlayList() override = default;

    void HandleCases(size_t mode) override;
};