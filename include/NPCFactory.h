#ifndef NPCFACTORY_H
#define NPCFACTORY_H
#include "Orc.h"
#include "Squirrel.h"
#include "Bear.h"

class NPCFactory
{
public:
    static std::shared_ptr<NPC> createNPC(int x, int y, const std::string &name, const std::string &type);
};
#endif