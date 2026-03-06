#pragma once
#include <Lootbox.hpp>
#include <string> 
#include <vector>

class Player {
private:
    std::string name_;
    int posx_;
    int posy_;
    int hp_;
    std::string actionstatus_;
    std::vector<Item> inventory_;
public:
    Player(std::string name, int posx, int posy, int hp, std::string actionstatus, std::vector<Item> inventory = {});
    Player(const Player& other);
    ~Player();
    std::string randomName();
    Player& operator=(const Player& other);
    Player operator+(const Player& other) const;
    Player operator-(const Player& other) const;
    Player operator/(const Player& other) const;
    void take_item_to_inventory(Item it);
    void OpenLootBox(LootBox box);
    void setPosX(int posx);
    void setPosY(int posy);
    void Setactionstatus(std::string actionstatus);
    void DrinkFlask(int k);
    void TakeDamage(int k);
    void ViewInventory() const;
    void ViewAll() const;
    std::string GetName() const;
    int GetPosX() const;
    int GetPosY() const;
    int GetHP() const;
};