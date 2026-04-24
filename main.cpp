#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <iostream>

#include "include/math/Vec2.hpp"
#include "include/renderer/Shader.hpp"
#include "include/renderer/Triangle.hpp"

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}


int main(int, char**) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        // Init failed
        return 1;
    }
    // GL + GLSL version
    const char* glsl_version = "#version 460";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with graphics context
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());
    GLFWwindow* window = glfwCreateWindow((int)(1280*main_scale), (int)(720*main_scale), "DuoEngine", nullptr, nullptr);
    if (!window) {
        // Window failed
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return 1;
    };
    glfwSwapInterval(1);    // Enable vsync
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable keyboard controls
    
    // Set style
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    io.ConfigDpiScaleFonts = true;

    // Set platform/renderer backend
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // OpenGL basics
    // Rectangle vertices
    // float vertices[] = {
    //     // positions        // colors
    //      0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Top right
    //      0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Bottom right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // Bottom left
    //     -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f   // Top left
    // };

    // unsigned int indices[] = {
    //     0, 1, 3,    // 1st triangle
    //     1, 2, 3     // 2nd triangle
    // };

    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // // Vertex array object
    // unsigned int VAO;
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);

    // // Vertex buff object
    // unsigned int VBO;
    // glGenBuffers(1, &VBO);  // Creates one buffer object
    //  // Binding the VBO buffer means any buffer calls made on the GL_ARRAY_BUFFER target will configure VBO.
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // // We copy the rectangle vertex data into the buffer's memory. 
    // // 1st param: buffer type we want to copy data into; this is why we just bound VBO.
    // // 2nd param: size of data in bytes. 
    // // 3rd param: Actual data
    // // 4th param: How we want the GPU to manage the given data.
    // // GL_STATIC_DRAW suggests the data is set once and used many times.
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Build and compile shader program
    Shader basicShader("assets/shaders/basic_color.glsl");

    // Tell OpenGL how to interpret vertex data
    // Each vertex attribute takes its data from memory managed by a VBO, and which VBO
    // it takes from is determined by the VBO currently bound to GL_ARRAY_BUFFER when calling glVertexAttribPointer.

    // 1st param: Specifies which vertex attribute we want to configure.
    // Since we specified the location of the position vertex attribute in our vertex shader
    // with layout (location = 0), we pass in 0.
    // 2nd param: Size of the vertex attribute. It's a vec3, so 3 values.
    // 3rd param: Type of data. vec1/2/3/4 in GLSL consists of floating point values
    // 4th param: If the data should be normalized. Not important right now, so false
    // 5th param: Stride - the space between consecutive vertex attributes.
    // 6th param: Offset of where the position data begins in the buffer.
    // Position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // // Color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    Triangle tri1;
    tri1.build();

    while (!glfwWindowShouldClose(window)) {

        // Poll and handle events (inputs, window resize, etc)
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Render triangle
        tri1.mesh.drawMesh(basicShader);

        // Simple window
        ImGui::Begin("Application");
        ImGui::Text("Test");
        ImGui::End();

        // Render
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}