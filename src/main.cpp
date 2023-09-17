#include "MyApp.hpp"

ImVec4 bg_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

int main()
{
    auto myapp = MyApp::Init("Hazel Physics VR Engine", 1720, 720, true);

    while (!myapp->ShouldClose())
    {
        myapp->BeginLoop();

        myapp->NewFrame();

        myapp->Update();

        myapp->Render(bg_color);

        myapp->EndLoop();
    }

    delete myapp;

    return 0;
}
