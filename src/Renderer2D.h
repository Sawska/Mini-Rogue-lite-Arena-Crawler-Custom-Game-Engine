#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>  

class Renderer2D {
public:
    bool init(int width = 800, int height = 600, const char* title = "ECS Game") {
        if (!glfwInit()) return false;

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) return false;

        glfwMakeContextCurrent(window);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress); // Load OpenGL funcs

        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, height, 0, -1, 1); // 2D setup

         IMGUI_CHECKVERSION();
         ImGui::CreateContext();
         ImGui_ImplGlfw_InitForOpenGL(window, true);
         ImGui_ImplOpenGL3_Init("#version 130");
    

        return true;
    }

    void drawRect(float x, float y, float w, float h) {
        glBegin(GL_QUADS);
        glColor3f(0.8f, 0.3f, 0.3f); // red-ish
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
        glEnd();
    }

    void clear() {
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void present() {
        glfwSwapBuffers(window);
    }

    void poll() {
        glfwPollEvents();
    }

    bool shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void terminate() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    GLFWwindow* getWindow() {
        return window;
    }

private:
    GLFWwindow* window = nullptr;
};

oid beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

#include <SFML/Graphics.hpp>

sf::RenderTexture sfmlTexture;
sf::Sprite sprite;
sf::Texture playerTexture;

void loadSprites() {
    if (!playerTexture.loadFromFile("assets/player.png"))
        throw std::runtime_error("Missing texture!");
    sprite.setTexture(playerTexture);
}

void drawSprite(float x, float y) {
    sprite.setPosition(x, y);
    sprite.setScale(1.0f, 1.0f);
    sprite.setColor(sf::Color::White);
    sprite.setTexture(playerTexture);
    sprite.draw(); // <- if using SFML render window
}