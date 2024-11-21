#ifndef BATTLE_VISITOR_H
#define BATTLE_VISITOR_H

#include "Visitor.h"
#include "NPC.h"
#include "Observer.h"
#include <vector>

class BattleVisitor : public Visitor
{
private:
    NPC *attacker;
    double attackRange;
    std::vector<NPC *> &npcs;
    std::vector<Observer *> &observers;
    std::vector<NPC *> &toRemove;

public:
    BattleVisitor(NPC *attacker, double attackRange, std::vector<NPC *> &npcs, std::vector<Observer *> &observers, std::vector<NPC *> &toRemove);
    void visit(Orc *orc) override;
    void visit(Squirrel *squirrel) override;
    void visit(Bear *bear) override;
    static void notify(const std::string &event, std::vector<Observer *> &observers);
};
#endif