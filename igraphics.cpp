#include "main.h"
#include "color.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace iG {
    int iWindowWidth;
    int iWindowHeight;
    int iWindowX;
    int iWindowY;
    int iScreenWidth;
    int iScreenHeight;
    double iMouseDir;
    double iMouseX;
    double iMouseY;
    double iClearR;
    double iClearG;
    double iClearB;

    void iClear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
    }

    void iResize(GLFWwindow* window, int width, int height) {
        iWindowWidth = width;
        iWindowHeight = height;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
    }

    void iInitialize(GLFWwindow* window, const char* title) {
        if (!window) {
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            throw std::runtime_error("Failed to initialize GLEW");
        }

        glfwGetFramebufferSize(window, &iWindowWidth, &iWindowHeight);
        iScreenWidth = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
        iScreenHeight = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

        glViewport(0, 0, iWindowWidth, iWindowHeight);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, iWindowWidth, 0.0, iWindowHeight, -1.0, 1.0);

        iClear();

        glfwSetFramebufferSizeCallback(window, iResize);
        glfwSetWindowTitle(window, title);

        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glLineWidth(2.0);
    }

    void iSetClearColor(double r, double g, double b) {
        iClearR = r;
        iClearG = g;
        iClearB = b;
        glClearColor(iClearR / 255.0, iClearG / 255.0, iClearB / 255.0, 1.0);
    }

    // Add additional functions and event handlers as needed
}
