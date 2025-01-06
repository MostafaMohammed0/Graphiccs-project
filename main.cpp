#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "main.h"
#include "color.h"
#include "chess_board.h"
#include "chess_team.h"

ChessTeam teamWhite(__WHITE__), teamBlack(__BLACK__);
ChessBoard board;

void Logic()
{
}

void windowSetup(GLFWwindow* window)
{
    // Get screen width and height from the primary monitor
    int screenWidth = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
    int screenHeight = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

    // Set window size to screen dimensions
    glfwSetWindowSize(window, screenWidth, screenHeight);
    
    // Set window position to (0, 0)
    glfwSetWindowPos(window, 0, 0);

    // Set clear color to black (assuming GLFW doesn't do this automatically)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black color (RGBA format)
}



void setup()
{
    board.setUnit(120);
    board.setWidth(8 * board.getUnit());
    board.setHeight(8 * board.getUnit());
    board.setPoint(glfwGetVideoMode(glfwGetPrimaryMonitor())->width / 2 - board.getWidth() / 2,
                   glfwGetVideoMode(glfwGetPrimaryMonitor())->height / 2 - board.getHeight() / 2);
    board.setBoard();
}

int main(int argc, char* argv[])
{
    srand(time(NULL));

    // Initialize GLFW
    if (!glfwInit())
    {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Chess", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        return -1;
    }

    // Setup window
    windowSetup(window);
    setup();

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        // Your rendering code here

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
