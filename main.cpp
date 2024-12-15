#include "include/ConsoleLogger.h"
#include "include/FileLogger.h"
#include "include/GameManager.h"
#include "include/NPCFactory.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void showMenu()
{
    std::cout << "---Balagur Fate 3 dungeon editor---" << std::endl;
    std::cout << "1. Add NPC (manually)" << std::endl;
    std::cout << "2. Add random NPC by type" << std::endl;
    std::cout << "3. Add N random NPCs" << std::endl;
    std::cout << "4. Load NPCs from file" << std::endl;
    std::cout << "5. Save NPCs to file" << std::endl;
    std::cout << "6. Remove NPC by index" << std::endl;
    std::cout << "7. Clear NPC List" << std::endl;
    std::cout << "8. Print NPC List" << std::endl;
    std::cout << "9. Enter NPC attack range" << std::endl;
    std::cout << "10. Start Battle" << std::endl;
    std::cout << "11. Start Async Battle" << std::endl;
    std::cout << "12. Exit" << std::endl;
}

std::shared_ptr<NPC> addNPCManually()
{
    int typeChoise = 0;
    std::cout << "Choose NPC type: " << std::endl;
    std::cout << "1. Orc" << std::endl;
    std::cout << "2. Squirrel" << std::endl;
    std::cout << "3. Bear" << std::endl;
    std::cin >> typeChoise;

    int x, y;
    std::string name;
    std::cout << "Enter NPC name: ";
    std::cin >> name;

    std::cout << "Enter NPC position in format <x y>: ";
    std::cin >> x >> y;
    while (x < 0 || x > 500 || y < 0 || y > 500)
    {
        std::cerr << "Invalid position for NPC. Position must be in range 0 <= x <= 500; 0 <= y <= 500. Try again: " << std::endl;
        std::cin >> x >> y;
    }

    switch (typeChoise)
    {
    case 1:
        return NPCFactory::createNPC(x, y, name, "Orc");

    case 2:
        return NPCFactory::createNPC(x, y, name, "Squirrel");

    case 3:
        return NPCFactory::createNPC(x, y, name, "Bear");
    }

    return nullptr;
}

std::shared_ptr<NPC> addRandomNPCByType()
{
    int typeChoise = 0;
    std::cout << "Choose NPC type: " << std::endl;
    std::cout << "1. Orc" << std::endl;
    std::cout << "2. Squirrel" << std::endl;
    std::cout << "3. Bear" << std::endl;
    std::cin >> typeChoise;

    std::srand(std::time(0));
    int x = std::rand() % 501;
    int y = std::rand() % 501;
    int NPCId = std::rand() % 250001;

    switch (typeChoise)
    {
    case 1:
        return NPCFactory::createNPC(x, y, "Orc" + std::to_string(NPCId), "Orc");

    case 2:
        return NPCFactory::createNPC(x, y, "Squirrel" + std::to_string(NPCId), "Squirrel");

    case 3:
        return NPCFactory::createNPC(x, y, "Bear" + std::to_string(NPCId), "Bear");
    }

    return nullptr;
}

std::vector<std::shared_ptr<NPC>> addRandomNPCs(int count)
{
    std::vector<std::shared_ptr<NPC>> npcs;
    std::srand(std::time(0));
    for (int i = 0; i < count; i++)
    {

        int x = std::rand() % 501;
        int y = std::rand() % 501;
        int NPCId = std::rand() % 250001;
        int NPCType = std::rand() % 3 + 1;

        switch (NPCType)
        {
        case 1:
            npcs.push_back(NPCFactory::createNPC(x, y, "Orc" + std::to_string(NPCId), "Orc"));
            break;
        case 2:
            npcs.push_back(NPCFactory::createNPC(x, y, "Squirrel" + std::to_string(NPCId), "Squirrel"));
            break;
        case 3:
            npcs.push_back(NPCFactory::createNPC(x, y, "Bear" + std::to_string(NPCId), "Bear"));
            break;
        default:
            break;
        }
    }

    std::cout << "NPCs generated successfully" << std::endl;
    return npcs;
}

int main()
{
    GameManager gameManager;
    auto fileLogger = std::make_shared<FileLogger>("log.txt");
    gameManager.addObserver(fileLogger);

    auto consoleLogger = std::make_shared<ConsoleLogger>();
    gameManager.addObserver(consoleLogger);

    int choise = 0;
    double attackRange = 0.0;

    while (choise != 12)
    {
        showMenu();
        if (!(std::cin >> choise))
        {
            std::cerr << "Invalid input. Enter a number from 1 to 11" << std::endl;
            std::cin.clear();
            continue;
        }

        try
        {
            switch (choise)
            {
            case 1:
            {
                std::shared_ptr<NPC> npc = addNPCManually();
                if (npc)
                {
                    gameManager.addNPC(npc);
                }
                std::cout << "NPC added successfully" << std::endl;
                break;
            }
            case 2:
            {
                std::shared_ptr<NPC> npc = addRandomNPCByType();
                if (npc)
                {
                    gameManager.addNPC(npc);
                }
                std::cout << "NPC added successfully" << std::endl;
                break;
            }
            case 3:
            {
                std::vector<std::shared_ptr<NPC>> npcs;
                int count = 0;
                std::cout << "Enter the number of NPCs to generate: ";
                std::cin >> count;
                npcs = addRandomNPCs(count);
                for (auto npc : npcs)
                {
                    gameManager.addNPC(npc);
                }
                std::cout << "NPCs generated and added successfully" << std::endl;
                break;
            }
            case 4:
            {
                std::string filename;
                std::cout << "Enter the file name(it should be in the same folder as main.cpp): ";
                std::cin >> filename;
                gameManager.loadNPCsFromFile(filename);
                break;
            }

            case 5:
            {
                std::string filename;
                std::cout << "Enter the file name: ";
                std::cin >> filename;
                gameManager.saveNPCsToFile(filename);
                break;
            }

            case 6:
            {
                size_t index = 0;
                std::cout << "Here is the list of NPCs: " << std::endl;
                gameManager.printNPCList();
                std::cout << "Enter the index of the NPC you want to remove: ";
                std::cin >> index;
                gameManager.removeNPCByIndex(index);
                std::cout << "NPC removed successfully" << std::endl;
                break;
            }

            case 7:
            {
                gameManager.clearNPCs();
                std::cout << "NPCs cleared successfully" << std::endl;
                break;
            }

            case 8:
            {
                gameManager.printNPCList();
                break;
            }

            case 9:
            {
                std::cout << "Enter the attack range: ";
                std::cin >> attackRange;
                std::cout << "Attack range set to " << attackRange << std::endl;
                break;
            }

            case 10:
            {
                if (attackRange == 0.0)
                {
                    std::cerr << "Attack range is not set. Enter attack range: " << std::endl;
                    std::cin >> attackRange;
                    std::cout << "Attack range set to " << attackRange << std::endl;
                }
                std::cout << "Starting battle..." << std::endl;
                gameManager.startBattle(attackRange);
                break;
            }

            case 11:
            {
                gameManager.clearNPCs();
                std::vector<std::shared_ptr<NPC>> npcs = addRandomNPCs(50);
                for (auto npc : npcs)
                {
                    gameManager.addNPC(npc);
                }
                std::cout << "Starting async battle..." << std::endl;
                gameManager.startAsyncBattle();
                break;
            }
            case 12:
            {
                std::cout << "Exiting program..." << std::endl;
                break;
            }

            default:
                std::cout << "Invalid Option" << std::endl;
                break;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    return 0;
}