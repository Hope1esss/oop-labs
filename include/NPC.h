#ifndef NPC_H
#define NPC_H

#include <string>
#include <iostream>
#include <cmath>
#include "Visitor.h"
#include <memory>
class NPC
{
protected:
    int x, y;
    std::string name;
    std::string type;

public:
    NPC(int x, int y, const std::string &name, const std::string &type);
    virtual ~NPC();

    std::string getName() const;
    std::string getType() const;
    std::pair<int, int> getPosition() const;

    virtual void accept(std::shared_ptr<Visitor> visitor) = 0;

    double distanceTo(std::shared_ptr<NPC> other) const;
    void printInfo() const;
};
#endif