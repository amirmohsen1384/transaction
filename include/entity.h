#ifndef ENTITY_H
#define ENTITY_H

#include "general.h"

class Entity
{
public:
    Entity();

public:
    virtual void saveToRecord(quint64 value) const = 0;
};

#endif // ENTITY_H
