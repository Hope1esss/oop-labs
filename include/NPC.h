#include <string>
#include <iostream>
#include <cmath>

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

    double distanceTo(NPC *other) const;

    virtual void interact(NPC *other) = 0;
    void printInfo() const;
};