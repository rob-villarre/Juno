#ifndef LAYER_H
#define LAYER_H

#include <string>

namespace Juno
{
    class Layer
    {
    public:
        explicit Layer(std::string name);
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        // virtual void OnEvent() {}


    protected:
        std::string m_Name;
    };
}

#endif //LAYER_H