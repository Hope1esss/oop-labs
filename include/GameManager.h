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
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;

public:
    ~GameManager();

    void addNPC(const std::shared_ptr<NPC> &npc);
    void addObserver(const std::shared_ptr<Observer> &observer);
    void removeObserver(const std::shared_ptr<Observer> &observer);
    static void removeNPC(const std::shared_ptr<NPC> &npc, std::vector<std::shared_ptr<NPC>> &npcs);
    void removeNPCByIndex(size_t index);
    void getNPCs(std::vector<std::shared_ptr<NPC>> &npcs) const;
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