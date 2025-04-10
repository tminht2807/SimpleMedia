#include "IController.hpp"

class ControllerPlayList : public IController {
public:
    ControllerPlayList(Model& m, std::shared_ptr<IView> v) : IController(m, v) {}
};