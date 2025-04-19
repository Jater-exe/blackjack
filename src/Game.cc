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

	player_cards = {deck[active_pos], deck[active_pos+1]};
	dealer_cards = {deck[active_pos+2]};
	active_pos += 3;
}

void Game::run() {

	while (true) {
        //processEvents();
        //update();
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
    if (hit_bet) {
		player_cards.push_back(deck[active_pos]);
		active_pos_sum();
		hit_bet = false;
	}
	else if (double_bet) {
		if (balance >= bet) {
			bet *= 2;
			balance -= bet;
			player_cards.push_back(deck[active_pos]);
			active_pos_sum();
		}
		double_bet = false;
	}
	else if (stand) {
		endround = true;
		stand = false;
	}
	else if (increment_bet) {
		if (balance-bet >= 1) {
			bet++;
			balance--;
		}
		increment_bet = false;
	}
	else if (decrease_bet) {
		if (bet > 1) {
			bet--;
			balance++;
		}
		decrease_bet = false;
	}
	check_end_round();
	if (endround) {
		endround_seq();
	}
}

void Game::render() {
	window.clear(sf::Color(0x50912700));
	window.draw(deck[0].getSprite());
	window.display();

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
				break;
			case 1:
				family = 'S';
				break;
			case 2:
				family = 'D';
				break;
			case 3:
				family = 'C';
				break;
		}
		int set_value = i%13;
		switch (set_value) {
			case 0:
				name = "Ace";
				value = 11;
				break;
			case 1:
				name = "Two";
				value = 2;
				break;
			case 2:
				name = "Three";
				value = 3;
				break;
			case 3:
				name = "Four";
				value = 4;
				break;
			case 4:
				name = "Five";
				value = 5;
				break;
			case 5:
				name = "Six";
				value = 6;
				break;
			case 6:
				name = "Seven";
				value = 7;
				break;
			case 7:
				name = "Eight";
				value = 8;
				break;
			case 8:
				name = "Nine";
				value = 9;
				break;
			case 9:
				name = "Ten";
				value = 10;
				break;
			case 10:
				name = "Jack";
				value = 10;
				break;
			case 11:
				name = "Queen";
				value = 10;
				break;
			case 12:
				name = "King";
				value = 10;
				break;
		}
		Card c(family, name, value)
	}
	return result;
}

void Game::shuffle(Deck& unshuffled) {
    for (int i = 0; i < unshuffled.size(); i++) {
        swap(unshuffled, i, random_num());
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

void Game::swap(Deck d, int pos1, int pos2) {
	Card c = d[pos1];
	d[pos1] = d[pos2];
	d[pos2] = c;
}

void Game::check_end_round() {
	int player_aces = count_aces(player_cards);
	int player_sum = 0;
	for (int i = 0; i < player_cards.size(); ++i) {
		player_sum += player_cards[i].getValue();
	}
	while (player_sum > 21 && player_aces > 0) {
		player_sum -= 10;
		player_aces--;
	}
	if (player_sum > 21) {
		endround = true;
	}
	
}

void Game::endround_seq() {
	int dealer_sum = 0;
	int dealer_aces = 0;
	if (dealer_cards[0].getName() == "Ace") dealer_aces++;
	while (dealer_sum < 17) {
		dealer_cards.push_back(deck[active_pos]);
		active_pos_sum();
		if (dealer_cards.back().getName() == "Ace") dealer_aces++;
		dealer_sum += dealer_cards.back().getValue();
		while (dealer_sum > 21 && dealer_aces > 0) {
			dealer_sum -= 10;
			dealer_aces--;
		}
	}
	if (dealer_sum > 21) {
		if (cards_sum(player_cards) > 21) {
			balance += bet;
			bet = 0;
		}
		else {
			balance += 1.5*bet;
			bet = 0;
		}
	}
	else {
		if (cards_sum(player_cards) > 21) {
			bet = 0;
		}
		else {
			balance += 1.5*bet;
			bet = 0;
		}
	}
	reset();
}

int count_aces(Deck& d) {
	int result = 0;
	for (int i = 0; i < d.size(); ++i) {
		if (d[i].getName() == "Ace") result++;
	}
	return result;
}

void Game::active_pos_sum() {
	if (active_pos == 51) active_pos = 0;
	else active_pos++;
}

int Game::cards_sum(Deck& d) {
	int d_aces = 0;
	int result = 0;
	for (int i = 0; i < d.size(); ++i) {
		if (d[i].getName() == "Ace") d_aces++;
		result += d[i].getValue();
	}
	while (result > 21 && d_aces > 0) {
		d_aces--;
		result -= 10;
	}
	return result;
}

void Game::reset() {
	shuffle(deck);
	active_pos = 0;
	player_cards = {deck[active_pos], deck[active_pos+1]};
	dealer_cards = {deck[active_pos+2]};
	active_pos += 3;
}