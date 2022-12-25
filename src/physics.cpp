#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Window.hpp"
#include <algorithm>
#include <physics.hpp>


/* ~ Object ~
 * * * * * * */

Body::Body(float radius, sf::Color _color) {
	this->color = _color;
	this->shape = sf::CircleShape(radius);
}
// vec2 Object::position() { return this->pos; }
// void Object::setPosition(vec2 new_pos) { this->pos = new_pos; }
// vec2 Object::velocity() { return this->vel; }
// void Object::setVelocity(vec2 new_vel) { this->vel = new_vel; }


/* ~ Scene ~
 * * * * * */

void Scene::addObject(Object *obj) {
	this->m_objects.push_back(obj);
}

void Scene::removeObject(Object* obj) {
	if (!obj) return;
	auto itr = std::find(this->m_objects.begin(), this->m_objects.end(), obj);
	if (itr == this->m_objects.end()) return;
	this->m_objects.erase(itr);
}

Object* Scene::getObject(int index) {
	return this->m_objects[index];
}

int Scene::objectsNumber() {
	return this->m_objects.size();
}

void Scene::render(sf::RenderWindow& window) {
	window.clear(this->clear_color);
	for (Object* x : this->m_objects) {
		Body* b = dynamic_cast<Body*>(x);
		if (b == nullptr) continue;
		b->shape.setFillColor(b->color);
		b->shape.setPosition(sf::Vector2f(b->pos.x, b->pos.y));
		window.draw(b->shape);
	}
}

void Scene::step(float dt) {
	for (Object* obj : this->m_objects) {
		for (Object* obj2 : this->m_objects) {
			float dist = vec2::distance(obj->pos, obj2->pos);
			if (dist == 0.0) continue;
			vec2 distv = vec2::normalize(vec2::distancev(obj->pos, obj2->pos));
			obj->force += distv * ((obj->mass * obj2->mass) / (dist * dist));
		}

		if (obj->is_static) {
			obj->force = vec2(0.f, 0.f);
			obj->vel = vec2(0.f, 0.f);
		}

		// obj->force += this->gravity * obj->mass;
		obj->vel += (obj->force / obj->mass) * dt;
		obj->pos += obj->vel * dt;

		// impulse != thrust. Impulse resets, thrust is continuous.
		obj->force = vec2(0.f, 0.f);
	}
}

Scene::~Scene() {
	for (Object* x : this->m_objects) {
		delete x;
	}
}
