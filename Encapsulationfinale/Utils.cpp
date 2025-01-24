#include <iostream>
#include <conio.h>
#include "Utils.h"

void clearScreen() {

    std::cout << "\033[2J\033[1;1H";
}

int selectFromList(const std::vector<std::string>& items) {
    int selected = 0;
    while (true) {
        clearScreen();
        std::cout << "Selectionnez un element (Fleches pour naviguer, Entree pour valider) :\n";
        for (size_t i = 0; i < items.size(); ++i) {
            if (i == selected) {
                std::cout << " > " << items[i] << " < \n";
            }
            else {
                std::cout << "   " << items[i] << "\n";
            }
        }

        int key = _getch();
        if (key == 72) { // Flиche haut
            selected = (selected - 1 + items.size()) % items.size();
        }
        else if (key == 80) { // Flиche bas
            selected = (selected + 1) % items.size();
        }
        else if (key == 13) { // Touche Entrйe
            return selected;
        }
    }
}