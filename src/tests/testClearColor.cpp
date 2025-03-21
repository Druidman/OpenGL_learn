#include "testClearColor.h"
#include "../Renderer.h"
#include "../vendor/imgui/imgui.h"
#include <GL/glew.h>

namespace test {


    ClearColor::ClearColor() : m_ClearColor {0.2,0.3,0.8,1.0}
    {
    }

    ClearColor::~ClearColor()
    {
        GlCall( glClearColor(0,0,0,0) );
        GlCall( glClear(GL_COLOR_BUFFER_BIT) );
    }

    void ClearColor::onUpdate(float deltaTime)
    {
    }

    void ClearColor::onRender()
    {
        GlCall( glClearColor(m_ClearColor[0],m_ClearColor[1],m_ClearColor[2],m_ClearColor[3]) );
        GlCall( glClear(GL_COLOR_BUFFER_BIT) );
    }

    bool ClearColor::onImGuiRender()
    {
        ImGui::Begin("ClearColorTest"); 
        ImGui::ColorEdit4("Clear color",m_ClearColor);
        if (ImGui::Button("Return",ImVec2(100,100))){
            ImGui::End();
            return false;
        }
        ImGui::End();
        return true;
    }
}