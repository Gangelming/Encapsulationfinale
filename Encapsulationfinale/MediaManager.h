#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H
#include <vector>
#include "Media.h"
#include "Game.h"
#include "Book.h"
#include "Movie.h"
#include "ClientManager.h"

class MediaManager {
private:
    std::vector<Media*> medias;

public:
    ~MediaManager();
    void addMedia();
    void removeMedia();
    void listMedia() const;
    void rentMedia(ClientManager& clientManager);
    void returnMedia(ClientManager& clientManager);
    std::vector<std::string> getMediaTitles() const;
    std::vector<std::string> getAvailableMediaTitles() const;
    std::vector<std::string> getBorrowedMediaTitles() const;
};
#endif