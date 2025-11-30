#include "LayerStack.h"

#include <algorithm>

namespace Juno
{
    LayerStack::~LayerStack()
    {
        for (const auto& layer : m_Layers)
        {
            layer->OnDetach();
        }
        m_Layers.clear();
    };

    void LayerStack::PushLayer(std::unique_ptr<Layer> layer)
    {
        m_Layers.emplace_back(std::move(layer));
        m_Layers.front()->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        const auto it = std::ranges::find_if(m_Layers,
                                       [layer](const std::unique_ptr<Layer>& pLayer) { return pLayer.get() == layer; });

        if (it != m_Layers.end())
        {
            (*it)->OnDetach();
            m_Layers.erase(it);
        }
    }
}