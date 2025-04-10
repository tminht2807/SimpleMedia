#include "../View/IView.hpp"
#include "../Model/Model.hpp"

class ControllerMediaPlay;
class ControllerPlayList;
class ControllerList;

class ViewMediaPlay;
class ViewPlayList;
class ViewList;

class IController {
protected:
    Model& model;  // **Shared model reference**

    std::shared_ptr<IView> centerView;

    inline static std::unique_ptr<IController> instance = nullptr;  // Singleton instance

public:
    IController(Model& m, std::shared_ptr<IView> v) : model(m), centerView(v) {}

    virtual void updateView(Model& _model);

    virtual void HandleCases();

    // **Switch Controller Type While Keeping Shared Model**
    static IController* toControllerList(Model& _model);

    static IController* toControllerMediaPlay(Model& _model);

    static IController* toControllerPlayList(Model& _model);

    // **Get the current instance of IController**
    static IController* getInstance();

    Model& getModel() {
        return model;
    }

    virtual ~IController() = default;
};
