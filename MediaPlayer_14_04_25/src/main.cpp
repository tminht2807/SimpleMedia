#include "Controller/AppController.hpp"


int main() {
    List list;
    AppController TheApp(std::make_shared<List>(list));
    TheApp.run();

    return 0;
}