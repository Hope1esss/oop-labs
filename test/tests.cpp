#include "../include/ConsoleLogger.h"
#include "../include/FileLogger.h"
#include "../include/GameManager.h"
#include "gtest/gtest.h"
#include <string>

TEST(NPCTests, NPCCreationTest)
{
    NPC *npc = NPCFactory::createNPC(0, 2, "Орк", "Orc");
    ASSERT_EQ(npc->getPosition().first, 0);
    ASSERT_EQ(npc->getPosition().second, 2);
    ASSERT_EQ(npc->getName(), "Орк");
    ASSERT_EQ(npc->getType(), "Orc");
    delete npc;
}

TEST(NPCTests, NPCSaveAndLoadTest)
{
    NPC *npc1 = NPCFactory::createNPC(0, 0, "Орк", "Orc");
    NPC *npc2 = NPCFactory::createNPC(1, 1, "Медведь", "Bear");
    NPC *npc3 = NPCFactory::createNPC(2, 2, "Белка", "Squirrel");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);
    gameManager.addNPC(npc3);

    gameManager.saveNPCsToFile("npcs.txt");

    std::vector<NPC *> npcs;

    gameManager.clearNPCs();
    gameManager.loadNPCsFromFile("npcs.txt");
    gameManager.getNPCs(npcs);

    ASSERT_EQ(npcs.size(), 3);
    ASSERT_EQ(npcs[0]->getPosition().first, 0);
    ASSERT_EQ(npcs[0]->getName(), "Орк");
    ASSERT_EQ(npcs[2]->getName(), "Белка");
    ASSERT_EQ(npcs[1]->getPosition().second, 1);

    delete npc1;
    delete npc2;
    delete npc3;
}

TEST(BattleTests, OrcAndOrcBattleTest)
{
    NPC *npc1 = NPCFactory::createNPC(0, 0, "Орк1", "Orc");
    NPC *npc2 = NPCFactory::createNPC(1, 1, "Орк2", "Orc");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<NPC *> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 0);
}

TEST(BattleTests, OrcAndBearBattleTest)
{
    NPC *npc1 = NPCFactory::createNPC(0, 0, "Орк", "Orc");
    NPC *npc2 = NPCFactory::createNPC(1, 1, "Медведь", "Bear");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<NPC *> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Орк");
    EXPECT_EQ(npcs[0]->getType(), "Orc");
}

TEST(BattleTests, OrcAndSquirrelBattleTest)
{
    NPC *npc1 = NPCFactory::createNPC(0, 0, "Орк", "Orc");
    NPC *npc2 = NPCFactory::createNPC(1, 1, "Белка", "Squirrel");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<NPC *> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 2);
}

TEST(BattleTests, BearAndBearBattleTest)
{
    NPC *npc1 = NPCFactory::createNPC(0, 0, "Медведь1", "Bear");
    NPC *npc2 = NPCFactory::createNPC(1, 1, "Медведь2", "Bear");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<NPC *> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 2);
}

TEST(BattleTests, BearAndSquirrelBattleTest)
{
    NPC *npc1 = NPCFactory::createNPC(0, 0, "Медведь", "Bear");
    NPC *npc2 = NPCFactory::createNPC(1, 1, "Белка", "Squirrel");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<NPC *> npcs;

    gameManager.getNPCs(npcs);

    EXPECT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Медведь");
    EXPECT_EQ(npcs[0]->getType(), "Bear");
}

TEST(BattleTests, SquirrelAndSquirrelBattleTest)
{
    NPC *npc1 = NPCFactory::createNPC(0, 0, "Белка1", "Squirrel");
    NPC *npc2 = NPCFactory::createNPC(1, 1, "Белка2", "Squirrel");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<NPC *> npcs;

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
    NPC *npc1 = NPCFactory::createNPC(0, 0, "Орк1", "Orc");
    NPC *npc2 = NPCFactory::createNPC(50, 50, "Орк2", "Orc");

    GameManager gameManager;
    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    double attackRange = 25.0;

    gameManager.startBattle(attackRange);

    std::vector<NPC *> npcs;

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

    NPC *npc1 = NPCFactory::createNPC(0, 0, "Орк", "Orc");
    NPC *npc2 = NPCFactory::createNPC(50, 50, "Медведь", "Bear");

    gameManager.addNPC(npc1);
    gameManager.addNPC(npc2);

    std::string logFile = "test.log";

    FileLogger fileLogger(logFile);
    gameManager.addObserver(&fileLogger);

    double attackRange = 100.0;
    gameManager.startBattle(attackRange);

    std::vector<std::string> lines;
    fileLogger.getLogs(lines, logFile);

    EXPECT_EQ(lines.size(), 3);
    EXPECT_EQ(lines[0], "Event: Battle started with attack range: " + std::to_string(attackRange));
    EXPECT_EQ(lines[1], "Event: Орк (Orc) killed Медведь (Bear)");
    EXPECT_EQ(lines[2], "Event: Battle is over. The winner is: Орк (Orc)");
}