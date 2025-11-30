#ifndef ASTEROIDS_LAYER_H
#define ASTEROIDS_LAYER_H

#include <string>
#include <memory>

namespace Juno
{
    class Layer
    {
    public:
        explicit Layer(std::string name);
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnRender() {}
        // virtual void OnEvent() {}


    protected:
        std::string m_Name;
    };
}

#endif //ASTEROIDS_LAYER_H