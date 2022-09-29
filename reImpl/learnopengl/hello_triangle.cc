#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <malloc.h>
#include <string>

#define SOURCE_BUF_SZ (258)
#define SOURCE_MAX_LINE (258)

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
};

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void readShaderSource(const std::string path, char** pSourceList)
{
    std::ifstream fin;
    fin.open(path, std::ios::in);
    if (!fin.is_open())
    {
        std::cout << "cannot find this file! " << std::endl;
    }
    char shaderSource[SOURCE_BUF_SZ] = {0};
    int i = 0;

    while (fin.getline(shaderSource, SOURCE_BUF_SZ)) {
        // std::cout << "Current Reading: " << shaderSource << std::endl;
        pSourceList[i] = (char*)malloc(SOURCE_BUF_SZ*sizeof(char));
        strcpy_s(pSourceList[i], SOURCE_BUF_SZ, shaderSource);
        i++;
    }
    /*
    for (int j = 0; j < i; j++) {
        std::cout << "GOT in pSourceList: " << pSourceList[j] << std::endl;
    }
    */
    fin.close();
}

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return -1;
    }

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Resources
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    
    // Create Vertex Buffer Object (VBO) to store a large number of vertices in GPU
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // GL_STREAM_DRAW: the data is set only once and used by GPU at most a few times
    // GL_STATIC_DRAW: the data is set only once and used many times
    // GL_DYNAMIC_DRAW: the data iss changed a lot and used many times

    // Create Vertex Shaders
    const std::string vertexShaderSourcePath = "D:/repos/research00/shaders/basicv.glsl";
    char** pVertexShaderList = (char**)malloc(SOURCE_MAX_LINE);
    readShaderSource(vertexShaderSourcePath, pShaderList);
    // std::cout << "GET VERTEX SHADER: \n" << pShaderList[0] << std::endl;
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, pVertexShaderList, NULL);
    glCompileShader(vertexShader);
    //TODO fragment shader

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        // Rendering
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}
