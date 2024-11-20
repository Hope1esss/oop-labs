#include "../include/GameManager.h"
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

void GameManager::removeNPC(NPC *npc)
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
        NPC *npc = NPCFactory::createNPC(name, type, x, y);
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

