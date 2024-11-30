#include "../include/GameManager.h"
#include "../include/BattleVisitor.h"
#include <random>
#include <ctime>
#include <vector>

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

void GameManager::removeNPCByIndex(size_t index)
{
    if (index < npcs.size())
    {
        removeNPC(npcs[index], npcs);
    }
    else
    {
        std::cerr << "Invalid index: " << index << std::endl;
    }
}

void GameManager::addObserver(Observer *observer)
{
    observers.push_back(observer);
}

void GameManager::removeObserver(Observer *observer)
{
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
    {
        delete *it;
        observers.erase(it);
    }
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

void GameManager::getNPCs(std::vector<NPC *> &npcs) const
{
    npcs = this->npcs;
}

void GameManager::clearNPCs()
{
    npcs.clear();
}
void GameManager::printNPCList() const
{
    if (npcs.empty())
    {
        std::cout << "NPC List is empty" << std::endl;
    }
    else
    {
        std::cout << "NPC List:" << std::endl;
        for (const auto &npc : npcs)
        {
            npc->printInfo();
        }
    }
}

void GameManager::saveNPCsToFile(const std::string &filename) const
{
    std::ofstream outputFile(filename);
    if (!outputFile)
    {
        throw OpeningFileException();
    }

    for (const auto &npc : npcs)
    {
        outputFile << npc->getPosition().first << " "
                   << npc->getPosition().second << " "
                   << npc->getName() << " "
                   << npc->getType() << std::endl;
    }

    outputFile.close();
    std::cout << "NPCs saved to file: " << filename << std::endl;
}

void GameManager::loadNPCsFromFile(const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile)
    {
        throw OpeningFileException();
    }

    int x, y;
    std::string name, type;

    while (inputFile >> x >> y >> name >> type)
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
    int AFKBattleCounter = 0;
    BattleVisitor::notify("Battle started with attack range: " + std::to_string(attackRange), observers);

    while (npcs.size() > 1)
    {
        bool anyBattleOccurred = false;

        std::vector<NPC *> toRemove;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(npcs.begin(), npcs.end(), gen);
        
        for (size_t i = 0; i < npcs.size(); i += 2)
        {
            if (i + 1 < npcs.size())
            {
                NPC *npc1 = npcs[i];
                NPC *npc2 = npcs[i + 1];

                BattleVisitor visitor(npc1, attackRange, npcs, observers, toRemove);
                npc2->accept(&visitor);

                if ((std::find(toRemove.begin(), toRemove.end(), npc1) != toRemove.end()) || (std::find(toRemove.begin(), toRemove.end(), npc2) != toRemove.end()))
                {
                    anyBattleOccurred = true;
                }
            }
        }

        for (NPC *npc : toRemove)
        {
            removeNPC(npc, npcs);
        }

        if (!anyBattleOccurred)
        {
            AFKBattleCounter++;
            if (AFKBattleCounter > 50)
            {
                break;
            }
        }
        else
        {
            AFKBattleCounter = 0;
        }
    }

    // Вывод результата
    if (npcs.size() == 1)
    {
        BattleVisitor::notify("Battle is over. The winner is: " + npcs[0]->getName() + " (" + npcs[0]->getType() + ")", observers);
    }
    else if (npcs.size() > 1)
    {

        BattleVisitor::notify("Battle is over. Friendship wins! No winner could be determined. Remaining NPCs:", observers);
        for (const auto &npc : npcs)
        {
            BattleVisitor::notify(npc->getName() + " (" + npc->getType() + ")", observers);
        }
    }
    else
    {
        BattleVisitor::notify("Battle is over. No winner could be determined. All NPCs are dead", observers);
    }
}