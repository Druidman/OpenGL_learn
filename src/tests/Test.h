#ifndef TEST_H
#define TEST_H
namespace test {

    class Test
    {
        public:
            Test() {}
            virtual ~Test(){}
            virtual void onUpdate(float deltaTime){}
            virtual void onRender(){}
            virtual bool onImGuiRender(){return true;}
    };

}

#endif