#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include <vector>
#include <vec.hpp>

struct Object {
	bool is_static = false;
	float mass = 1.f;
	vec2 pos = vec2(0.f, 0.f);
	vec2 vel = vec2(0.f, 0.f);
	vec2 force = vec2(0.f, 0.f);

	Object() = default;
	Object(float m, vec2 p, vec2 v, vec2 f, bool is)
		: is_static(is), mass(m), pos(p), vel(v), force(f)
	{}
	virtual ~Object() = default;
};

struct Particle : Object {
	sf::Color color;
	sf::CircleShape shape;

	Particle(float radius, sf::Color color);
	virtual ~Particle() = default;

	static bool collide(const Particle *const a, const Particle *const b);
	static void resolveCollsion(const Particle* a, const Particle* b);
};


class Scene {
private:
	std::vector<Object*> m_objects;
public:
	bool gravitational_pull = true;
	bool bounding_box = false;

	vec2 bounding_box_dims;

	float gravitational_constant = 1000.f;
	sf::Color clear_color = sf::Color::Cyan;

public:
	Scene(sf::RenderWindow* window);
	~Scene();

	void addObject(Object* obj);
	void removeObject(Object* obj);
	Object* getObject(int index);
	int objectsNumber();
	void render(sf::RenderWindow& window);
	void step(float dt, sf::RenderWindow* window, bool& pause);
};
