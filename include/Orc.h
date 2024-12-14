#ifndef ORC_H
#define ORC_H

#include "NPC.h"

class Orc : public NPC, public std::enable_shared_from_this<Orc>
{
public:
    Orc(int x, int y, const std::string &name) : NPC(x, y, name, "Orc", 20, 10) {}
    void accept(std::shared_ptr<Visitor> visitor) override
    {
        visitor->visit(shared_from_this());
    }
};
#endif