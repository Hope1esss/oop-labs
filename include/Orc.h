#ifndef ORC_H
#define ORC_H

#include "NPC.h"

class Orc : public NPC
{
public:
    Orc(int x, int y, const std::string &name) : NPC(x, y, name, "Orc") {}
    void accept(Visitor *visitor) override
    {
        visitor->visit(this);
    }
};
#endif