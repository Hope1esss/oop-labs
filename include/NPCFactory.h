#include "Orc.h"
#include "Squirrel.h"
#include "Bear.h"

class NPCFactory
{
public:
    static NPC *createNPC(const std::string &name, const std::string &type, int x, int y);
};