#include "MyApp.hpp"

ImVec4 bg_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

int main()
{
    MyApp::UseImGui* myimgui = new MyApp::UseImGui("Hazel Physics VR Engine", 1720, 720, true);

    while (!myimgui->ShouldClose())
    {
        myimgui->BeginLoop();

        myimgui->NewFrame();

        myimgui->Update();

        myimgui->Render(bg_color);

        myimgui->EndLoop();
    }

    delete myimgui;
    return 0;
}
