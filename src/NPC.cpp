#include "../include/NPC.h"

NPC::NPC(int x, int y, const std::string &name, const std::string &type) : x(x), y(y), name(name), type(type) {}

NPC::~NPC() = default;

std::string NPC::getName() const
{
    return name;
}

std::string NPC::getType() const
{
    return type;
}

std::pair<int, int> NPC::getPosition() const
{
    return {x, y};
}

double NPC::distanceTo(NPC *other) const
{
    return std::sqrt(std::pow(x - other->x, 2) + std::pow(y - other->y, 2));
}

void NPC::printInfo() const
{
    std::cout << "Type: " << type << ", Name: " << name << ", Position: (" << x << ", " << y << ")" << std::endl;
}