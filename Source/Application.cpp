#include "Application.h"

namespace Juno
{
    Application::Application(const ApplicationSpecification& spec)
        : m_Specification(spec), m_Window(spec.WindowSpec.Width, spec.WindowSpec.Height, spec.WindowSpec.title)
    { }

    Application::~Application()
    = default;

    void Application::PushLayer(std::unique_ptr<Layer> layer)
    {
        m_LayerStack.PushLayer(std::move(layer));
    }

    void Application::PopLayer(Layer* layer)
    {
        m_LayerStack.PopLayer(layer);
    }

    void Application::SwapLayersDeferred(Layer* oldLayer, std::unique_ptr<Layer> newLayer)
    {
        PopLayerDeferred(oldLayer);
        PushLayerDeferred(std::move(newLayer));
    }

    void Application::PushLayerDeferred(std::unique_ptr<Layer> layer)
    {
        m_PendingLayerPushes.push(std::move(layer));
    }

    void Application::PopLayerDeferred(Layer* layer)
    {
        m_PendingLayerPops.push(layer);
    }

    void Application::ProcessPendingLayers()
    {
        while(!m_PendingLayerPops.empty())
        {
            Layer* layer = m_PendingLayerPops.front();
            m_LayerStack.PopLayer(layer);
            m_PendingLayerPops.pop();
        }

        while(!m_PendingLayerPushes.empty())
        {
            m_LayerStack.PushLayer(std::move(m_PendingLayerPushes.front()));
            m_PendingLayerPushes.pop();
        }
    }

    void Application::Run()
    {
        while (!m_Window.ShouldClose())
        {
            const float deltaTime = m_Window.GetFrameTime();

            ProcessPendingLayers();

            for (const auto& layer : m_LayerStack)
            {
                layer->OnUpdate(deltaTime);
            }

            BeginDrawing();
            for (const auto& layer : m_LayerStack)
            {
                layer->OnRender();
            }
            EndDrawing();
        }
    }
}