#include "../include/AsyncBattleVisitor.h"
#include "../include/Orc.h"
#include "../include/Squirrel.h"
#include "../include/Bear.h"
#include "../include/GameManager.h"
#include <iostream>
#include <algorithm>

AsyncBattleVisitor::AsyncBattleVisitor(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, std::vector<std::shared_ptr<Observer>> &observers) : attacker(attacker), defender(defender), observers(observers) {}

void AsyncBattleVisitor::notify(const std::string &event, std::vector<std::shared_ptr<Observer>> &observers)
{
    for (auto &observer : observers)
    {
        observer->onEvent(event);
    }
}

void AsyncBattleVisitor::visit(std::shared_ptr<Orc> orc)
{
    int attackRoll = rand() % 6 + 1;
    int defenseRoll = rand() % 6 + 1;
    if (attacker->getType() == "Orc")
    {
        if (attackRoll > defenseRoll)
        {
            notify(attacker->getName() + " (Orc) killed " + defender->getName() + " (Orc)", observers);
            defender->kill();
        }
        else
        {
            notify(defender->getName() + " (Orc) killed " + attacker->getName() + " (Orc)", observers);
            attacker->kill();
        }
    } else if (attacker->getType() == "Bear")
    {
        if (defenseRoll > attackRoll)
        {
            notify(defender->getName() + " (Orc) killed " + attacker->getName() + " (Bear)", observers);
            attacker->kill();
        }
        else
        {
            notify(attacker->getName() + " (Bear) defended against " + defender->getName() + " (Orc)", observers);
        }
    }
}

void AsyncBattleVisitor::visit(std::shared_ptr<Squirrel> squirrel)
{
    int attackRoll = rand() % 6 + 1;
    int defenseRoll = rand() % 6 + 1;

    if (attacker->getType() == "Bear")
    {
        if (attackRoll > defenseRoll)
        {
            notify(attacker->getName() + " (Bear) killed " + defender->getName() + " (Squirrel)", observers);
            defender->kill();
        }
        else
        {
            notify(defender->getName() + " (Squirrel) defended against " + attacker->getName() + " (Bear)", observers);
        }
    }
}

void AsyncBattleVisitor::visit(std::shared_ptr<Bear> bear)
{
    int attackRoll = rand() % 6 + 1;
    int defenseRoll = rand() % 6 + 1;
    if (attacker->getType() == "Orc")
    {
        if (attackRoll > defenseRoll)
        {
            notify(attacker->getName() + " (Orc) killed " + defender->getName() + " (Bear)", observers);
            defender->kill();
        }
        else
        {
            notify(defender->getName() + " (Bear) defended against " + attacker->getName() + " (Orc)", observers);
        }
    }
}