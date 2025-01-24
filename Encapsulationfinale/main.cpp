#include <iostream>
#include "Client.h"
#include "MediaManager.h"
#include "ClientManager.h"
#include "Utils.h"
#include <conio.h>

void showMenu(const std::vector<std::string>& options, int selected) {
    clearScreen();
    std::cout << "========================\n";
    std::cout << "  Gestion de la Mediatheque\n";
    std::cout << "========================\n";
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == selected) {
            std::cout << " > " << options[i] << " < \n";
        }
        else {
            std::cout << "   " << options[i] << "\n";
        }
    }
}

void mainMenu(ClientManager& clientManager, MediaManager& mediaManager) {
    std::vector<std::string> options = {
        "Ajouter un client",
        "Supprimer un client",
        "Lister les clients",
        "Ajouter un media",
        "Supprimer un media",
        "Lister les medias",
        "Emprunter un media",
        "Retourner un media",
        "Voir les medias empruntes",
        "Quitter"
    };

    int selected = 0;
    while (true) {
        showMenu(options, selected);
        int key = _getch();

        if (key == 72) { // Flèche haut
            selected = (selected - 1 + options.size()) % options.size();
        }
        else if (key == 80) { // Flèche bas
            selected = (selected + 1) % options.size();
        }
        else if (key == 13) { // Touche Entrée
            clearScreen();
            switch (selected) {
            case 0:
                clientManager.addClient();
                break;
            case 1:
                clientManager.removeClient();
                break;
            case 2:
                clientManager.listClients();
                break;
            case 3:
                mediaManager.addMedia();
                break;
            case 4:
                mediaManager.removeMedia();
                break;
            case 5:
                mediaManager.listMedia();
                break;
            case 6:
                mediaManager.rentMedia(clientManager);
                break;
            case 7:
                mediaManager.returnMedia(clientManager);
                break;
            case 8:
                clientManager.listBorrowedMedia();
                break;
            case 9:
                std::cout << "Au revoir !\n";
                return;
            default:
                std::cout << "Choix invalide.\n";
            }
            system("pause");
        }
    }
}

int main() {
    ClientManager clientManager;
    MediaManager mediaManager;
    mainMenu(clientManager, mediaManager);
}