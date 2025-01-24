#ifndef MEDIA_H
#define MEDIA_H
#include <string>

class Media {
protected:
    std::string title;
    bool isBorrowed;

public:
    Media(std::string title);
    virtual ~Media() = default;

    virtual void inputDetails() = 0; // Méthode virtuelle pure pour les sous-classes

    std::string getTitle() const;
    bool getIsBorrowed() const;
    void borrow();
    void returnMedia();
};

#endif
