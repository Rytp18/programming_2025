#include "Player.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstdlib>


void removeDuplicates(std::vector<std::string>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        for (size_t j = i + 1; j < vec.size(); ) {
            if (vec[j] == vec[i]) {
                vec.erase(vec.begin() + j);
            }
            else {
                j++;
            }
        }
    }
}
void InventoryView(std::vector<std::string> inventory_) {
    if (inventory_.empty()) {
        std::cout << "empty";
    }
    else {
        for (size_t i = 0; i < inventory_.size(); ++i) {
            std::cout << inventory_[i];
            if (i != inventory_.size() - 1) {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

std::vector<std::string> plus_inventory(std::vector<std::string> result, std::vector<std::string> oth) {
    std::vector<std::string> inventory = result;
    for (int i = 0; i < oth.size(); i++) {
        if ((std::find(inventory.begin(), inventory.end(), oth[i])) == inventory.end()) {
            inventory.push_back(oth[i]);
        }
    }
    return inventory;
}



Player::Player(std::string name, int posx, int posy, int hp, std::string actionstatus, std::vector<std::string> inventory) {
    name_ = name;
    posx_ = posx;
    posy_ = posy;
    hp_ = hp;
    actionstatus_ = actionstatus;
    inventory_ = inventory;
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty!");
    }
    if (hp < 0) {
        throw std::invalid_argument("HP must be positive number!");
    }
}
Player::Player(const Player& other) :
    name_(other.name_),
    posx_(other.posx_),
    posy_(other.posy_),
    hp_(other.hp_),
    actionstatus_(other.actionstatus_),
    inventory_(other.inventory_) {
    std::cout << "Player was copied" << std::endl;
}
Player::~Player() {
    if (!inventory_.empty()) {
        inventory_.clear();
        std::cout << "Vector clear" << std::endl;
    }

    std::cout << "-------------Destructor-------------" << std::endl;
}
std::string Player::randomName() {
    return "Player_" + std::to_string(rand() % 100000);
}
Player& Player::operator=(const Player& other) {
    if (this == &other) {
        return *this;
    }
    name_ = other.name_;
    posx_ = other.posx_;
    posy_ = other.posy_;
    hp_ = other.hp_;
    actionstatus_ = other.actionstatus_;
    inventory_ = other.inventory_;
    std::cout << "Player assigned through assignment operator" << std::endl;
    return *this;
}

Player Player::operator+(const Player& other) const {
    Player result = *this;
    removeDuplicates(result.inventory_);
    result.name_ = result.randomName();
    result.posx_ = (this->posx_ + other.posx_) / 2;
    result.posy_ = (this->posy_ + other.posy_) / 2;
    result.inventory_ = plus_inventory(this->inventory_, other.inventory_);
    return result;
}
Player Player::operator-(const Player& other) const {
    Player result = *this;
    result.name_ = result.randomName();
    if (other.inventory_.empty()) return result;
    int items_to_remove = rand() % other.inventory_.size() + 1;
    std::string bufer = other.inventory_[(rand() % other.inventory_.size())];
    if (std::find(result.inventory_.begin(), result.inventory_.end(), bufer) == result.inventory_.end()) {
        return result;
    }
    result.inventory_.erase(std::remove(result.inventory_.begin(), result.inventory_.end(), bufer), result.inventory_.end());
    return result;
}

Player Player::operator/(const Player& other) const {
    Player result = *this;
    result.name_ = result.randomName();
    result.posx_ = ((abs(result.posx_) + 1) / (abs(this->posx_) + 1));
    result.posy_ = ((abs(result.posy_) + 1) / (abs(this->posy_) + 1));
    int middle1 = result.inventory_.size() / 2;
    int middle2 = other.inventory_.size() / 2;
    std::vector<std::string> firstHalf(result.inventory_.begin(), result.inventory_.begin() + middle1);
    std::vector<std::string> secondHalf(other.inventory_.begin() + middle2, other.inventory_.end());
    result.inventory_.clear();
    result.inventory_.reserve(firstHalf.size() + secondHalf.size());
    result.inventory_.insert(result.inventory_.end(), firstHalf.begin(), firstHalf.end());
    result.inventory_.insert(result.inventory_.end(), secondHalf.begin(), secondHalf.end());
    return result;
}

void Player::setPosX(int posx) {
    posx_ = posx;
}
void Player::setPosY(int posy) {
    posy_ = posy;
}
void Player::setInventoryInsert(std::string item) {
    inventory_.push_back(item);
    std::cout << "Element -" << item << "- Added to player's inventory -" << name_ << "-" << std::endl;
}
void Player::setInventoryRemove(std::string item) {
    if (std::find(inventory_.begin(), inventory_.end(), item) == inventory_.end()) {
        std::cout << "Element -" << item << "- Not in the player's inventory -" << name_ << "-" << std::endl;
        return;
    }
    inventory_.erase(std::remove(inventory_.begin(), inventory_.end(), item), inventory_.end());
    std::cout << "Element -" << item << "- Clear from the player's inventory -" << name_ << "-" << std::endl;
}
void Player::Setactionstatus(std::string actionstatus) {
    actionstatus_ = actionstatus;
}
void Player::DrinkFlask(int k) {
    hp_ += k;
    if (hp_ >= 100) {
        hp_ = 0;
    }
}
void Player::TakeDamage(int k) {
    hp_ -= k;
    if (hp_ <= 0) {
        hp_ = 0;
    }
}
void Player::ViewInventory() const {
    std::cout << "Player's inventory " << name_ << ":" << std::endl;
    for (const auto& item : inventory_) {
        std::cout << "- " << item << std::endl;
    }
    if (inventory_.empty()) {
        std::cout << "(empty)" << std::endl;
    }
}
void Player::ViewAll() const {
    std::cout << "Player: " << name_
        << "     HP: " << hp_
        << "     Position: (" << posx_
        << ", " << posy_ << ")"
        << "     " << "Action: " << actionstatus_
        << "     " << "InvenTory: ";
    InventoryView(inventory_);
}
std::string Player::GetName() const { return name_; }
int Player::GetPosX() const { return posx_; }
int Player::GetPosY() const { return posy_; }
int Player::GetHP() const { return hp_; }