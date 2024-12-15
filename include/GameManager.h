#include <vector>
#include "NPC.h"
#include "NPCFactory.h"
#include "Observer.h"
#include "FightTask.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <queue>
#include <mutex>
#include <thread>
class GameManager
{
private:
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<std::shared_ptr<Observer>> observers;
    std::queue<FightTask> fightQueue;
    std::mutex mutex;
    bool stopThreadsFlag = false;

public:
    ~GameManager();

    void addNPC(const std::shared_ptr<NPC> &npc);
    void addObserver(const std::shared_ptr<Observer> &observer);
    void removeObserver(const std::shared_ptr<Observer> &observer);
    static void removeNPC(const std::shared_ptr<NPC> &npc, std::vector<std::shared_ptr<NPC>> &npcs);
    static void removeNPCAsync(const std::shared_ptr<NPC> &npc, std::vector<std::shared_ptr<NPC>> &npcs, std::mutex &mutex);
    void removeDeadNPCs(std::vector<std::shared_ptr<NPC>> &npcs, std::mutex &mutex);
    void removeNPCByIndex(size_t index);
    void getNPCs(std::vector<std::shared_ptr<NPC>> &npcs) const;
    void clearNPCs();
    void printNPCList() const;
    void saveNPCsToFile(const std::string &filename) const;
    void loadNPCsFromFile(const std::string &filename);
    void startBattle(double attackRange);

    // Многопоточкаааааа

    
    void moveNPCs(std::vector<std::shared_ptr<NPC>> &npcs, std::queue<FightTask> &fightQueue, std::mutex &mutex);
    void fightNPCs(std::vector<std::shared_ptr<NPC>> &npcs, std::queue<FightTask> &fightQueue, std::vector <std::shared_ptr<Observer>> &observers, std::mutex &mutex);
    void printMap(const std::vector<std::shared_ptr<NPC>> npcs, std::mutex &mutex);
    void startAsyncBattle();

    void stopThreads();

};


class OpeningFileException : public std::runtime_error
{
    public: 
        OpeningFileException() : std::runtime_error("Error while opening file") {}
};