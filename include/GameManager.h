#include <vector>
#include "NPC.h"
#include "NPCFactory.h"
#include "Observer.h"
#include <iostream>
#include <fstream>
#include <algorithm>
class GameManager
{
private:
    std::vector<NPC *> npcs;
    std::vector<Observer *> observers;

public:
    ~GameManager();

    void addNPC(NPC *npc);
    void addObserver(Observer* observer);
    static void removeNPC(NPC *npc, std::vector<NPC *> &npcs);
    void getNPCs(std::vector<NPC *> &npcs) const;
    void clearNPCs();
    void printNPCList() const;
    void saveNPCsToFile(const std::string &filename) const;
    void loadNPCsFromFile(const std::string &filename);
    void startBattle(double attackRange);
};