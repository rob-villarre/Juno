#ifndef COMMAND_H
#define COMMAND_H

#include "IEntity.h"

namespace Juno
{
    class Command
    {
    public:
        Command() = default;
        virtual ~Command() = default;

        virtual void Execute(IEntity& actor, float deltaTime) = 0;
    };
}

#endif COMMAND_H