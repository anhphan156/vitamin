#include <math.h>

#include "renderer/stdinc.h"
#include "math/math.h"
#include "renderer/shader.h"

void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(){
    glfwInit();
    /* glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); */
    /* glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); */
    /* glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API); // Set the client API */
    /* glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API); */
    glfwWindowHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND); 
    /* glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); */

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewInit();
    /* if(err != GLEW_OK){ */
    /*     std::cout << err  << std::endl; */
    /* } */
    /* std::cout << glGetString(GL_VERSION) << std::endl; */

    float positions[] = {
        -.5f, -.5f, 1.0f, 0.0f, 0.0f, 0.0, 0.0,
        .5f, .5f, 0.0f, 0.0f, 1.0f, 1.0, 1.0,
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0, 1.0,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0, 0.0
    };

    unsigned int indices[6] = {
        0, 1, 2,
        0, 3, 1
    };

    unsigned int buffer;
    GLCall(glGenBuffers(1, &buffer));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    GLCall(glBufferData(GL_ARRAY_BUFFER, 28 * sizeof(float), positions, GL_STATIC_DRAW));

    unsigned int ibo;
    GLCall(glGenBuffers(1, &ibo));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)0));

    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(2 * sizeof(float))));

    GLCall(glEnableVertexAttribArray(2));
    GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(5 * sizeof(float))));

    char vert[61] = "/home/backspace/data/dev/miso/resources/shaders/color.vert";
    char frag[61] = "/home/backspace/data/dev/miso/resources/shaders/color.frag";
    int shader_program = create_shader_program(vert, frag);
    GLCall(glUseProgram(shader_program));

    float rotation[4];

    while (!glfwWindowShouldClose(window))
    {
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        GLCall(int loc = glGetUniformLocation(shader_program, "u_r"));
        if(loc != -1){
            double t = glfwGetTime();
            mkRotation2x2(t, rotation);
            GLCall(glUniformMatrix2fv(loc, 1, GL_FALSE, rotation));
        }

        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    GLCall(GLCall(glDeleteBuffers(1, &buffer)));
    GLCall(glDeleteBuffers(1, &ibo));
    GLCall(glDeleteProgram(shader_program));
    GLCall(glfwTerminate());

    return 0;
}

void error_callback(int error, const char* description)
{
    printf("Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
