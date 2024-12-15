#ifndef BEAR_H
#define BEAR_H

#include "NPC.h"

class Bear : public NPC, public std::enable_shared_from_this<Bear>
{
public:
    Bear(int x, int y, const std::string &name) : NPC(x, y, name, "Bear", 5, 10, true) {}
    void accept(std::shared_ptr<Visitor> visitor) override
    {
        visitor->visit(shared_from_this());
    }
};
#endif