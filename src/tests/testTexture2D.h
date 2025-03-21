#ifndef TEST_TEXTURE2D_H
#define TEST_TEXTURE2D_H
#include "Test.h"
#include "../vendor/glm/glm.hpp"
#include "../Shader.h"
#include "../Renderer.h"
#include "../VertexArray.h"
#include "../IndexBuffer.h"
namespace test {

    class Texture2D : public Test
    {
        public:
            Texture2D(Shader &shader,glm::mat4 &proj,glm::mat4 &view, Renderer &renderer, VertexArray &vao, IndexBuffer &ib);
            ~Texture2D();
            void onUpdate(float deltaTime) override;
            void onRender() override;
            bool onImGuiRender() override;
        private:
            Shader &m_Shader;
            glm::vec3 m_TranslationA;
            glm::vec3 m_TranslationB;
            glm::mat4 &m_Proj;
            glm::mat4 &m_View;
            Renderer &m_Renderer;
            VertexArray &m_Vao;
            IndexBuffer &m_Ib;
    };

}

#endif