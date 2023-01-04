#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Window.hpp"
#include "line.hpp"
#include <cmath>
#include <algorithm>
#include <physics.hpp>


/* ~ Lerp and Antilerp ~
 *
 * -----a---c---------b------->
 * t<0  t=0           t=1  t>1
 *
 * get any value at t from a to b:
 *    c = a + (b-a)t
 * get t value for any c from a to b:
 *    t = (c-a)/(b-a)
 * */

float lerp(float a, float b, float t) {
	return a + (b-a)*t;
}
float antilerp(float a, float b, float c) {
	return (c-a)/(b-a);
}

vec2 lerp(vec2 a, vec2 b, float t) {
	return a + (b-a)*t;
}
float antilerp(vec2 a, vec2 b, vec2 c) {
	return (c.magnitude() - a.magnitude()) / (b.magnitude() - a.magnitude());
}


/* ~ Object ~
 * * * * * * */

Particle::Particle(float radius, sf::Color _color) {
	this->color = _color;
	this->shape = sf::CircleShape(radius);
}


/* ~ Scene ~
 * * * * * */

Scene::Scene(sf::RenderWindow* window) {
	this->bounding_box_dims = vec2(window->getSize().x, window->getSize().y);
}

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
		Particle* p = dynamic_cast<Particle*>(x);
		if (p == nullptr) continue;
		p->shape.setFillColor(p->color);
		p->shape.setPosition(sf::Vector2f(p->pos.x - p->shape.getRadius(), p->pos.y - p->shape.getRadius()));
		window.draw(p->shape);
		sf::Vertex velocity[] = {
			sf::Vector2f(p->pos.x, p->pos.y),
			sf::Vector2f(p->pos.x + p->vel.x, p->pos.y + p->vel.y),
		};
		window.draw(velocity, 2, sf::Lines);
	}
}

void Scene::step(float dt, sf::RenderWindow* window) {
	for (Object* obj : this->m_objects) {

		Particle* a = dynamic_cast<Particle*>(obj);
		if (!a || !this->bounding_box) goto jmp_bounding_box;
		if (a->pos.x - a->shape.getRadius() < 0) {
			a->pos.x = a->shape.getRadius();
			a->vel.x *= -1;
		} else if (a->pos.x + a->shape.getRadius() > this->bounding_box_dims.x) {
			a->pos.x = this->bounding_box_dims.x - a->shape.getRadius();
			a->vel.x *= -1;
		}
		if (a->pos.y - a->shape.getRadius() < 0) {
			a->pos.y = a->shape.getRadius();
			a->vel.y *= -1;
		} else if (a->pos.y + a->shape.getRadius() > this->bounding_box_dims.y) {
			a->pos.y = this->bounding_box_dims.y - a->shape.getRadius();
			a->vel.y *= -1;
		}
		jmp_bounding_box:

		// interactions
		for (Object* obj2 : this->m_objects) {
			if (obj == obj2) continue;
			if (this->gravitational_pull) {
				float dist = vec2::distance(obj->pos, obj2->pos);
				if (dist == 0.0) continue;
				vec2 distv = vec2::normalize(vec2::distancev(obj->pos, obj2->pos));
				obj->force += distv * ((obj->mass * obj2->mass) / (dist * dist)) * this->gravitational_constant;
			}

		}

		for (Object* obj2 : this->m_objects) {
			if (obj == obj2) continue;
			Particle* b = dynamic_cast<Particle*>(obj2);
			// both must be particles
			if (!a || !b) continue;
			bool collision = false;
#define p1 (a->pos)
#define p2 (b->pos)
#define v1 (a->vel)
#define v2 (b->vel)
#define m1 (a->mass)
#define m2 (b->mass)
#define r1 (a->shape.getRadius())
#define r2 (b->shape.getRadius())

			vec2 u = v2 - v1;
			vec2 A = p2;
			vec2 B = p2 + u;
			vec2 k = vec2::normalize(u);
			float m = (B.y - A.y) / (B.x - A.x);
			vec2 H = vec2(
					(  (m*A.x + (1.f/m)*p1.x - A.y + p1.y) / (m/(m*m + 1))  ),
					(  (m*m+1)*(m*A.x + (1.f/m)*p1.x - A.y + p1.y) - m*A.x + A.y  ));
			float AH = vec2::distance(A,H);
			float C1H = Line::distancePointLine(p1, Line(A, B));
			float HP = sqrt((r1+r2)*(r1+r2) - C1H);

			vec2 P = A + k * (AH - HP) * dt;
			float t = antilerp(A, B, P);
			vec2 P2 = lerp(p2, p2+v2*dt, t);
			vec2 P1 = lerp(p1, p1+v1*dt, t);

			sf::Vertex line[] = {
				sf::Vector2f(p2.x, p2.y),
				sf::Vector2f(p2.x + u.x, p2.y + u.y),
			};
			sf::CircleShape Pc(10.f);
			Pc.setFillColor(sf::Color::Green);
			Pc.setPosition(P.x, P.y);
			sf::CircleShape P1c(5.f);
			P1c.setFillColor(sf::Color::Red);
			P1c.setPosition(P1.x, P1.y);
			sf::CircleShape P2c(5.f);
			P2c.setFillColor(sf::Color::Red);
			P2c.setPosition(P2.x, P2.y);

			window->draw(Pc);
			window->draw(P1c);
			window->draw(P2c);
			window->draw(line, 2, sf::Lines);

			if (C1H < r1+r2 && t >= 0.0f && t <= 1.0f) {
				collision = true;
				std::cout << "P1,P2: " << P1 << " - " << P2 << std::endl;
				std::cout << "p1,p2: " << p1 << " - " << p2 << std::endl;
			}

			// if (vec2::distance(a->pos, b->pos) < a->shape.getRadius() + b->shape.getRadius()) {
			if (collision) {
				p1 = P1;
				p2 = P2;
				v1 = (  v1 - (p1-p2) * vec2::dot(v1-v2,p1-p2)/((p1-p2).magnitude() * (p1-p2).magnitude()) * 2*m2/(m1+m2)  );
				v2 = (  v2 - (p2-p1) * vec2::dot(v2-v1,p2-p1)/((p2-p1).magnitude() * (p2-p1).magnitude()) * 2*m1/(m1+m2)  );
#undef p1
#undef p2
#undef v1
#undef v2
#undef m1
#undef m2
#undef r1
#undef r2
			}
		}

		// if the object is static, no force/velocity should affect it
		if (obj->is_static) {
			obj->force = vec2(0.f, 0.f);
			obj->vel = vec2(0.f, 0.f);
		}

		obj->vel += (obj->force / obj->mass) * dt;
		obj->pos += obj->vel * dt;

		// reset net force
		obj->force = vec2(0.f, 0.f);

	}
}

Scene::~Scene() {
	for (Object* x : this->m_objects) {
		delete x;
	}
}
