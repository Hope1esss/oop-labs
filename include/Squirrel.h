#ifndef SQUIRREL_H
#define SQUIRREL_H
#include "NPC.h"

class Squirrel : public NPC
{
public:
    Squirrel(int x, int y, const std::string &name) : NPC(x, y, name, "Squirrel") {}
    void accept(Visitor *visitor) override
    {
        visitor->visit(this);
    }
};
#endif