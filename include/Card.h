#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <string>

class Card {
private:
    char family_;
    std::string name_;
    int value_;
    sf::Sprite sprite;

    

public:
    // Constructor
    Card(char family, std::string name, int value, sf::Texture& texture);

    char getFamily() const;
    
    std::string getName() const;

    int getValue() const;

    void setPosition (float x, float y);

    sf::Sprite& getSprite();
};

#endif // CARD_H
