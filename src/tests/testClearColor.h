#ifndef TEST_COLOR_H
#define TEST_COLOR_H
#include "Test.h"
namespace test {

    class ClearColor : public Test
    {
        public:
            ClearColor();
            ~ClearColor();
            void onUpdate(float deltaTime) override;
            void onRender() override;
            bool onImGuiRender() override;
        private:
            float m_ClearColor[4];
    };

}

#endif