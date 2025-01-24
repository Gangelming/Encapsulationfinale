#include "MediaManager.h"
#include "Game.h"
#include "Book.h"
#include "Movie.h"
#include "Utils.h"
#include <iostream>
#include <algorithm>
#include <conio.h>

MediaManager::~MediaManager() {
    for (auto media : medias) {
        delete media;
    }
}

void MediaManager::addMedia() {
    std::vector<std::string> mediaTypes = {
        "Jeu video",
        "Livre",
        "Film"
    };

    int selected = selectFromList(mediaTypes);

    std::string title;
    std::cout << "Entrez le titre (mettre un espace puis le nom) : ";
    std::cin.ignore();
    std::getline(std::cin, title);

    Media* newMedia = nullptr;
    switch (selected) {
    case 0:
        newMedia = new Game(title);
        break;
    case 1:
        newMedia = new Book(title);
        break;
    case 2:
        newMedia = new Movie(title);
        break;
    }

    newMedia->inputDetails();
    medias.push_back(newMedia);
    std::cout << "Media ajoute avec succes.\n";
}

void MediaManager::removeMedia() {
    if (medias.empty()) {
        std::cout << "Aucun media a supprimer.\n";
        return;
    }

    std::vector<std::string> mediaTitles;
    for (const auto& media : medias) {
        mediaTitles.push_back(media->getTitle());
    }

    int selected = selectFromList(mediaTitles);

    delete medias[selected];
    medias.erase(medias.begin() + selected);
    std::cout << "Media supprime avec succes.\n";
}

void MediaManager::listMedia() const {
    if (medias.empty()) {
        std::cout << "Aucun media enregistre.\n";
        return;
    }

    std::vector<Media*> jeux, livres, films;

    // Trier les m�dias par type
    for (const auto& media : medias) {
        if (dynamic_cast<Game*>(media)) {
            jeux.push_back(media);
        }
        else if (dynamic_cast<Book*>(media)) {
            livres.push_back(media);
        }
        else if (dynamic_cast<Movie*>(media)) {
            films.push_back(media);
        }
    }

    // Afficher les jeux vid�o
    std::cout << "=== Jeux Video ===\n";
    for (const auto& jeu : jeux) {
        std::cout << "Titre: " << jeu->getTitle() << ", Emprunte: " << (jeu->getIsBorrowed() ? "Oui" : "Non") << "\n";
    }

    // Afficher les livres
    std::cout << "\n=== Livres ===\n";
    for (const auto& livre : livres) {
        std::cout << "Titre: " << livre->getTitle() << ", Emprunte: " << (livre->getIsBorrowed() ? "Oui" : "Non") << "\n";
    }

    // Afficher les films
    std::cout << "\n=== Films ===\n";
    for (const auto& film : films) {
        std::cout << "Titre: " << film->getTitle() << ", Emprunte: " << (film->getIsBorrowed() ? "Oui" : "Non") << "\n";
    }
}

void MediaManager::rentMedia(ClientManager& clientManager) {
    // S�lectionner un client
    std::vector<std::string> clientNames;
    for (const auto& client : clientManager.getClients()) {
        // Check borrowing limit
        if (client.getBorrowedMedia().size() >= 5) {
            std::cout << "Le client " << client.getName() << " a d�j� emprunt� 5 m�dias.\n";
            return;
        }
        clientNames.push_back(client.getName() + " " + client.getFirstname() + " (Age: " + std::to_string(client.getAge()) + ")");
    }
    int clientSelected = selectFromList(clientNames);
    auto& selectedClient = clientManager.getClients()[clientSelected];

    // S�lectionner un m�dia
    std::vector<std::string> availableMedias;
    std::vector<int> mediaPossibleAges;
    for (const auto& media : medias) {
        if (!media->getIsBorrowed()) {
            Game* gameMedia = dynamic_cast<Game*>(media);
            Movie* movieMedia = dynamic_cast<Movie*>(media);

            if (gameMedia) {
                availableMedias.push_back(media->getTitle() + " (Jeu, Age limite: " + std::to_string(gameMedia->getAgeLimit()) + ")");
                mediaPossibleAges.push_back(gameMedia->getAgeLimit());
            }
            else if (movieMedia) {
                availableMedias.push_back(media->getTitle() + " (Film, Age limite: " + std::to_string(movieMedia->getAgeLimit()) + ")");
                mediaPossibleAges.push_back(movieMedia->getAgeLimit());
            }
            else {
                availableMedias.push_back(media->getTitle());
                mediaPossibleAges.push_back(0);
            }
        }
    }

    if (availableMedias.empty()) {
        std::cout << "Tous les medias sont deja empruntes.\n";
        return;
    }

    int mediaSelected = selectFromList(availableMedias);

    // V�rifier l'�ge pour les jeux et les films
    Game* selectedGameMedia = dynamic_cast<Game*>(medias[mediaSelected]);
    Movie* selectedMovieMedia = dynamic_cast<Movie*>(medias[mediaSelected]);

    if (selectedGameMedia && selectedClient.getAge() < selectedGameMedia->getAgeLimit()) {
        std::cout << "Age insuffisant pour emprunter ce jeu.\n";
        return;
    }

    if (selectedMovieMedia && selectedClient.getAge() < selectedMovieMedia->getAgeLimit()) {
        std::cout << "Age insuffisant pour emprunter ce film.\n";
        return;
    }

    // Limite d'emprunt
    if (selectedClient.getBorrowedMedia().size() >= 5) {
        std::cout << "Limite de 5 m�dias emprunt�s atteinte.\n";
        return;
    }

    // Emprunter le m�dia
    medias[mediaSelected]->borrow();
    selectedClient.borrowMedia(medias[mediaSelected]->getTitle());
    std::cout << "Media emprunte avec succes.\n";
}

void MediaManager::returnMedia(ClientManager& clientManager) {
    // S�lectionner un m�dia emprunt�
    std::vector<std::string> borrowedMedias;
    for (const auto& media : medias) {
        if (media->getIsBorrowed()) {
            borrowedMedias.push_back(media->getTitle());
        }
    }

    if (borrowedMedias.empty()) {
        std::cout << "Aucun media emprunte a retourner.\n";
        return;
    }

    int mediaSelected = selectFromList(borrowedMedias);

    // S�lectionner le client qui a emprunt� ce m�dia
    std::vector<std::string> borrowingClients;
    for (const auto& client : clientManager.getClients()) {
        auto borrowedMedia = client.getBorrowedMedia();
        if (std::find(borrowedMedia.begin(), borrowedMedia.end(), borrowedMedias[mediaSelected]) != borrowedMedia.end()) {
            borrowingClients.push_back(client.getName() + " " + client.getFirstname());
        }
    }

    if (borrowingClients.empty()) {
        std::cout << "Aucun client n'a emprunte ce media.\n";
        return;
    }

    int clientSelected = selectFromList(borrowingClients);

    // Retourner le m�dia
    for (auto& media : medias) {
        if (media->getTitle() == borrowedMedias[mediaSelected]) {
            media->returnMedia();

            // Retirer le m�dia des emprunts du client
            auto& selectedClient = clientManager.getClients()[clientSelected];
            selectedClient.returnMedia(media->getTitle());

            std::cout << "Media retourne avec succes.\n";
            return;
        }
    }
}