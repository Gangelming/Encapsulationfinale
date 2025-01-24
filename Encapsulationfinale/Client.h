#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <vector>

class Client {
private:
    std::string name;
    std::string firstname;
    int age;
    std::string address;
    std::string phoneNumber;
    std::string email;
    std::vector<std::string> borrowedMedia;


public:
    Client(std::string name, std::string firstname, int age, std::string address, std::string phoneNumber, std::string email);

    std::string getName() const;
    std::string getFirstname() const;
    int getAge() const;
    std::string getEmail() const;

    void borrowMedia(const std::string& media);
    void returnMedia(const std::string& media);
    std::vector<std::string> getBorrowedMedia() const;

};

#endif