#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H
#include <vector>
#include "Client.h"


class ClientManager {
private:
    std::vector<Client> clients;
   

public:
    void addClient();
    void removeClient();
    void listBorrowedMedia() const;
    void listClients() const;
    std::vector<Client>& getClients() {
        return clients;
    }
};

#endif