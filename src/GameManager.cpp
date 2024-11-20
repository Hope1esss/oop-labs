#include "../include/GameManager.h"
#include "../include/BattleVisitor.h"
#include <random>
#include <ctime>

GameManager::~GameManager()
{
    for (auto npc : npcs)
    {
        delete npc;
    }
    npcs.clear();
}

void GameManager::addNPC(NPC *npc)
{
    npcs.push_back(npc);
}

void GameManager::addObserver(Observer *observer)
{
    observers.push_back(observer);
}

void GameManager::removeNPC(NPC *npc, std::vector<NPC *> &npcs)
{
    auto it = std::find(npcs.begin(), npcs.end(), npc);
    if (it != npcs.end())
    {
        delete *it;
        npcs.erase(it);
    }
}

void GameManager::printNPCList() const
{
    std::cout << "List of NPCs:" << std::endl;
    for (const auto &npc : npcs)
    {
        npc->printInfo();
    }
}

void GameManager::saveNPCsToFile(const std::string &filename) const
{
    std::ofstream outputFile(filename);
    if (!outputFile)
    {
        std::cerr << "Error while opening file to save NPCs: " << filename << std::endl;
        return;
    }

    for (const auto &npc : npcs)
    {
        outputFile << npc->getName() << " "
                   << npc->getType() << " "
                   << npc->getPosition().first << " "
                   << npc->getPosition().second << std::endl;
    }

    outputFile.close();
    std::cout << "NPCs saved to file: " << filename << std::endl;
}

void GameManager::loadNPCsFromFile(const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile)
    {
        std::cerr << "Error while opening file to load NPCs: " << filename << std::endl;
        return;
    }

    int x, y;
    std::string name, type;

    while (inputFile >> name >> type >> x >> y)
    {
        NPC *npc = NPCFactory::createNPC(x, y, name, type);
        if (npc)
        {
            addNPC(npc);
        }
        else
        {
            std::cerr << "Error creating NPC: (" << name << ", " << type << ", " << x << ", " << y << ")" << std::endl;
        }
    }

    inputFile.close();
    std::cout << "NPCs loaded from file: " << filename << std::endl;
}

void GameManager::startBattle(double attackRange)
{
    std::shuffle(npcs.begin(), npcs.end(), std::default_random_engine(std::time(0)));

    for (size_t i = 0; i < npcs.size(); i += 2)
    {
        if (i + 1 < npcs.size())
        {
            NPC *npc1 = npcs[i];
            NPC *npc2 = npcs[i + 1];

            if (npc1 && npc2)
            {
                BattleVisitor visitor(npc1, attackRange, npcs, observers);
                npc2->accept(&visitor);

                npcs.erase(std::remove(npcs.begin(), npcs.end(), nullptr), npcs.end());
            }
        }
    }

    std::cout << "Battle ended" << std::endl;
    printNPCList();
    saveNPCsToFile("npcs.txt");
}