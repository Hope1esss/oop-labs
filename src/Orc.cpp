#include "../include/Orc.h"

Orc::Orc(int x, int y, const std::string &name) : NPC(x, y, name, "Orc") {}

void Orc::interact(NPC *other)
{
    if (other->getType() == "Bear" || other->getType() == "Orc")
    {
        std::cout << name << " (" << type << ") on position (" << x << ", " << y << ") kills " << other->getName() << " (" << other->getType() << ") on position (" << other->getPosition().first << ", " << other->getPosition().second << ")!" << std::endl;
    }
}