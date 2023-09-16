#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui.h>

namespace MyApp
{
    class UseGLFW
    {
        private:
            const char* m_title;
            int m_width;
            int m_height;
            bool m_vsync;
            GLFWwindow* m_window;

        public:
            UseGLFW(const char* title, int width, int height, bool vsync);
            ~UseGLFW();

        public:
            bool ShouldClose();
            void CloseLoop();
            void GetFBSize(int* width, int* height);
            GLFWwindow* GetWindow();
            void BeginLoop();
            void EndLoop();

        private:
            void Init();
    };



    class UseImGui : public UseGLFW
    {
        private:
            const char* m_glsl_version = "#version 130";
            ImVec4 m_clear_color;

        public:
            UseImGui(const char* title, int width, int height, bool vsync);
            ~UseImGui();

        public:
            void NewFrame();
            void Update();
            void Render(ImVec4 clear_color);
            void Shutdown();

        private:
            void Init();
    };



    void glfw_error_callback(int error, const char* description);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}
