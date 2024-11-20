#include "NPC.h"

class Bear : public NPC
{
public:
    Bear(int x, int y, const std::string &name);
    void interact(NPC *other) override;
};