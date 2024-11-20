#ifndef BEAR_H
#define BEAR_H

#include "NPC.h"

class Bear : public NPC
{
public:
    Bear(int x, int y, const std::string &name) : NPC(x, y, name, "Bear") {}
    void accept(Visitor *visitor) override
    {
        visitor->visit(this);
    }
};
#endif