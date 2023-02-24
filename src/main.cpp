#include <cstdlib>
#include <iostream>
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "line.hpp"
#include "physics.hpp"

// assume a < b, generate random number in [a,b)
int randnum(int a, int b) {
	if (a==b) return a;
	return a + (rand()) % (b-a);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	sf::Clock clock;

	srand((unsigned)time(NULL));

	Particle* part1 = new Particle(15.f, sf::Color::Blue);
	part1->mass = 5000.f;
	part1->pos += vec2(500.f, 300.f);
	part1->vel += vec2(-200.f, 100.f);
	Particle* part2 = new Particle(8.f, sf::Color::Blue);
	part2->mass = 1000.f;
	part2->pos += vec2(200.f, 300.f);
	part2->vel += vec2(200.f, 100.f);

	Scene scene = Scene(&window);
	scene.gravitational_pull = false;
	scene.bounding_box = true;
	scene.addObject(part1);
	scene.addObject(part2);
	
	bool pause = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				Particle* body = new Particle(30.f, sf::Color(randnum(100, 255),randnum(100, 255),randnum(100, 255)));
				body->mass += randnum(100, 800);
				body->pos += vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				body->vel += vec2(randnum(-200, 200), randnum(-200, 200));
				scene.addObject(body);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				int i = randnum(0, scene.objectsNumber());
				Object* obj = scene.getObject(i);
				scene.removeObject(obj);

				// pause = true;
			}
        }

		scene.render(window);
		scene.step(clock.restart().asSeconds(), &window, pause);

		if (pause) {
			// std::cout << scene.getObject(0)->pos << std::endl;
			char i = std::cin.get();
			if (i == 'r') pause = false;
			clock.restart();
		}

		// std::cout << part1->pos << " - " << part2->pos << " => " << vec2::distance(part1->pos, part2->pos) << " - " << part1->shape.getRadius() + part2->shape.getRadius() << std::endl;

        window.display();
    }

    return 0;
}
