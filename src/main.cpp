#include <cstdlib>
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "physics.hpp"

// assume a < b, generate random number in [a,b)
int randnum(int a, int b) {
	if (a==b) return a;
	return a + (rand()) % (b-a);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::Clock clock;

	srand((unsigned)time(NULL));

	Body* body1 = new Body(15.f, sf::Color::Red);
	body1->mass = 1000000.f;
	body1->pos += vec2(300.f, 400.f);
	body1->vel += vec2(0.f, -30.f);
	Body* body2 = new Body(15.f, sf::Color::Green);
	body2->mass = 1000000.f;
	body2->pos += vec2(500.f, 400.f);
	body2->vel += vec2(0.f, 30.f);

	Scene scene = Scene();
	scene.addObject(body1);
	scene.addObject(body2);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				Body* body = new Body(10.f, sf::Color(randnum(100, 255),randnum(100, 255),randnum(100, 255)));
				body->mass += randnum(100000, 1000000);
				body->pos += vec2(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				body->vel += vec2(randnum(-800, 800), randnum(-800, 800));
				scene.addObject(body);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				int i = randnum(0, scene.objectsNumber());
				Object* obj = scene.getObject(i);
				scene.removeObject(obj);
			}
        }

		scene.step(clock.restart().asSeconds());
		scene.render(window);

        window.display();
    }

    return 0;
}
