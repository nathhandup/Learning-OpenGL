#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

/* Window becomes normalized, so x = [-1, 1]
    and y = [-1, 1] */

int main() {
    /* Initialize GLFW */
    glfwInit();

    /* Tell GLFW what version of OpenGL we are using */
    /* In this case we are using OpenGL 3.3 */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    /* Tell GLFW we are using the CORE profile */
    /* So, we only have the modern functions */
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Datatype GLfloat is sa fe as it has predefined datasizes.*/
    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
    };

    GLuint indices[] = {
        0, 3, 5, // lower left triangle
        3, 2, 4, // lower right triangle
        5, 4, 1 // upper triangle
    };

    /* Width, Height, Window name, Fullscreen, ? */
    GLFWwindow* window = glfwCreateWindow(800, 800, "Hi", NULL, NULL);
    /* Error checking */
    if (window == NULL) {
        std::cout << "failed to do job. poo\n";
        glfwTerminate();
        return -1;
    }
    
    /* Introduces window into the current context */
    glfwMakeContextCurrent(window);

    /* Load glad so OpenGL is configured */
    gladLoadGL();

    /* Bottom left of window to top right */
    glViewport(0, 0, 800, 800);

    /* GL version of an unsigned integer */
    /* Create vertex shader objext*/
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    /* Attaches vertex shader source to vertex shader object */
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    /* Compiles vertex shader to machine code */
    glCompileShader(vertexShader);

    /* GL version of an unsigned integer */
    /* Create fragment shader object and get reference */
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    /* Attach fragment shader source to fragment shader object */
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    /* Compile vertex shader to machine code */
    glCompileShader(fragmentShader);

    /* To use these shaders, we have to wrap them in a shader program. */
    /* Create shader program object and get reference */
    GLuint shaderProgram = glCreateProgram();
    /* Attach to shader program*/
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    /* Link all shaders together into one singular program */
    glLinkProgram(shaderProgram);

    /* Safe to delete, already linked in program. */
    /* They are useless now.*/
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    /* Vertex array object & Vertex buffer object */
    /* These are reference containers */
    GLuint VAO, VBO, EBO;
    /* MAKE SURE TO GENERATE VAO BEFORE VBO */
    /* Generate VAO and VBO with only 1 object each*/
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    /* make VAO current vertex array object by binding it */
    /* Binding means we create a certain object the current one. */
    glBindVertexArray(VAO);
    /* Bind VBO by specifying it's a gl_array_buffer */
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    /* Store vertices in buffer */
    /* stream means modify once and used multiple times */
    /* static means modified once and used many times */
    /* dynamic means modified modified multiple times, used many times */
    /* draw, read or copy.*/
    /* Basically, configuring vertex attribute so opengl knows how to read VBO */
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    /* position, how many values per vertex, type of value, integers, ? */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    /* Enable vertex attribute so openGL knows to use it */
    glEnableVertexAttribArray(0);

    /* Bind both VBO and VAO to 0 so that we dont modify them*/
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    /* Prepare to clear colour and give it another */
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    /* Execute prepared color buffer */
    glClear(GL_COLOR_BUFFER_BIT);
    /* Swap frame with buffer */
    glfwSwapBuffers(window);

    /* Constant while loop until close is it */
    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.07f,0.13f,0.17f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        /* Processing polled events on window constantly */
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    /* deallocation? */
    glfwDestroyWindow(window);
    /* terminate glfw instance */
    glfwTerminate();
    return 0;
}