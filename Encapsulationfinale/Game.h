#ifndef GAME_H
#define GAME_H
#include "Media.h"

class Game : public Media {
private:
    std::string studio;
    int ageLimit;
    std::string genre;

public:
    Game(std::string title);
    void inputDetails() override;
    int getAgeLimit() const { return ageLimit; } // Ajoutez cette ligne
};

#endif

