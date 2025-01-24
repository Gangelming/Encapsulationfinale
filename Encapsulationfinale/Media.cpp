#include "Media.h"

Media::Media(std::string title) : title(title), isBorrowed(false) {}

std::string Media::getTitle() const { return title; }

bool Media::getIsBorrowed() const { return isBorrowed; }

void Media::borrow() { isBorrowed = true; }

void Media::returnMedia() { isBorrowed = false; }

