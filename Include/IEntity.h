#ifndef ENTITY_H
#define ENTITY_H

class IEntity
{
public:
    IEntity() = default;
    virtual ~IEntity() = default;

    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnRender() = 0;
};

#endif //ENTITY_H