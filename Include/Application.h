#ifndef APPLICATION_H
#define APPLICATION_H

#include "raylib-cpp.hpp"
#include "LayerStack.h"

#include <string>
#include <memory>
#include <queue>

namespace Juno
{
    struct WindowSpecification
    {
        int Width;
        int Height;
        std::string title;
    };

    struct ApplicationSpecification
    {
        WindowSpecification WindowSpec;
    };

    class Application final
    {
    public:
        explicit Application(const ApplicationSpecification& spec);
        ~Application();

        void PushLayer(std::unique_ptr<Layer> layer);
        void PopLayer(Layer* layer);

        void PushLayerDeferred(std::unique_ptr<Layer> layer);
        void PopLayerDeferred(Layer* layer);
        void SwapLayersDeferred(Layer* oldLayer, std::unique_ptr<Layer> newLayer);

        void ProcessPendingLayers();

        void Run();

        [[nodiscard]] raylib::Window& GetWindow() { return m_Window; }
        [[nodiscard]] const raylib::Window& GetWindow() const { return m_Window; }

    private:
        ApplicationSpecification m_Specification;
        raylib::Window m_Window;
        LayerStack m_LayerStack;
        std::queue<std::unique_ptr<Layer>> m_PendingLayerPushes;
        std::queue<Layer*> m_PendingLayerPops;
    };
}

#endif //APPLICATION_H