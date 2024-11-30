#include "../include/BattleVisitor.h"
#include "../include/Orc.h"
#include "../include/Squirrel.h"
#include "../include/Bear.h"
#include "../include/GameManager.h"
#include <iostream>
#include <algorithm>

BattleVisitor::BattleVisitor(std::shared_ptr<NPC> attacker, double attackRange, std::vector<std::shared_ptr<NPC>> &npcs, std::vector<std::shared_ptr<Observer>> &observers, std::vector<std::shared_ptr<NPC>> &toRemove) : attacker(attacker), attackRange(attackRange), npcs(npcs), observers(observers), toRemove(toRemove) {}

void BattleVisitor::notify(const std::string &event, std::vector<std::shared_ptr<Observer>> &observers)
{
    for (auto &observer : observers)
    {
        observer->onEvent(event);
    }
}

void BattleVisitor::visit(std::shared_ptr<Orc> orc)
{
    if (attacker->distanceTo(orc) > attackRange)
        return;

    if (attacker->getType() == "Orc")
    {
        notify(attacker->getName() + " (Orc) killed " + orc->getName() + " (Orc)", observers);
        notify(orc->getName() + " (Orc) killed " + attacker->getName() + " (Orc)", observers);
        toRemove.push_back(orc);
        toRemove.push_back(attacker);
    }
    else if (attacker->getType() == "Bear")
    {
        notify(orc->getName() + " (Orc) killed " + attacker->getName() + " (Bear)", observers);
        toRemove.push_back(attacker);
    }
}

void BattleVisitor::visit(std::shared_ptr<Squirrel> squirrel)
{
    if (attacker->distanceTo(squirrel) > attackRange)
        return;

    if (attacker->getType() == "Bear")
    {
        notify(attacker->getName() + " (Bear) killed " + squirrel->getName() + " (Squirrel)", observers);
        toRemove.push_back(squirrel);
    }
}

void BattleVisitor::visit(std::shared_ptr<Bear> bear)
{
    if (attacker->distanceTo(bear) > attackRange)
        return;
    if (attacker->getType() == "Orc")
    {
        notify(attacker->getName() + " (Orc) killed " + bear->getName() + " (Bear)", observers);
        toRemove.push_back(bear);
    }
    else if (attacker->getType() == "Squirrel")
    {
        notify(bear->getName() + " (Bear) killed " + attacker->getName() + " (Squirrel)", observers);
        toRemove.push_back(attacker);
    }
}