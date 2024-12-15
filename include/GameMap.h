#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "NPC.h"
class GameMap
{
private:
    std::vector<std::vector<int>> map;
    int width, height;
    sf::RenderWindow &window;

public:
    GameMap(int width, int height, sf::RenderWindow &window);

    void drawMap();

    void placeNPCs(std::vector<std::shared_ptr<NPC>> &npcs);
};