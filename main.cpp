#include "include/ConsoleLogger.h"
#include "include/FileLogger.h"
#include "include/GameManager.h"
#include <iostream>

int main()
{
    GameManager gameManager;
    ConsoleLogger consoleLogger;
    gameManager.addObserver(&consoleLogger);
    std::cout << "Hello! This is Balagur Fate 3 dungeon editor. Let's create some NPC and start battle with them" << std::endl;
    gameManager.addNPC(NPCFactory::createNPC(20, 25, "Миша", "Bear"));
    gameManager.addNPC(NPCFactory::createNPC(40, 50, "Глупый Орк", "Orc"));
    gameManager.addNPC(NPCFactory::createNPC(15, 20, "Алексей", "Bear"));
    gameManager.addNPC(NPCFactory::createNPC(70, 80, "Белка", "Squirrel"));
    gameManager.addNPC(NPCFactory::createNPC(300, 400, "Осторожная белка", "Squirrel"));
    gameManager.addNPC(NPCFactory::createNPC(30, 40, "Тупой Орк", "Orc"));

    std::cout << "Here we go! Look at the list of NPCs:" << std::endl;
    gameManager.printNPCList();

    std::cout << "Okay, we'll use consoleLogger to watch battle. Try to add 1 NPC to this party! Remember, that there are only 'Orc', 'Bear' and 'Squirrel'" << std::endl;
    int x, y;
    std::string name, type;
    std::cout << "Enter your NPC in format <x y name type>: ";
    std::cin >> x >> y >> name >> type;
    NPC* userNPC = NPCFactory::createNPC(x, y, name, type);
    std::cout << "This is your NPC: ";
    userNPC->printInfo();

    double userAttackRange;
    std::cout << "Enter attack range of NPCs and watch their battle: ";
    std::cin >> userAttackRange;

    gameManager.startBattle(userAttackRange);

    std::cout << "Thanks for testing Balagur Fate 3 dungeon editor. Goodbye!" << std::endl;
    return 0;
}