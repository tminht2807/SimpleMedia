#pragma once
#include "../View/IView.hpp"
#include "../Model/Model.hpp"

// class ControllerMediaPlay;
// class ControllerPlayList;
// class ControllerList;

// class ViewMediaPlay;
// class ViewPlayList;
// class ViewList;

class IController {
protected:
    Model& model;  // **Shared model reference**

    std::shared_ptr<IView> centerView;

    inline static std::shared_ptr<IController> instance = nullptr;  // Singleton instance

public:
    IController(Model& m, std::shared_ptr<IView> v) : model(m), centerView(v) {}

    void updateView();

    virtual void HandleCases(size_t mode);

    // **Switch Controller Type While Keeping Shared Model**
    static std::shared_ptr<IController> toControllerList(Model& _model);

    static std::shared_ptr<IController> toControllerMediaPlay(Model& _model);

    static std::shared_ptr<IController> toControllerPlayList(Model& _model);

    static std::shared_ptr<IController> toIController(Model& _model);

    virtual ~IController() = default;
};
