#ifndef ENTITY_H
#define ENTITY_H


class Entity
{
public:
    Entity() {}
    virtual ~Entity() {}
    virtual void Init()=0;
    virtual void Update()=0;
    virtual void Render()=0;
};

#endif // ENTITY_H
