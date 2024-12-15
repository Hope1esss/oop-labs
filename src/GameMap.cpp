#include "../include/GameMap.h"

GameMap::GameMap(int width, int height, sf::RenderWindow &window) : width(width), height(height), window(window)
{
    map.resize(height, std::vector<int>(width, 0));
}

void GameMap::drawMap()
{
    // Рисуем карту
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            sf::RectangleShape cell(sf::Vector2f(50.f, 50.f)); // Клетка 50x50

            // Устанавливаем позицию клетки на экране
            cell.setPosition(x * 50.f, y * 50.f);

            // Если на клетке есть NPC, рисуем её зелёной, иначе белой
            if (map[y][x] == 1)
            {
                cell.setFillColor(sf::Color::Green);
            }
            else
            {
                cell.setFillColor(sf::Color::White);
            }

            window.draw(cell); // Отрисовываем клетку
        }
    }
}


void GameMap::placeNPCs(std::vector<std::shared_ptr<NPC>> &npcs)
{
    // Сначала очищаем карту
    std::fill(map.begin(), map.end(), std::vector<int>(width, 0));

    // Обновляем позиции NPC на карте
    for (const auto &npc : npcs)
    {
        int x = npc->getPosition().first;
        int y = npc->getPosition().second;

        // Проверяем, что координаты NPC находятся в пределах карты
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            map[y][x] = 1;  // Помечаем клетку как занятую NPC
        }
    }
}
