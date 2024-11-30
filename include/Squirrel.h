#ifndef SQUIRREL_H
#define SQUIRREL_H
#include "NPC.h"

class Squirrel : public NPC, public std::enable_shared_from_this<Squirrel>
{
public:
    Squirrel(int x, int y, const std::string &name) : NPC(x, y, name, "Squirrel") {}
    void accept(std::shared_ptr<Visitor> visitor) override
    {
        visitor->visit(shared_from_this());
    }
};
#endif