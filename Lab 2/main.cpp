#include <iostream>
#include "Player.hpp"


int main() {
    srand(time(0));
    try {
        std::vector<std::string> items_player1 = { "sword", "shield", "potion" };
        std::vector<std::string> items_player2 = { "bow", "lom", "skotch", "arrows", "potion" };
        //startingItems.insert(startingItems.end(), "меч");
        //std::cout << startingItems.size() << std::endl;
        Player player1("Ivan", 0, 0, 100, "Run from the monster", items_player1);
        //std::cout << player1.GetName() << std::endl;
        //std::cout << player1.GetPosX() << std::endl;
        //player1.setPosX(100);
        Player player2("Robert", 11, 79, 91, "Searches box", items_player2);
        //std::cout << player1.GetPosX() << std::endl;
        Player player3 = player1 / player2;
        player1.ViewAll();
        //player2.setInventoryRemove("лук");
        player2.ViewAll();
        player3.ViewAll();
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown error: " << std::endl;
    }
}