#include "../include/NPCFactory.h"

NPC *NPCFactory::createNPC(const std::string &name, const std::string &type, int x, int y)
{
    if (type == "Orc")
    {
        return new Orc(x, y, name);
    }
    else if (type == "Squirrel")
    {
        return new Squirrel(x, y, name);
    }
    else if (type == "Bear")
    {
        return new Bear(x, y, name);
    }
    else
    {
        std::cerr << "Unknown NPC type: " << type << std::endl;
        return nullptr;
    }
}