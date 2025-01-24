#ifndef MOVIE_H
#define MOVIE_H
#include "Media.h"

class Movie : public Media {
private:
    std::string format; // Blu-ray ou DVD
    int ageLimit;

public:
    Movie(std::string title);
    void inputDetails() override;
    int getAgeLimit() const { return ageLimit; }
};

#endif