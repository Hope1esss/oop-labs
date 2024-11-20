#include "../include/Squirrel.h"

Squirrel::Squirrel(int x, int y, const std::string &name) : NPC(x, y, name, "Squirrel") {}

void Squirrel::interact(NPC *other) {}