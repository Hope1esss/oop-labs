#include "../include/NPCFactory.h"

std::shared_ptr<NPC> NPCFactory::createNPC(int x, int y, const std::string &name, const std::string &type)
{
    if (type == "Orc")
    {
        return std::make_shared<Orc>(x, y, name);
    }
    else if (type == "Squirrel")
    {
        return std::make_shared<Squirrel>(x, y, name);
    }
    else if (type == "Bear")
    {
        return std::make_shared<Bear>(x, y, name);
    }
    else
    {
        std::cerr << "Unknown NPC type: " << type << std::endl;
        return nullptr;
    }
}