#include "../Model/Model.hpp"

class IView {
public:
    virtual void displayPlaylists(const Model& model);

    virtual void ShowScreen(Model& _model);

    virtual ~IView() = default;
};