#pragma once
#include <GLFW/glfw3.h>
#include <unordered_map>

class InputSystem {
public:
    void update(GLFWwindow* window) {
        keys['w'] = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
        keys['a'] = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
        keys['s'] = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
        keys['d'] = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

        glfwGetCursorPos(window, &mouseX, &mouseY);
        leftClick = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
    }

    bool isPressed(char key) {
        return keys[key];
    }

     double getMouseX() const { return mouseX; }
    double getMouseY() const { return mouseY; }
    bool isLeftClick() const { return leftClick; }

private:
    std::unordered_map<char, bool> keys;
    double mouseX = 0, mouseY = 0;
    bool leftClick = false;

};
