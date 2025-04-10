#include "IController.hpp"

class ControllerList : public IController {
public:
    ControllerList(Model& m, std::shared_ptr<IView> v) : IController(m, v) {}
};