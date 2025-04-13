#include "../include/Game.h"


/*SPRITE TEXTURE SIZES
* CARD:60x40 (13x4 items)
* FAMILIES:16x16 (4 items)
* RED/BLACK VALS: 8x8 (13 items each)
* BUTTONS: 16x48 (3 items)
* NUMBERS; 8x8 (10 items)
*
* Resizable in Piskel
*/

Game::Game() : window(sf::VideoMode(1280, 720), "Blackjack") {
	unsigned int width = 1280;
    unsigned int height = 720;
	
    //Initialize
	window.setFramerateLimit(60);
    
    //Load textures
    sf::Texture card_background;
	if (!card_background.loadFromFile("Sprites/card_background.png")) {
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/card_background.png" << std::endl;
	}

	sf::Texture buttons;
	if (!buttons.loadFromFile("Sprites/buttons.png")) {
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/buttons.png" << std::endl;
	}

	sf::Texture nums;
	if (!nums.loadFromFile("Sprites/nums.png")) {
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/nums.png" << std::endl;
	}
	sf::Texture cards;
	if (!cards.loadFromFile("Sprites/cards.png")) {
		std::cerr << "ERROR COULD NOT LOAD FILE::Sprites/cards.png" << std::endl;
	}
	textures["card_background"] = card_background;
	textures["buttons"] = buttons;
	textures["nums"] = nums;
	textures["cards"] = cards;

	deck = unshuffled_deck();
	shuffle(deck);
}

void Game::run() {

	while (true) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::KeyPressed) {
			key_actions(event);
		}
	}
}

void Game::update() {
    if (hit_bet) {}
	else if (double_bet) {}
	else if (stand) {}
	else if (increment_bet) {}
	else if (decrease_bet) {}
}

void Game::render() {
    // Render sprites, cards, etc.
}

Deck Game::unshuffled_deck() {
	Deck result(52);
	for (int i = 0; i < 52; ++i) {
		char family;
		int value;
		std::string name;
		int suit = i%4;
		switch(suit) {
			case 0:
				family = 'H';
		}
	}
	return result;
}

void Game::shuffle(Deck& unshuffled) {
    for (int i = 0; i < unshuffled.size(); i++) {
        swap(unshuffled[i], unshuffled[random_num()]);
    }
}

int Game::random_num() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(0, 51);
    return distrib(gen);
}

void Game::key_actions(sf::Event& event){
	switch (event.key.scancode) {
		case sf::Keyboard::Scan::Escape:
			window.close();
			break;
		case sf::Keyboard::Scan::H:
			hit_bet = true;
			double_bet = false;
			stand = false;
			increment_bet = false;
			decrease_bet = false;
			break;
		case sf::Keyboard::Scan::D:
			hit_bet = false;
			double_bet = true;
			stand = false;
			increment_bet = false;
			decrease_bet = false;
			break;
		case sf::Keyboard::Scan::S:
			hit_bet = false;
			double_bet = false;
			stand = true;
			increment_bet = false;
			decrease_bet = false;
			break;
		case sf::Keyboard::Scan::Right:
			hit_bet = false;
			double_bet = false;
			stand = false;
			increment_bet = true;
			decrease_bet = false;
			break;
		case sf::Keyboard::Scan::Left:
			hit_bet = false;
			double_bet = false;
			stand = false;
			increment_bet = false;
			decrease_bet = true;
			break;
		default:
			break;
	}
}