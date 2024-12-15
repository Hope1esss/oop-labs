#ifndef ASYNC_BATTLE_VISITOR_H
#define ASYNC_BATTLE_VISITOR_H

#include "Visitor.h"
#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>
#include <mutex>

class AsyncBattleVisitor : public Visitor
{
private:
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
    std::vector<std::shared_ptr<Observer>> &observers;

public:
    AsyncBattleVisitor(std::shared_ptr<NPC> attacker, std::shared_ptr<NPC> defender, std::vector<std::shared_ptr<Observer>> &observers);
    void visit(std::shared_ptr<Orc> orc) override;
    void visit(std::shared_ptr<Squirrel> squirrel) override;
    void visit(std::shared_ptr<Bear> bear) override;
    static void notify(const std::string &event, std::vector<std::shared_ptr<Observer>> &observers);
};
#endif