#ifndef VISITOR_H
#define VISITOR_H

class Orc;
class Squirrel;
class Bear;

class Visitor
{
public:
    virtual void visit(Orc *orc) = 0;
    virtual void visit(Squirrel *squirrel) = 0;
    virtual void visit(Bear *bear) = 0;
    virtual ~Visitor() = default;
};
#endif