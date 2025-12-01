#ifndef COMPONENT_H
#define COMPONENT_H

class IEntity;

class Component
{
public:
    virtual ~Component() = default;

    void SetOwner(IEntity* owner) { m_Owner = owner; }
    [[nodiscard]] IEntity* GetOwner() const { return m_Owner; }

private:
    IEntity* m_Owner = nullptr;
};

#endif //COMPONENT_H