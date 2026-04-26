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

    // Build and compile shader program
    Shader basicShader("assets/shaders/basic_color.glsl");

    Triangle tri1;
    tri1.build();

    // Vector math
    RendMath::Vec4f vec(0.0f, 0.0f, 0.0f, 0.0f);
    RendMath::Mat4f trans;
    trans = RendMath::Mat4f::translate(Mat4f(), RendMath::Vec3f(0.0f, 0.0f, 0.0f));

    float rotX = 0.0f;
    float rotY = 0.0f;
    float rotZ= 0.0f;

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
        trans = RendMath::Mat4f::translate(Mat4f(), RendMath::Vec3f(rotX, rotY, 0));
        basicShader.use();
        basicShader.setMatrix4f("transform", trans);
        tri1.mesh.drawMesh(basicShader);

        // Simple window
        ImGui::Begin("Application");
        ImGui::Text("Triangle");
        ImGui::SliderFloat("Rotation X", &rotX, -2*std::numbers::pi_v<float>, 2*std::numbers::pi_v<float>);
        ImGui::SliderFloat("Rotation Y", &rotY, -2*std::numbers::pi_v<float>, 2*std::numbers::pi_v<float>);
        ImGui::SliderFloat("Rotation Z", &rotZ, -2*std::numbers::pi_v<float>, 2*std::numbers::pi_v<float>);
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