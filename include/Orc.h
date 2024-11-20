#include "NPC.h"

class Orc : public NPC
{
public:
    Orc(int x, int y, const std::string &name);
    void interact(NPC *other) override;
};