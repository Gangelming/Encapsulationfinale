#include "Game.h"
#include <iostream>

Game::Game(std::string title) : Media(title) {}

void Game::inputDetails() {
    std::cout << "Entrez le studio : ";
    std::cin.ignore();
    std::getline(std::cin, studio);
    std::cout << "Entrez l'age limite : ";
    std::cin >> ageLimit;
    std::cout << "Entrez le genre : ";
    std::cin.ignore();
    std::getline(std::cin, genre);
}