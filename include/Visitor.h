#ifndef VISITOR_H
#define VISITOR_H
#include <memory>

class Orc;
class Squirrel;
class Bear;

class Visitor
{
public:
    virtual void visit(std::shared_ptr<Orc> orc) = 0;
    virtual void visit(std::shared_ptr<Squirrel> squirrel) = 0;
    virtual void visit(std::shared_ptr<Bear> bear) = 0;
    virtual ~Visitor() = default;
};
#endif