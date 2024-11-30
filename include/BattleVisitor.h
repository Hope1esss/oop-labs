#ifndef BATTLE_VISITOR_H
#define BATTLE_VISITOR_H

#include "Visitor.h"
#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>

class BattleVisitor : public Visitor
{
private:
    std::shared_ptr<NPC> attacker;
    double attackRange;
    std::vector<std::shared_ptr<NPC>> &npcs;
    std::vector<std::shared_ptr<Observer>> &observers;
    std::vector<std::shared_ptr<NPC>> &toRemove;

public:
    BattleVisitor(std::shared_ptr<NPC> attacker, double attackRange, std::vector<std::shared_ptr<NPC>> &npcs, std::vector<std::shared_ptr<Observer>> &observers, std::vector<std::shared_ptr<NPC>> &toRemove);
    void visit(std::shared_ptr<Orc> orc) override;
    void visit(std::shared_ptr<Squirrel> squirrel) override;
    void visit(std::shared_ptr<Bear> bear) override;
    static void notify(const std::string &event, std::vector<std::shared_ptr<Observer>> &observers);
};
#endif