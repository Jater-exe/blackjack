#ifndef GAME_H
#define GAME_H

#include <vector>
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <algorithm>
#include "Card.hh"  // If game logic involves cards

typedef std::vector<Card> Deck;

class Game {
public:
    Game();
    void run();  // Main game loop

private:
    bool running_;
    // Vectors for sprites (or any other game objects)
    sf::RenderWindow window;
    Deck deck;
    Deck player_cards;
    Deck dealer_cards;
    std::map<std::string, sf::Texture> textures;
    //true -> input bet stage | false -> decision stage
    bool game_seq = false;
    bool hit_bet = false;
    bool double_bet = false;
    bool stand = false;
    bool increment_bet = false;
    bool decrease_bet = false;
    bool endround = false;
    int balance = 500;
    int bet;
    int active_pos = 0; 

    
    // Private methods to handle events, update game state, render, etc.
    void processEvents();
    void update();
    void render();
    Deck unshuffled_deck();
    void shuffle(Deck& unshuffled);
    int random_num();
    void key_actions(sf::Event& event);
    void swap(Deck d, int pos1, int pos2);
    void check_end_round();
    int count_aces(Deck& d);
    void endround_seq();
    void active_pos_sum();
    int cards_sum(Deck& d);
    void reset();

};

#endif // GAME_H
