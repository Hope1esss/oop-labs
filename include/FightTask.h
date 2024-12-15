#include "NPC.h"
#include <memory>

struct FightTask
{
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
    bool isDuel;

    FightTask() {}
    FightTask(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, bool isDuel)
        : attacker(attacker), defender(defender), isDuel(isDuel) {}
};