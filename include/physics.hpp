#pragma once
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include <vector>
#include <vec.hpp>

#include <SFML/Graphics.hpp>


struct Object {
	float mass = 1.f;
	vec2 pos = vec2(0.f, 0.f);
	vec2 vel = vec2(0.f, 0.f);
	vec2 force = vec2(0.f, 0.f);
	bool is_static = false;

	Object() = default;
	Object(float m, vec2 p, vec2 v, vec2 f, bool is) : mass(m), pos(p), vel(v), force(f), is_static(is) {}
	virtual ~Object() = default;
};

struct Body : Object {
	sf::Color color;
	sf::CircleShape shape;

	Body(float radius, sf::Color color);
	virtual ~Body() = default;
};


class Scene {
private:
	std::vector<Object*> m_objects;
public:
	vec2 gravity = vec2(0.f, 981.f);
	sf::Color clear_color = sf::Color::Black;

public:
	Scene() = default;
	~Scene();

	void addObject(Object* obj);
	void removeObject(Object* obj);
	Object* getObject(int index);
	int objectsNumber();
	void render(sf::RenderWindow& window);
	void step(float dt);
};
