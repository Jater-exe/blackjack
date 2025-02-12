#include "main.hpp"

/*SPRITE TEXTURE SIZES
* CARD BACKGROUND:60x40 (2 items)
* FAMILIES:16x16 (4 items)
* RED/BLACK VALS: 8x8 (13 items each)
* BUTTONS: 16x48 (3 items)
*
* Resizable in Piskel
*/


int main() {
	unsigned int width = 1280;
	unsigned int height = 720;
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Intro to SFML");
	window->setFramerateLimit(60);

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

	//Create sprites
	sf::Sprite card(card_background);
	sf::IntRect face[2];
	face[0] = sf::IntRect({ {0,0}, {40,60} });
	face[1] = sf::IntRect({ {40, 0}, {40, 60} });
	card.setTextureRect(face[back]);
	card.setOrigin({ 20,30 });
	//card.setPosition({ width / 2.0f, height / 2.0f });

	sf::Sprite number(black_vals);
	sf::IntRect value[10];
	for (int i = 0; i < 10; i++) {
		value[i] = sf::IntRect({{8*i,0}, {8, 8}});
	}

	//Game setup
	int balance = 500;
    int bet;
    Deck main_deck = unshuffled_deck();
    shuffle(main_deck);

    int current_pos = 0;
    std::cout << "Insert bet: ";

	while (window->isOpen()) {
		while (const std::optional event = window->pollEvent()) {
			if (event->is < sf::Event::Closed>()) {
				window->close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
					window->close();
				}
			}
		}

		std::vector<int> separated_balance = int_to_vec(balance);
		int length = separated_balance.size();
		std::vector<sf::Sprite> balance_displayed(length);
		for (int i = 0; i < length; i++) {
			balance_displayed[i] = number;
			balance_displayed[i].setTextureRect(value[separated_balance[i]-1]);
		}



		//Render
		window->clear(sf::Color(0x509127FF));


		//Draw
		window->draw(card);
		window->display();
	}

	delete window;
	return 0;
}