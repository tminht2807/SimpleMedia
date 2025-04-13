#include "IController.hpp"
#pragma once

class ControllerMediaPlay : public IController {
public:
    ControllerMediaPlay(Model& m, std::shared_ptr<IView> v) : IController(m, v) {}
    ~ControllerMediaPlay() override = default;
    
    void HandleCases(size_t mode) override;

    void ControlPlayMedia();
    void ControlPlayMedia(size_t chooseFileIndex, size_t choosePlayListIndex);
    void ControlPlayMedia(size_t choosePlayListIndex);
    void ControlPauseResumeMedia();
    void ControlNextMedia();
    void ControlPreviousMedia();
};