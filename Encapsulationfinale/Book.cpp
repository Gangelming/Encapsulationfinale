#include "Book.h"
#include <iostream>

Book::Book(std::string title) : Media(title) {}

void Book::inputDetails() {
    std::cout << "Entrez l'ISBN : ";
    std::cin.ignore();
    std::getline(std::cin, isbn);
}