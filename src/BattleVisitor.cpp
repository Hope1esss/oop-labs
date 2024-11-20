#include "../include/BattleVisitor.h"
#include "../include/Orc.h"
#include "../include/Squirrel.h"
#include "../include/Bear.h"
#include "../include/GameManager.h"
#include <iostream>
#include <algorithm>

BattleVisitor::BattleVisitor(NPC *attacker, double attackRange, std::vector<NPC *> &npcs, std::vector<Observer *> &observers) : attacker(attacker), attackRange(attackRange), npcs(npcs), observers(observers) {}

void BattleVisitor::notify(const std::string &event)
{
    for (auto &observer : observers)
    {
        observer->onEvent(event);
    }
}

void BattleVisitor::visit(Orc *orc)
{
    if (attacker->distanceTo(orc) > attackRange)
        return;

    if (attacker->getType() == "Orc")
    {
        notify(attacker->getName() + " (Orc) killed " + orc->getName() + " (Orc)");
        notify(orc->getName() + " (Orc) killed " + attacker->getName() + " (Orc)");
        GameManager::removeNPC(attacker, npcs);
        GameManager::removeNPC(orc, npcs);
    }
    else if (attacker->getType() == "Bear")
    {
        notify(orc->getName() + " (Orc) killed " + attacker->getName() + " (Bear)");
        GameManager::removeNPC(attacker, npcs);
    }
    else if (attacker->getType() == "Squirrel")
    {
        notify(orc->getName() + " (Orc) avoids combat");
    }
}

void BattleVisitor::visit(Squirrel *squirrel)
{
    if (attacker->distanceTo(squirrel) > attackRange)
        return;

    if (attacker->getType() == "Bear")
    {
        notify(attacker->getName() + " (Bear) killed " + squirrel->getName() + " (Squirrel)");
        GameManager::removeNPC(squirrel, npcs);
    }
    else if ((attacker->getType() == "Orc") || (attacker->getType() == "Squirrel"))
    {
        notify(squirrel->getName() + " (Squirrel) avoids combat");
    }
}

void BattleVisitor::visit(Bear *bear)
{
    if (attacker->distanceTo(bear) > attackRange)
        return;
    if (attacker->getType() == "Orc")
    {
        notify(attacker->getName() + " (Orc) killed " + bear->getName() + " (Bear)");
        GameManager::removeNPC(bear, npcs);
    }
    else if (attacker->getType() == "Squirrel")
    {
        notify(bear->getName() + " (Bear) killed " + attacker->getName() + " (Squirrel)");
        GameManager::removeNPC(attacker, npcs);
    }
    else if (attacker->getType() == "Bear")
    {
        notify(bear->getName() + " (Bear) avoids combat");
    }
}