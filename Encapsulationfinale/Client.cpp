#include "Client.h"

Client::Client(std::string name, std::string firstname, int age, std::string address, std::string phoneNumber, std::string email)
    : name(name), firstname(firstname), age(age), address(address), phoneNumber(phoneNumber), email(email) {
}

std::string Client::getName() const { return name; }
std::string Client::getFirstname() const { return firstname; }
int Client::getAge() const { return age; }
std::string Client::getEmail() const { return email; }

void Client::borrowMedia(const std::string& media) {
    borrowedMedia.push_back(media);
}

void Client::returnMedia(const std::string& media) {
    borrowedMedia.erase(std::remove(borrowedMedia.begin(), borrowedMedia.end(), media), borrowedMedia.end());
}

std::vector<std::string> Client::getBorrowedMedia() const {
    return borrowedMedia;
}