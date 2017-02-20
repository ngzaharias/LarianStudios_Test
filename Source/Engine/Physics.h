#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <functional>
#include <vector> 

class Actor;

struct HitInfo
{
	sf::Vector2f point;
	sf::Vector2f normal;
	Actor& actor;

	HitInfo(sf::Vector2f point, sf::Vector2f normal, Actor& actor)
		: point(point)
		, normal(normal)
		, actor(actor)
	{ }
};

class Physics
{
public:
	Physics();
	~Physics();

public:
	void Update();

	void CheckCollision(Actor& a, Actor& b);

	void RegisterDynamic(Actor* actor);
	void UnregisterDynamic(const Actor* actor);

	void RegisterStatic(Actor* actor);
	void UnregisterStatic(const Actor* actor);

private:
	std::vector<Actor*> m_dynamic;
	std::vector<Actor*> m_static;

};
#endif
//EOF