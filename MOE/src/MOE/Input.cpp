//
// Created by gru on 1/8/24.
//

#include "Input.h"

//#include <utility>

namespace MOE {
    std::vector<std::pair<KEYS, std::vector<std::function<void()>>>> Input::inputs;
    std::vector<InputStruct> Input::inpstructs;

    InputStruct::InputStruct(MOE::KEYS k, std::vector<std::function<void()>> f, bool p) : key(k), funcs(f), press(p){
        Input::addStruct(*this);
    }

    void Input::addStruct(InputStruct inpstruct) {
        Input::inpstructs.emplace_back(inpstruct);
    }
    void Input::SetInput(std::vector<InputStruct> inps) {
        Input::inpstructs = inps;
    }

    void Input::SetInput(std::vector<std::pair<KEYS, std::vector<std::function<void()>>>> inpfuncs) {
        Input::inputs = inpfuncs;
    }
    void Input::ProcessInput(std::vector<std::pair<KEYS, std::vector<std::function<void()>>>> inpfuncs, GLFWwindow *window) {
        for(auto inp : inpfuncs) {
            int keycode = int(inp.first);
            if(glfwGetKey(window, keycode) == 1) {
                for(auto func : inp.second) {
                    func();
                }
            }
        }
    }
    void Input::ProcessInput(GLFWwindow *window) {
        for (auto inp : Input::inpstructs) {
            int keycode = int(inp.key);
            if(glfwGetKey(window, keycode) == int(inp.press)) {
                for(auto func: inp.funcs) {
                    func();
                }
            }
        }
//        for(auto inp : Input::inputs) {
//            int keycode = int(inp.first);
//            if(glfwGetKey(window, keycode) == 1) {
//                for(auto func : inp.second) {
//                    func();
//                }
//            }
//        }
    }


}
