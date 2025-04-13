#pragma once
#include "../Model/Model.hpp"
#include "../View/ViewMediaPlay.hpp"

class ControllerMediaPlay  {
protected:
    Model& model;  // **Shared model reference**

    std::shared_ptr<ViewMediaPlay> centerView;
public:
    ControllerMediaPlay(Model& m, std::shared_ptr<ViewMediaPlay> v) : model(m), centerView(v) {
        // Initialize the controller with the model
    }
    ~ControllerMediaPlay() = default;

    std::shared_ptr<ViewMediaPlay> getView() {
        return centerView;
    }
    
    Model& getModel() {
        return model;
    }

    void ControlPlayMedia();
    void ControlPlayMedia(size_t chooseFileIndex, size_t choosePlayListIndex);
    void ControlPlayMedia(size_t choosePlayListIndex);
    void ControlPauseResumeMedia();
    void ControlNextMedia();
    void ControlPreviousMedia();
};