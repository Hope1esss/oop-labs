#include <vector>
#include "NPC.h"
#include "NPCFactory.h"
#include "Observer.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
class GameManager
{
private:
    std::vector<NPC *> npcs;
    std::vector<Observer *> observers;

public:
    ~GameManager();

    void addNPC(NPC *npc);
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    static void removeNPC(NPC *npc, std::vector<NPC *> &npcs);
    void removeNPCByIndex(size_t index);
    void getNPCs(std::vector<NPC *> &npcs) const;
    void clearNPCs();
    void printNPCList() const;
    void saveNPCsToFile(const std::string &filename) const;
    void loadNPCsFromFile(const std::string &filename);
    void startBattle(double attackRange);
};


class OpeningFileException : public std::runtime_error
{
    public: 
        OpeningFileException() : std::runtime_error("Error while opening file") {}
};