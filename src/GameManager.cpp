#include "../include/GameManager.h"
#include "../include/BattleVisitor.h"
#include "../include/AsyncBattleVisitor.h"
#include <random>
#include <ctime>
#include <vector>
#include "../include/GameMap.h"
GameManager::~GameManager()
{
    npcs.clear();
}

void GameManager::addNPC(const std::shared_ptr<NPC> &npc)
{
    npcs.push_back(npc);
}

void GameManager::removeNPCByIndex(size_t index)
{
    if (index < npcs.size())
    {
        removeNPC(npcs[index], npcs);
    }
    else
    {
        std::cerr << "Invalid index: " << index << std::endl;
    }
}

void GameManager::addObserver(const std::shared_ptr<Observer> &observer)
{
    observers.push_back(observer);
}

void GameManager::removeObserver(const std::shared_ptr<Observer> &observer)
{
    auto it = std::find(observers.begin(), observers.end(), observer);
    if (it != observers.end())
    {
        observers.erase(it);
    }
}
void GameManager::removeNPC(const std::shared_ptr<NPC> &npc, std::vector<std::shared_ptr<NPC>> &npcs)
{
    auto it = std::find(npcs.begin(), npcs.end(), npc);
    if (it != npcs.end())
    {
        npcs.erase(it);
    }
}

void GameManager::removeNPCAsync(const std::shared_ptr<NPC> &npc, std::vector<std::shared_ptr<NPC>> &npcs, std::mutex &mutex)
{
    std::lock_guard<std::mutex> lock(mutex);
    GameManager::removeNPC(npc, npcs);
}

void GameManager::removeDeadNPCs(std::vector<std::shared_ptr<NPC>> &npcs, std::mutex &mutex)
{
    for (auto it = npcs.begin(); it != npcs.end();)
    {
        if (!(*it)->isAlive())
        {
            removeNPCAsync(*it, npcs, mutex);
            it = npcs.begin();
        } else
        {
            ++it;
        }
    }
}
void GameManager::getNPCs(std::vector<std::shared_ptr<NPC>> &npcs) const
{
    npcs = this->npcs;
}

void GameManager::clearNPCs()
{
    npcs.clear();
}
void GameManager::printNPCList() const
{
    if (npcs.empty())
    {
        std::cout << "NPC List is empty" << std::endl;
    }
    else
    {
        std::cout << "NPC List:" << std::endl;
        for (const auto &npc : npcs)
        {
            npc->printInfo();
        }
    }
}

void GameManager::saveNPCsToFile(const std::string &filename) const
{
    std::ofstream outputFile(filename);
    if (!outputFile)
    {
        throw OpeningFileException();
    }

    for (const auto &npc : npcs)
    {
        outputFile << npc->getPosition().first << " "
                   << npc->getPosition().second << " "
                   << npc->getName() << " "
                   << npc->getType() << std::endl;
    }

    outputFile.close();
    std::cout << "NPCs saved to file: " << filename << std::endl;
}

void GameManager::loadNPCsFromFile(const std::string &filename)
{
    std::ifstream inputFile(filename);
    if (!inputFile)
    {
        throw OpeningFileException();
    }

    int x, y;
    std::string name, type;

    while (inputFile >> x >> y >> name >> type)
    {
        std::shared_ptr<NPC> npc = NPCFactory::createNPC(x, y, name, type);
        if (npc)
        {
            addNPC(npc);
        }
        else
        {
            std::cerr << "Error creating NPC: " << type << ", " << name << ", (" << x << ", " << y << ")" << std::endl;
        }
    }
    inputFile.close();
    std::cout << "NPCs loaded from file: " << filename << std::endl;
}

void GameManager::startBattle(double attackRange)
{
    int AFKBattleCounter = 0;
    BattleVisitor::notify("Battle started with attack range: " + std::to_string(attackRange), observers);
    std::vector<std::shared_ptr<NPC>> toRemove;
    while (npcs.size() > 1)
    {
        bool anyBattleOccurred = false;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(npcs.begin(), npcs.end(), gen);
        for (size_t i = 0; i < npcs.size(); i += 2)
        {
            if (i + 1 < npcs.size())
            {
                std::shared_ptr<NPC> npc1 = npcs[i];
                std::shared_ptr<NPC> npc2 = npcs[i + 1];

                std::shared_ptr<BattleVisitor> visitor = std::make_shared<BattleVisitor>(npc1, attackRange, npcs, observers, toRemove);
                npc2->accept(visitor);

                if ((std::find(toRemove.begin(), toRemove.end(), npc1) != toRemove.end()) || (std::find(toRemove.begin(), toRemove.end(), npc2) != toRemove.end()))
                {
                    anyBattleOccurred = true;
                }
            }
        }

        for (auto npc : toRemove)
        {
            removeNPC(npc, npcs);
        }

        if (!anyBattleOccurred)
        {
            AFKBattleCounter++;
            if (AFKBattleCounter > 50)
            {
                break;
            }
        }
        else
        {
            AFKBattleCounter = 0;
        }

        toRemove.clear();
    }

    // Вывод результата
    if (npcs.size() == 1)
    {
        BattleVisitor::notify("Battle is over. The winner is: " + npcs[0]->getName() + " (" + npcs[0]->getType() + ")", observers);
    }
    else if (npcs.size() > 1)
    {

        BattleVisitor::notify("Battle is over. Friendship wins! No winner could be determined. Remaining NPCs:", observers);
        for (const auto &npc : npcs)
        {
            BattleVisitor::notify(npc->getName() + " (" + npc->getType() + ")", observers);
        }
    }
    else
    {
        BattleVisitor::notify("Battle is over. No winner could be determined. All NPCs are dead", observers);
    }
}

// Многопоточка пошла
void GameManager::moveNPCs(std::vector<std::shared_ptr<NPC>> &npcs, std::queue<FightTask> &fightQueue, std::mutex &mutex)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> directionDis(0, 3);

    while (!stopThreadsFlag)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        for (auto &npc : npcs)
        {
            if (!npc->isAlive())
                continue;
            int direction = directionDis(gen);
            int dx, dy = 0;
            switch (direction)
            {
            case 0:
                dy = npc->getMoveDistance();
                break; // UP
            case 1:
                dx = npc->getMoveDistance();
                break; // RIGHT
            case 2:
                dy = -npc->getMoveDistance();
                break; // DOWN
            case 3:
                dx = -npc->getMoveDistance();
                break; // LEFT
            }
            {
                std::lock_guard<std::mutex> lock(mutex);
                npc->move(dx, dy);
            }
            for (auto &otherNPC : npcs)
            {
                if (npc != otherNPC && otherNPC->isAlive())
                {
                    double distanceBetweenNPCs = npc->distanceTo(otherNPC);

                    if (distanceBetweenNPCs <= npc->getKillDistance() && distanceBetweenNPCs <= otherNPC->getKillDistance())
                    {
                        fightQueue.push(FightTask(npc, otherNPC, true));
                        break;
                    }
                    else if (distanceBetweenNPCs <= npc->getKillDistance() && distanceBetweenNPCs > otherNPC->getKillDistance())
                    {
                        fightQueue.push(FightTask(npc, otherNPC, false));
                        break;
                    }
                    else if (distanceBetweenNPCs > npc->getKillDistance() && distanceBetweenNPCs <= otherNPC->getKillDistance())
                    {
                        fightQueue.push(FightTask(otherNPC, npc, false));
                        break;
                    }
                }
            }
        }
    }
}

void GameManager::fightNPCs(std::vector<std::shared_ptr<NPC>> &npcs, std::queue<FightTask> &fightQueue, std::vector<std::shared_ptr<Observer>> &observers, std::mutex &mutex)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    while (!stopThreadsFlag)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (!fightQueue.empty())
        {
            FightTask task;

            {
                std::lock_guard<std::mutex> lock(mutex);
                task = fightQueue.front();
                fightQueue.pop();
            }

            std::shared_ptr<AsyncBattleVisitor> visitor = std::make_shared<AsyncBattleVisitor>(task.attacker, task.defender, observers);
            
            task.defender->accept(visitor);
        }
    }
}

void GameManager::printMap(std::vector<std::shared_ptr<NPC>> npcs, std::mutex &mutex)
{
    // Создаем окно SFML
    sf::RenderWindow window(sf::VideoMode(500, 500), "Balagur Fate 3");

    // Создаем объект GameMap для отрисовки карты
    GameMap gameMap(500, 500, window);

    // Основной цикл отрисовки
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Закрытие окна при клике на крестик
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // Очистка окна перед новой отрисовкой
        window.clear();

        // Мьютекс для синхронизации доступа к данным
        std::lock_guard<std::mutex> lock(mutex);

        // Обновляем расположение NPC на карте
        gameMap.placeNPCs(npcs);

        // Рисуем обновленную карту
        gameMap.drawMap();

        // Отображаем все на экране
        window.display();

        // Устанавливаем задержку, чтобы не обновлять экран слишком быстро
        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Можно увеличить для более плавного обновления
    }
}


void GameManager::stopThreads()
{
    stopThreadsFlag = true;
}

void GameManager::startAsyncBattle()
{
    std::thread moveThread([this]
                           { moveNPCs(npcs, fightQueue, mutex); });
    std::thread fightThread([this]
                            { fightNPCs(npcs, fightQueue, observers, mutex); });
    std::thread mapThread([this]
                          { printMap(npcs, mutex); });
    std::cout << "Battle Started!" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(10));

    stopThreads();

    moveThread.join();
    fightThread.join();
    mapThread.join();

    std::cout << "Battle Finished!" << std::endl;

    GameManager::removeDeadNPCs(npcs, mutex);
    
    std::cout << "Remaining NPCs:" << std::endl;

    printNPCList();
    stopThreadsFlag = false;
}