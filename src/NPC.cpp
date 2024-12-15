#include "../include/NPC.h"

NPC::NPC(int x, int y, const std::string &name, const std::string &type, int moveDistance, int killDistance, bool alive) : x(x), y(y), name(name), type(type), moveDistance(moveDistance), killDistance(killDistance), alive(true) {}

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

int NPC::getMoveDistance() const
{
    return moveDistance;
}

int NPC::getKillDistance() const
{
    return killDistance;
}

bool NPC::isAlive() const
{
    return alive;
}

void NPC::kill()
{
    alive = false;
}
void NPC::move(int dx, int dy)
{
    x = std::max(0, std::min(500, x + dx));
    y = std::max(0, std::min(500, y + dy));
}

double NPC::distanceTo(std::shared_ptr<NPC> other) const
{
    return std::sqrt(std::pow(x - other->x, 2) + std::pow(y - other->y, 2));
}

void NPC::printInfo() const
{
    std::cout << "Type: " << type << ", Name: " << name << ", Position: (" << x << ", " << y << ")" << std::endl;
}