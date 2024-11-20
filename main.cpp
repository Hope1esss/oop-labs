#include "include/NPCFactory.h"
#include "include/ConsoleLogger.h"
#include "include/FileLogger.h"
#include <iostream>
#include "include/GameManager.h"

int main()
{
    GameManager gameManager;

    ConsoleLogger consoleLogger;
    FileLogger fileLogger("battle.log");
    gameManager.addObserver(&consoleLogger);
    gameManager.addObserver(&fileLogger);

    gameManager.addNPC(NPCFactory::createNPC(100, 150, "Goruk", "Orc"));
    gameManager.addNPC(NPCFactory::createNPC(200, 250, "Grizzly", "Bear"));
    gameManager.addNPC(NPCFactory::createNPC(300, 350, "Chippy", "Squirrel"));
    gameManager.addNPC(NPCFactory::createNPC(120, 140, "Oleg", "Orc"));
    gameManager.addNPC(NPCFactory::createNPC(220, 230, "Krusty", "Bear"));
    gameManager.addNPC(NPCFactory::createNPC(320, 330, "Scooby", "Orc"));

    double attackRange = 500;
    gameManager.startBattle(attackRange);

    return 0;
}