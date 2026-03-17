#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    /* Width, Height, Window name, Fullscreen, ? */
    GLFWwindow* window = glfwCreateWindow(800, 800, "Hi", NULL, NULL);
    if (window == NULL) {
        std::cout << "failed to do job. poo\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    /* Load glad */
    gladLoadGL();

    /* Bottom left of window to top right */
    glViewport(0, 0, 800, 800);

    /* Prepare to clear colour and give it another */
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    /* Execute prepared color buffer */
    glClear(GL_COLOR_BUFFER_BIT);
    /* Swap frame with buffer */
    glfwSwapBuffers(window);

    /* Constant while loop until close is it */
    while(!glfwWindowShouldClose(window)) {
        /* Processing polled events on window constantly */
        glfwPollEvents();
    }

    /* deallocation? */
    glfwDestroyWindow(window);
    /* terminate glfw instance */
    glfwTerminate();
    return 0;
}