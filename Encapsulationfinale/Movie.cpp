#include "Movie.h"
#include <iostream>

Movie::Movie(std::string title) : Media(title), ageLimit(0) {}

void Movie::inputDetails() {
    std::cout << "Entrez le format (Blu-ray/DVD) : ";
    std::cin.ignore();
    std::getline(std::cin, format);

    std::cout << "Entrez l'age limite : ";
    std::cin >> ageLimit;
}