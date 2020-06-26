#include <iostream>
#include "crossroads.h"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <string>

using namespace std;

// рисует прекресток
void drawCrossraods(sf::RenderWindow& window);
// рисует машинки
void drawCar(sf::RenderWindow& window, queue<Car*>* way);
// пишет длину очереди машин для каждого направления
void writeQueueSize(sf::RenderWindow& window, queue<Car*>* way, float x, float y);

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	Crossroad myCrossroad(ROAD_WIDTH);
	myCrossroad.createCars();


	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossroads");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// main loop
		while (myCrossroad.load() > 0)
		{
			myCrossroad.traffic();
			window.clear();

			drawCrossraods(window);

			drawCar(window, myCrossroad.getUpQueue());
			drawCar(window, myCrossroad.getDownQueue());
			drawCar(window, myCrossroad.getRightQueue());
			drawCar(window, myCrossroad.getLeftQueue());

			writeQueueSize(window, myCrossroad.getUpQueue(), 525.f, 510.f);
			writeQueueSize(window, myCrossroad.getDownQueue(), 480.f, 200.f);
			writeQueueSize(window, myCrossroad.getRightQueue(), 300.f, 386.f);
			writeQueueSize(window, myCrossroad.getLeftQueue(), 660.f, 340.f);

			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		//-----------------
	}

	return 0;
}

void drawCrossraods(sf::RenderWindow& window)
{

	sf::Vertex line1[] =
	{
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2, 0)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - ROAD_WIDTH))
	};
	sf::Vertex line2[] =
	{
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + ROAD_WIDTH)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT))
	};


	sf::Vertex line3[] =
	{
		sf::Vertex(sf::Vector2f(0, SCREEN_HEIGHT / 2)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 - ROAD_WIDTH, SCREEN_HEIGHT / 2))
	};
	sf::Vertex line4[] =
	{
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 + ROAD_WIDTH, SCREEN_HEIGHT / 2)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2))
	};


	sf::Vertex line5[] =
	{
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 - ROAD_WIDTH, 0)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 - ROAD_WIDTH, SCREEN_HEIGHT / 2 - ROAD_WIDTH))
	};
	sf::Vertex line6[] =
	{
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 + ROAD_WIDTH, 0)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 + ROAD_WIDTH, SCREEN_HEIGHT / 2 - ROAD_WIDTH))
	};

	sf::Vertex line7[] =
	{
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 - ROAD_WIDTH, SCREEN_HEIGHT / 2 + ROAD_WIDTH)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 - ROAD_WIDTH, SCREEN_HEIGHT))
	};
	sf::Vertex line8[] =
	{
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 + ROAD_WIDTH, SCREEN_HEIGHT / 2 + ROAD_WIDTH)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 + ROAD_WIDTH, SCREEN_HEIGHT))
	};

	sf::Vertex line9[] =
	{
		sf::Vertex(sf::Vector2f(0, SCREEN_HEIGHT / 2 - ROAD_WIDTH)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 - ROAD_WIDTH, SCREEN_HEIGHT / 2 - ROAD_WIDTH))
	};
	sf::Vertex line10[] =
	{
		sf::Vertex(sf::Vector2f(0, SCREEN_HEIGHT / 2 + ROAD_WIDTH)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 - ROAD_WIDTH, SCREEN_HEIGHT / 2 + ROAD_WIDTH))
	};

	sf::Vertex line11[] =
	{
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 + ROAD_WIDTH, SCREEN_HEIGHT / 2 - ROAD_WIDTH)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2 - ROAD_WIDTH))
	};
	sf::Vertex line12[] =
	{
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH / 2 + ROAD_WIDTH, SCREEN_HEIGHT / 2 + ROAD_WIDTH)),
		sf::Vertex(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT / 2 + ROAD_WIDTH))
	};

	window.draw(line1, 2, sf::Lines);
	window.draw(line2, 2, sf::Lines);
	window.draw(line3, 2, sf::Lines);
	window.draw(line4, 2, sf::Lines);
	window.draw(line5, 2, sf::Lines);
	window.draw(line6, 2, sf::Lines);
	window.draw(line7, 2, sf::Lines);
	window.draw(line8, 2, sf::Lines);
	window.draw(line9, 2, sf::Lines);
	window.draw(line10, 2, sf::Lines);
	window.draw(line11, 2, sf::Lines);
	window.draw(line12, 2, sf::Lines);

}

void drawCar(sf::RenderWindow& window, queue<Car*>* way)
{
	if (!way->empty())
	{
		auto x = SCREEN_WIDTH / 2.0 + way->front()->model.coordinates.x;
		auto y = SCREEN_HEIGHT / 2.0 + way->front()->model.coordinates.y;

		sf::RectangleShape rectangle(sf::Vector2f((float)way->front()->model.sizes.width, (float)way->front()->model.sizes.height));
		rectangle.setPosition((float)x, (float)y);

		window.draw(rectangle);
	}
}

void writeQueueSize(sf::RenderWindow& window, queue<Car*>* way, float x, float y)
{
	sf::Font font;
	font.loadFromFile("arialRegular.ttf");

	sf::Text text(to_string(way->size()), font);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);

	text.setPosition(x, y);

	window.draw(text);
}
