#include <vector>
#include "NPC.h"
#include "NPCFactory.h"
#include <iostream>
#include <fstream>
#include <algorithm>
class GameManager
{
private:
    std::vector<NPC *> npcs;

public:
    ~GameManager();

    void addNPC(NPC *npc);
    void removeNPC(NPC *npc);
    void printNPCList() const;
    void saveNPCsToFile(const std::string &filename) const;
    void loadNPCsFromFile(const std::string &filename);
    void startBattle(double attackRange);
};