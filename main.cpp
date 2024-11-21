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

    gameManager.loadNPCsFromFile("npcs.txt");

    double attackRange = 500.0;
    gameManager.startBattle(attackRange);

    return 0;
}