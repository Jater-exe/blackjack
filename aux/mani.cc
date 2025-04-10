#include "mani.hh"


/*SPRITE TEXTURE SIZES
* CARD BACKGROUND:60x40 (2 items)
* FAMILIES:16x16 (4 items)
* RED/BLACK VALS: 8x8 (13 items each)
* BUTTONS: 16x48 (3 items)
* NUMBERS; 8x8 (10 items)
*
* Resizable in Piskel
*/


int main() {
	unsigned int width = 1280;
	unsigned int height = 720;
	sf::RenderWindow window(sf::VideoMode(width, height), "Blackjack");
	window.setFramerateLimit(60);

	
	//Load textures
	sf::Texture card_background;
	if (!card_background.loadFromFile("Sprites/card_background.png")) {
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/card_background.png" << std::endl;
		return -1;
	}

	sf::Texture families;
	if (!families.loadFromFile("Sprites/families.png")) {
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/families.png" << std::endl;
		return -1;
	}

	sf::Texture red_vals;
	if (!red_vals.loadFromFile("Sprites/red_vals.png")) {
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/red_vals.png" << std::endl;
		return -1;
	}

	sf::Texture black_vals;
	if (!black_vals.loadFromFile("Sprites/black_vals.png")) {
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/black_vals.png" << std::endl;
		return -1;
	}

	sf::Texture buttons;
	if (!buttons.loadFromFile("Sprites/buttons.png")) {
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/buttons.png" << std::endl;
		return -1;
	}

	sf::Texture nums;
	if (!nums.loadFromFile("Sprites/nums.png")) {
		std::cerr << "ERROR::COULD NOT LOAD FILE::Sprites/nums.png" << std::endl;
		return -1;
	}

	//Create sprites
	sf::Sprite card(card_background);
	sf::IntRect face[2];
	face[0] = sf::IntRect({ {0,0}, {40,60} });
	face[1] = sf::IntRect({ {40, 0}, {40, 60} });
	card.setTextureRect(face[back]);
	card.setOrigin({ 20,30 });
	card.setPosition({ width / 2.0f, height / 2.0f });

	//IntRect for numbers (balance)
	sf::IntRect value[10];
	for (int i = 0; i < 10; i++) {
		value[i] = sf::IntRect({{0, 8*i}, {8, 8}});
	}

	//IntRect for action buttons buttons
	sf::IntRect action[3];
	for (int i = 0; i < 3; i++) {
		action[i] = sf::IntRect({{48*i, 0}, {48, 16}});
	}
	
	//Game setup
	int balance = 500;
    int bet;
    Deck main_deck = unshuffled_deck();
    shuffle(main_deck);

    int current_pos = 0;

	while (window.isOpen()) {

		//event management
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}




		//balance display
		std::vector<int> separated_balance = int_to_vec(balance);
		int length = separated_balance.size();
		std::vector<sf::Sprite> balance_displayed(length);

		for (int i = 0; i < length; i++) {
			balance_displayed[i].setTexture(nums);
			switch (separated_balance[i]) {
			case 0:
				balance_displayed[i].setTextureRect(value[Zero]);
				break;
			case 1:
				balance_displayed[i].setTextureRect(value[One]);
				break;
			case 2:
				balance_displayed[i].setTextureRect(value[Two]);
				break;
			case 3:
				balance_displayed[i].setTextureRect(value[Three]);
				break;
			case 4:
				balance_displayed[i].setTextureRect(value[Four]);
				break;
			case 5:
				balance_displayed[i].setTextureRect(value[Five]);
				break;
			case 6:
				balance_displayed[i].setTextureRect(value[Six]);
				break;
			case 7:
				balance_displayed[i].setTextureRect(value[Seven]);
				break;
			case 8:
				balance_displayed[i].setTextureRect(value[Eight]);
				break;
			case 9:
				balance_displayed[i].setTextureRect(value[Nine]);
				break;
			default:
				break;
			}
			balance_displayed[i].setPosition({(width / 1.5f) + i*8, height / 1.5f});
		}
		
		//buttons display
		std::vector<sf::Sprite> action_buttons(3);
		for (int i = 0; i < 3; i++) {
			action_buttons[i].setTexture(buttons);
			action_buttons[i].setPosition({width/10.0f +i*48, height/1.2f});
		}
		action_buttons[0].setTextureRect(action[hit]);
		action_buttons[1].setTextureRect(action[d_down]);
		action_buttons[2].setTextureRect(action[stand]);

		//active cards display
		//std::vector<sf::Sprite> 



		//Render
		window.clear(sf::Color(0x50912700));
		window.draw(card);
		for (int i = 0; i < length; ++i) {
			window.draw(balance_displayed[i]);
		}
		for (int i = 0; i < 3; ++i) window.draw(action_buttons[i]);


		//Draw
		//window.draw(card);
		window.display();
	}
	return 0;
}