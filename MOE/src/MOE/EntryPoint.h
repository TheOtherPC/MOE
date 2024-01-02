//
// Created by gru on 1/1/24.
//

#ifndef MOE_ENTRYPOINT_H
#define MOE_ENTRYPOINT_H

#include "Application.h"

extern MOE::Application* MOE::CreateApplication();

int main(int argc, char** argv) {
    auto app = MOE::CreateApplication();
    app->Run();
    delete app;
}


#endif //MOE_ENTRYPOINT_H
