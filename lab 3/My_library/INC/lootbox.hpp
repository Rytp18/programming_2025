#pragma once
#include <string> 
#include <vector>
#include <Item.hpp>

class LootBox {
private:
    std::string name_;
    std::vector<Item> items_;
public:
    LootBox(std::string name, std::vector<Item> items);
    LootBox(const LootBox& other);
    ~LootBox();
    Item Open_LootBox();
};