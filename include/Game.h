#ifndef GAME_H
#define GAME_H

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include "Card.h"  // If game logic involves cards

typedef std::vector<std::string> Deck;

class Game {
public:
    Game();
    void run();  // Main game loop

private:
    // Vectors for sprites (or any other game objects)
    sf::RenderWindow window;
    Deck deck;
    std::map<std::string, sf::Texture> textures;
    bool hit_bet = false;
    bool double_bet = false;
    bool stand = false;
    bool increment_bet = false;
    bool decrease_bet = false;

    
    // Private methods to handle events, update game state, render, etc.
    void processEvents();
    void update();
    void render();
    Deck unshuffled_deck();
    void shuffle(Deck& unshuffled);
    int random_num();
    void key_actions(sf::Event& event);
};

#endif // GAME_H
