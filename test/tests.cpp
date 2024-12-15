#include "../include/ConsoleLogger.h"
#include "../include/FileLogger.h"
#include "../include/GameManager.h"
#include "gtest/gtest.h"
#include <string>
#include <cstdio>

TEST(NPCTests, NPCCreationTest)
{
    std::shared_ptr<NPC> npc = NPCFactory::createNPC(0, 2, "Орк", "Orc");
    ASSERT_EQ(npc->getPosition().first, 0);
    ASSERT_EQ(npc->getPosition().second, 2);
    ASSERT_EQ(npc->getName(), "Орк");
    ASSERT_EQ(npc->getType(), "Orc");
}

TEST(NPCTests, NPCSaveAndLoadTest)
{
    std::shared_ptr<NPC> npc1 = NPCFactory::createNPC(0, 0, "Орк", "Orc");
    std::shared_ptr<NPC> npc2 = NPCFactory::createNPC(1, 1, "Медведь", "Bear");
    std::shared_ptr<NPC> npc3 = NPCFactory::createNPC(2, 2, "Белка", "Squirrel");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);
    gameManager.addNPC(npc3);

    gameManager.saveNPCsToFile("npcs.txt");

    std::vector<std::shared_ptr<NPC>> npcs;

    gameManager.clearNPCs();
    gameManager.loadNPCsFromFile("npcs.txt");
    gameManager.getNPCs(npcs);

    ASSERT_EQ(npcs.size(), 3);
    ASSERT_EQ(npcs[0]->getPosition().first, 0);
    ASSERT_EQ(npcs[0]->getName(), "Орк");
    ASSERT_EQ(npcs[2]->getName(), "Белка");
    ASSERT_EQ(npcs[1]->getPosition().second, 1);
}

TEST(BattleTests, OrcAndOrcBattleTest)
{
    std::shared_ptr<NPC> npc1 = NPCFactory::createNPC(0, 0, "Орк1", "Orc");
    std::shared_ptr<NPC> npc2 = NPCFactory::createNPC(1, 1, "Орк2", "Orc");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<std::shared_ptr<NPC>> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 0);
}

TEST(BattleTests, OrcAndBearBattleTest)
{
    std::shared_ptr<NPC> npc1 = NPCFactory::createNPC(0, 0, "Орк", "Orc");
    std::shared_ptr<NPC> npc2 = NPCFactory::createNPC(1, 1, "Медведь", "Bear");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<std::shared_ptr<NPC>> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Орк");
    EXPECT_EQ(npcs[0]->getType(), "Orc");
}

TEST(BattleTests, OrcAndSquirrelBattleTest)
{
    std::shared_ptr<NPC> npc1 = NPCFactory::createNPC(0, 0, "Орк", "Orc");
    std::shared_ptr<NPC> npc2 = NPCFactory::createNPC(1, 1, "Белка", "Squirrel");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<std::shared_ptr<NPC>> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 2);
}

TEST(BattleTests, BearAndBearBattleTest)
{
    std::shared_ptr<NPC> npc1 = NPCFactory::createNPC(0, 0, "Медведь1", "Bear");
    std::shared_ptr<NPC> npc2 = NPCFactory::createNPC(1, 1, "Медведь2", "Bear");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<std::shared_ptr<NPC>> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 2);
}

TEST(BattleTests, BearAndSquirrelBattleTest)
{
    std::shared_ptr<NPC> npc1 = NPCFactory::createNPC(0, 0, "Медведь", "Bear");
    std::shared_ptr<NPC> npc2 = NPCFactory::createNPC(1, 1, "Белка", "Squirrel");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<std::shared_ptr<NPC>> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Медведь");
    EXPECT_EQ(npcs[0]->getType(), "Bear");
}

TEST(BattleTests, SquirrelAndSquirrelBattleTest)
{
    std::shared_ptr<NPC> npc1 = NPCFactory::createNPC(0, 0, "Белка1", "Squirrel");
    std::shared_ptr<NPC> npc2 = NPCFactory::createNPC(1, 1, "Белка2", "Squirrel");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<std::shared_ptr<NPC>> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 2);
    for (auto npc : npcs)
    {
        if (npc->getName() == "Белка1")
        {
            EXPECT_EQ(npc->getName(), "Белка1");
        }
        else
        {
            EXPECT_EQ(npc->getName(), "Белка2");
        }
    }
}

TEST(BattleTests, BattleWithSmallAttackRangeTest)
{
    std::shared_ptr<NPC> npc1 = NPCFactory::createNPC(0, 0, "Орк1", "Orc");
    std::shared_ptr<NPC> npc2 = NPCFactory::createNPC(50, 50, "Орк2", "Orc");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 25.0;

    gameManager.startBattle(attackRange);

    std::vector<std::shared_ptr<NPC>> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 2);

    for (auto npc : npcs)
    {
        if (npc->getName() == "Орк1")
        {
            EXPECT_EQ(npc->getName(), "Орк1");
        }
        else
        {
            EXPECT_EQ(npc->getName(), "Орк2");
        }
    }
}

TEST(LoggerTests, LogToFileTest)
{

    GameManager gameManager;

    std::shared_ptr<NPC> npc1 = NPCFactory::createNPC(0, 0, "Орк", "Orc");
    std::shared_ptr<NPC> npc2 = NPCFactory::createNPC(50, 50, "Медведь", "Bear");

    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    std::string logFile = "test.log";

    auto fileLogger = std::make_shared<FileLogger>(logFile);
    gameManager.addObserver(fileLogger);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<std::string> lines;
    fileLogger->getLogs(lines, logFile);

    EXPECT_EQ(lines.size(), 3);
    EXPECT_EQ(lines[0], "Battle started with attack range: " + std::to_string(attackRange));
    EXPECT_EQ(lines[1], "Орк (Orc) killed Медведь (Bear)");
    EXPECT_EQ(lines[2], "Battle is over. The winner is: Орк (Orc)");

    std::remove(logFile.c_str());
}

TEST(AsyncBattleTests, NPCMovementTest)
{
    GameManager gameManager;

    auto npc1 = NPCFactory::createNPC(50, 50, "Орк", "Orc");

    gameManager.addNPC(npc1);

    auto posX = npc1->getPosition().first, posY = npc1->getPosition().second;


    gameManager.startAsyncBattle(1);

    auto currentPosX = npc1->getPosition().first, currentPosY = npc1->getPosition().second;

    EXPECT_NE(posX, currentPosX);
    EXPECT_NE(posY, currentPosY);
}

TEST(AsyncBattleTests, NoBattleOnBigDistanceTest)
{
    GameManager gameManager;

    auto npc1 = NPCFactory::createNPC(0, 0, "Орк", "Orc");
    auto npc2 = NPCFactory::createNPC(500, 500, "Медведь", "Bear");

    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    gameManager.startAsyncBattle(1);

    std::vector<std::shared_ptr<NPC>> npcs;
    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 2);
}

TEST(AsyncBattleTests, AsyncBattleLogToFileTest)
{
    GameManager gameManager;

    auto npc1 = NPCFactory::createNPC(5, 5, "Орк", "Orc");
    auto npc2 = NPCFactory::createNPC(10, 10, "Медведь", "Bear");

    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    std::string logFile = "async_test.log";

    auto fileLogger = std::make_shared<FileLogger>(logFile);
    gameManager.addObserver(fileLogger);

    double attackRange = 15.0;

    gameManager.startAsyncBattle(1);

    std::vector<std::string> lines;
    fileLogger->getLogs(lines, logFile);

    EXPECT_GE(lines.size(), 2);
    EXPECT_EQ(lines[0], "Battle started!");

    std::remove(logFile.c_str());
}