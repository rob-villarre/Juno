#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <vector>
#include <raylib-cpp.hpp>

#include "Component.h"

class IEntity
{
public:
    explicit IEntity(const raylib::Vector2 position, const float heading) : m_Position(position), m_Heading(heading) {};
    virtual ~IEntity() = default;

    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnRender() = 0;

    template<std::derived_from<Component> T, typename... Args>
    void AddComponent(Args&&... args)
    {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->SetOwner(this);
        m_Components.push_back(std::move(component));
    }

    template<std::derived_from<Component> T>
    T* GetComponent()
    {
        for (const auto& component : m_Components)
        {
            if (auto* casted = dynamic_cast<T*>(component.get()))
            {
                return casted;
            }
        }
        return nullptr;
    }

    raylib::Vector2 GetPosition() const { return m_Position; }
    float GetHeading() const { return m_Heading; }

protected:
    raylib::Vector2 m_Position;
    float m_Heading;
    std::vector<std::unique_ptr<Component>> m_Components;
};

#endif //ENTITY_H