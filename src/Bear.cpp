#include "../include/Bear.h"

Bear::Bear(int x, int y, const std::string &name) : NPC(x, y, name, "Bear") {}

void Bear::interact(NPC *other)
{
    if (other->getType() == "Squirrel")
    {
        std::cout << name << " (" << type << ") on position (" << x << ", " << y << ") kills " << other->getName() << " (" << other->getType() << ") on position (" << other->getPosition().first << ", " << other->getPosition().second << ")!" << std::endl;
    }
}