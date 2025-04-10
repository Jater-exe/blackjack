#include "../include/Card.h"

Card::Card(char family, std::string name, int value, sf::Texture& texture)
    : family_(family), name_(name), value_(value) {
        sprite.setTexture(texture);
    }

char Card::getFamily() const {
    return family_;
}

std::string Card::getName() const {
    return name_;
}

int Card::getValue() const {
    
    return value_;
}

void Card::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}
sf::Sprite& Card::getSprite() {
    return sprite;
}