#include "testTexture2D.h"
#include "../Renderer.h"
#include "../vendor/imgui/imgui.h"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>
#include "../Texture.h"
#include "../Shader.h"
#include "../Renderer.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
namespace test {


    Texture2D::Texture2D(Shader &shader,glm::mat4 &proj,glm::mat4 &view, Renderer &renderer, VertexArray &vao, IndexBuffer &ib) 
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

    Texture2D::~Texture2D()
    {
    }

    void Texture2D::onUpdate(float deltaTime)
    {
    }

    void Texture2D::onRender()
    {
        Texture texture2 = Texture("../res/textures/block2.png");
        Texture texture = Texture("../res/textures/block.png");
        texture2.Bind(0);
        texture.Bind(1);
        
        int indexes[2] = {0,1};
        m_Shader.setUniform1iv("u_Texture",indexes);
        
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

    bool Texture2D::onImGuiRender()
    {
        
        
        ImGui::Begin("Texture2DTest"); 
        ImGui::SliderFloat3("Translate A",&m_TranslationA.x,0.0,960.0);
        ImGui::SliderFloat3("Translate B",&m_TranslationB.x,0.0,960.0);
        if (ImGui::Button("Return",ImVec2(100,100))){
            ImGui::End();
            return false;
        }
        ImGui::End();
        return true;
    }
}