#include <LootBox.hpp>

LootBox::LootBox(std::string name, std::vector<Item> items) {
    name_ = name;
    items_ = items;
}
LootBox::LootBox(const LootBox& other) :
    name_(other.name_),
    items_(other.items_) {
}

Item LootBox::Open_LootBox() {
    std::vector<Item> Legendary = {};
    std::vector<Item> Epic = {};
    std::vector<Item> Rare = {};
    std::vector<Item> Uncommon = {};
    std::vector<Item> Common = {};
    for (int i = 0; i < items_.size(); i++) {
        if (items_[i].rare == "Legendary") {
            Legendary.push_back(items_[i]);
        }
        else if (items_[i].rare == "Epic") {
            Epic.push_back(items_[i]);
        }
        else if (items_[i].rare == "Rare") {
            Rare.push_back(items_[i]);
        }
        else if (items_[i].rare == "Uncommon") {
            Uncommon.push_back(items_[i]);
        }
        else if (items_[i].rare == "Common") {
            Common.push_back(items_[i]);
        }
    }
    int bufer = (rand() % 100) + 1;
    if (bufer == 1) {
        return Legendary[rand() % Legendary.size()];
    }
    else if ((bufer >= 2) && (bufer <= 10)) {
        return Epic[rand() % Epic.size()];
    }
    else if ((bufer >= 11) && (bufer <= 25)) {
        return Rare[rand() % Rare.size()];
    }
    else if ((bufer >= 26) && (bufer <= 55)) {
        return Uncommon[rand() % Uncommon.size()];
    }
    else if ((bufer >= 56) && (bufer <= 100)) {
        return Common[rand() % Common.size()];
    }
}