#include "GLFW/glfw3.h"
#include "imgui.h"

#include <chrono>

namespace MyApp
{
    class Timer
    {
        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
            std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTimepoint;

        public:
            Timer();
            ~Timer();

        public:
            void Stop();
    };

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

    UseImGui* Init(const char* title, int width, int height, bool vsync);
    void glfw_error_callback(int error, const char* description);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

} // namespace MyA
