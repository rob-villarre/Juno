#ifndef ASTEROIDS_LAYERSTACK_H
#define ASTEROIDS_LAYERSTACK_H

#include "Layer.h"

#include <vector>
#include <memory>

namespace Juno
{
    // TODO: add overlay layers
    class LayerStack
    {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(std::unique_ptr<Layer> layer);
        void PopLayer(Layer* layer);

        std::unique_ptr<Layer>& back() { return m_Layers.back(); }

        std::vector<std::unique_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
        std::vector<std::unique_ptr<Layer>>::iterator end() { return m_Layers.end(); }

        [[nodiscard]] std::vector<std::unique_ptr<Layer>>::const_iterator begin() const { return m_Layers.begin(); }
        [[nodiscard]] std::vector<std::unique_ptr<Layer>>::const_iterator end() const { return m_Layers.end(); }

    private:
        std::vector<std::unique_ptr<Layer>> m_Layers;
    };

}

#endif //ASTEROIDS_LAYERSTACK_H