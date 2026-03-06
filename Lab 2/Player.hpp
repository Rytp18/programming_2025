#pragma once
#include <string> 
#include <vector>

class Player {
private:
    std::string name_;
    int posx_;
    int posy_;
    int hp_;
    std::string actionstatus_;
    std::vector<std::string> inventory_;
public:
    Player(std::string name, int posx, int posy, int hp, std::string actionstatus, std::vector<std::string> inventory = {});
    Player(const Player& other);
    ~Player();
    std::string randomName();
    Player& operator=(const Player& other);
    Player operator+(const Player& other) const;
    Player operator-(const Player& other) const;
    Player operator/(const Player& other) const;
    void setPosX(int posx);
    void setPosY(int posy);
    void setInventoryInsert(std::string item);
    void setInventoryRemove(std::string item);
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