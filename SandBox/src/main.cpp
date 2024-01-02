#include <iostream>
#include "MOE.h"

class SandBox : public MOE::Application {
public:
    SandBox() {}
    ~SandBox() {}
};

MOE::Application* MOE::CreateApplication() {
    return new SandBox();
}
