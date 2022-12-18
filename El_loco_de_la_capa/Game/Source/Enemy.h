#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

struct SDL_Texture;

class Enemy : public Entity
{
public:

	Enemy();

	virtual ~Enemy();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

public:

	bool debug;
	bool idleEnemy = true;
	bool holdingAnimation = false;
	bool enemyAlive;
	float startx;
	float starty;
	bool goingRight = true;
	bool goingLeft = false;
	uint enemyDeathFx = 0;

	PhysBody* pbodyEnemy;

private:

	//L02: DONE 1: Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	// L07 TODO 5: Add physics to the player - declare a Physics body

	float speed = 2.0;
	float impulse = 7.0;

	//Animations
	Animation* currentAnimation;

	Animation EnemyWalkRight;
	Animation EnemyWalkLeft;

};

#endif // __ENEMY_H__
