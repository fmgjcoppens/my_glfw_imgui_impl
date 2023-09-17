#include "MyApp.hpp"

namespace MyApp
{

    Timer::Timer()
    {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }
    
    Timer::~Timer()
    {
        Stop();
    }

    void Timer::Stop()
    {
        m_EndTimepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end   = std::chrono::time_point_cast<std::chrono::microseconds>(m_EndTimepoint).time_since_epoch().count();
        auto duration  = end - start;
        double miliseconds = duration * 0.001;
        std::cout << "Game loop duration: " << duration << " μs (" << miliseconds << " ms)\n";
    }

    UseGLFW::UseGLFW(const char* title, int width, int height, bool vsync)
    {
        std::cerr << "UseGLFW constructor called with title = " << title << ",  width = " << width << ", height = " << height << " and VSync = " << vsync << std::endl;
        m_title = title;
        m_width = width;
        m_height = height;
        m_vsync = vsync;
        Init();
    }

    UseGLFW::~UseGLFW()
    {
        std::cerr << "UseGLFW destructor called" << std::endl;
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    bool UseGLFW::ShouldClose()
    {
        return glfwWindowShouldClose(m_window);
    }

    void UseGLFW::CloseLoop()
    {
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    }

    void UseGLFW::GetFBSize(int* width, int* height)
    {
        glfwGetFramebufferSize(m_window, width, height);
    }

    GLFWwindow* UseGLFW::GetWindow()
    {
        return m_window;
    }

    void UseGLFW::BeginLoop()
    {
        glfwPollEvents();
    }

    void UseGLFW::EndLoop()
    {
        glfwSwapBuffers(m_window);
    }

    void UseGLFW::Init()
    {
        if (!glfwInit()) throw std::runtime_error("GLFW failed to initialize.");

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
        if (m_window == nullptr) throw std::runtime_error("GLFW window failed to initialize.");

        glfwMakeContextCurrent(m_window);

        // Set callbacks for the current window
        glfwSetErrorCallback(MyApp::glfw_error_callback);
        glfwSetKeyCallback(m_window, MyApp::key_callback);

        if (m_vsync)
        {
            glfwSwapInterval(1); // Enable vsync
        }
    }

    UseImGui::UseImGui(const char* title, int width, int height, bool vsync) :
        UseGLFW(title,  width,  height,  vsync)
    {
        std::cerr << "UseImGui constructor called" << std::endl;
        Init();
    }

    UseImGui::~UseImGui()
    {
        std::cerr << "UseImGui destructor called" << std::endl;
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UseImGui::NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void UseImGui::Update() // Here is the actual UI defined.
    {
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // A small window just to quit the application
        ImGui::Begin("Exit application");
        if (ImGui::Button("Quit")) CloseLoop();
        ImGui::End();

        // A viewport window
        ImGui::Begin("Viewport");
        ImGui::End();

        ImGui::End();
    }

    void UseImGui::Render(ImVec4 clear_color)
    {
        ImGui::Render();

        int display_w, display_h;
        GetFBSize(&display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        m_clear_color = clear_color;
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UseImGui::Init()
    {
        // // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // This does not behave properly in i3wm!

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(GetWindow(), true);
        ImGui_ImplOpenGL3_Init(m_glsl_version);

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Load Fonts
        ImFont* f_noto = io.Fonts->AddFontFromFileTTF("/usr/share/fonts/noto/NotoSans-Regular.ttf", 22.0f);
        IM_ASSERT(f_noto != nullptr);
    }

    UseImGui* Init(const char* title, int width, int height, bool vsync)
    {
        return new UseImGui("Hazel Physics VR Engine", 1720, 720, true);
    }

    void glfw_error_callback(int error, const char* description)
    {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if ((key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
