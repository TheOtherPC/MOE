//
// Created by gru on 1/1/24.
//

#ifndef MOE_APPLICATION_H
#define MOE_APPLICATION_H

#include <iostream>


namespace MOE {
    class Application {
    public:
        Application();

        ~Application();

        void Run();

    };
    Application* CreateApplication();
}


#endif //MOE_APPLICATION_H
