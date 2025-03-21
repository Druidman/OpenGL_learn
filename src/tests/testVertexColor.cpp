#include "testVertexColor.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/glm/gtc/matrix_transform.hpp"

namespace test {



    VertexColor::VertexColor(Shader &shader,glm::mat4 &proj,glm::mat4 &view, Renderer &renderer, VertexArray &vao, IndexBuffer &ib)
    : m_TranslationA(0,0,0), 
    m_TranslationB(0,0,0),
    m_Shader(shader),
    m_Proj(proj),
    m_View(view),
    m_Vao(vao),
    m_Renderer(renderer),
    m_Ib(ib)
    {
    }

    VertexColor::~VertexColor()
    {
    }

    void VertexColor::onUpdate(float deltaTime)
    {
    }

    void VertexColor::onRender()
    {
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0),m_TranslationA);
            glm::mat4 MVP = m_Proj * m_View * model;
            m_Shader.setUniformMat4f("u_MVP",MVP);

            m_Renderer.Draw(m_Vao,m_Ib,m_Shader);
        }
        
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0),m_TranslationB);
            glm::mat4 MVP = m_Proj * m_View * model;
            m_Shader.setUniformMat4f("u_MVP",MVP);

            m_Renderer.Draw(m_Vao,m_Ib,m_Shader);
        }
    }

    bool VertexColor::onImGuiRender()
    {
        ImGui::Begin("VertexColorTest"); 
        ImGui::SliderFloat3("Translate A",&m_TranslationA.x,0.0,960.0);
        ImGui::SliderFloat3("Translate B",&m_TranslationB.x,0.0,960.0);
        if (ImGui::Button("Return",ImVec2(100,100))){
            ImGui::End();
            return false;
        }
        ImGui::End();
        return true;
        
        return false;
    }
}
