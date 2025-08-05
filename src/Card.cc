#include "../include/Card.hh"

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