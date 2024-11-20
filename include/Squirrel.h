#include "NPC.h"

class Squirrel : public NPC
{
public:
    Squirrel(int x, int y, const std::string &name);
    void interact(NPC *other) override;
};