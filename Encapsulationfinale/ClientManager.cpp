#include "ClientManager.h"
#include <iostream>
#include "Utils.h"
void ClientManager::addClient() {
    std::string name, firstname, address, phoneNumber, email;
    int age;

    std::cout << "Entrez le nom : ";
    std::cin >> name;
    std::cout << "Entrez le prenom : ";
    std::cin >> firstname;
    std::cout << "Entrez l'age : ";
    std::cin >> age;
    std::cout << "Entrez l'adresse : ";
    std::cin.ignore();
    std::getline(std::cin, address);
    std::cout << "Entrez le numero de telephone : ";
    std::cin >> phoneNumber;
    std::cout << "Entrez l'e-mail : ";
    std::cin >> email;

    clients.emplace_back(name, firstname, age, address, phoneNumber, email);
    std::cout << "Client ajoute avec succes.\n";
}

void ClientManager::removeClient() {
    if (clients.empty()) {
        std::cout << "Aucun client a supprimer.\n";
        return;
    }

    // Créer une liste des noms de clients
    std::vector<std::string> clientNames;
    for (const auto& client : clients) {
        clientNames.push_back(client.getName() + " " + client.getFirstname() + " (" + client.getEmail() + ")");
    }

    // Sélectionner un client
    int selected = selectFromList(clientNames);

    // Trouver et supprimer le client sélectionné
    auto it = std::find_if(clients.begin(), clients.end(),
        [&clientNames, selected](const Client& client) {
            return (client.getName() + " " + client.getFirstname() + " (" + client.getEmail() + ")")
                == clientNames[selected];
        });

    if (it != clients.end()) {
        clients.erase(it);
        std::cout << "Client supprime avec succes.\n";
    }
    else {
        std::cout << "Erreur lors de la suppression du client.\n";
    }
}

void ClientManager::listClients() const {
    if (clients.empty()) {
        std::cout << "Aucun client enregistre.\n";
        return;
    }

    for (const auto& client : clients) {
        std::cout << "Nom: " << client.getName() << ", Prenom: " << client.getFirstname()
            << ", Age: " << client.getAge() << ", Email: " << client.getEmail() << "\n";
    }
}

void ClientManager::listBorrowedMedia() const {
    bool hasBorrowedMedia = false;

    for (const auto& client : clients) {
        auto borrowedMedia = client.getBorrowedMedia();
        if (!borrowedMedia.empty()) {
            hasBorrowedMedia = true;
            std::cout << "Client: " << client.getName() << " " << client.getFirstname()
                << " (Age: " << client.getAge() << ")\n";
            std::cout << "Medias empruntes :\n";
            for (const auto& media : borrowedMedia) {
                std::cout << " - " << media << "\n";
            }
            std::cout << "\n";
        }
    }

    if (!hasBorrowedMedia) {
        std::cout << "Aucun client n'a actuellement de medias empruntes.\n";
    }
}