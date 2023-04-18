#include <iostream> 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std; 


int main() {
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFW* window - glfwCreateWindow(800, 600, "this is not a window", NULL, NULL);

    if(window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1; 
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1; 
    }

    while(glfwWindowShouldClose(window)) {
        glfwPollEvents(); 

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;



}