#ifndef BOOK_H
#define BOOK_H
#include "Media.h"

class Book : public Media {
private:
    std::string isbn;

public:
    Book(std::string title);
    void inputDetails() override;
};

#endif