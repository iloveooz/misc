#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
	srand(time(nullptr));

	sf::RenderWindow window(sf::VideoMode(340, 340), "MAP");
	window.setFramerateLimit(60);

	int count = 0;
	int num;

	std::vector<sf::CircleShape> circle;

	sf::Font mFont;
	mFont.loadFromFile("C:\\git\\2017\\sfml_map\\Debug\\arial.ttf");

	std::vector<sf::Text> number;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			num = rand() % 10;
			number.push_back(sf::Text("", mFont, 10));
			number[count].setString(std::to_string(num));
			number[count].setPosition(25 + i * 40, 25 + j * 40);
			count++;
		}
	}

	count = 0;

	for (int k = 0; k < 8; k++) {
		for (int j = 0; j < 8; j++) {
			circle.push_back(sf::CircleShape(20));
			circle[count].setPosition(10 + k * 40, 10 + j * 40);
			circle[count].setOutlineColor(sf::Color::White);
			circle[count].setOutlineThickness(1);
			count++;
		}
	}

	while (window.isOpen()) {
		sf::Event event{};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		}

		for (int k = 0; k < 64; k++) {
			circle[k].setFillColor(sf::Color(204, 204, 204));
		}

		for (int k = 0; k < 64; k++) {
			window.draw(circle[k]);
			window.draw(number[k]);
		}
		window.display();
	}

	return 0;
}
