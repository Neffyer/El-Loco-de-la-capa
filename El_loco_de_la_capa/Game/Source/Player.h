#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "App.h"
#include "Entity.h"
#include "Point.h"
#include "SDL/include/SDL.h"
#include "Animation.h"

struct SDL_Texture;

class Player : public Entity
{
public:

	Player();

	virtual ~Player();

	bool Awake();

	bool Start();

	bool Update();

	bool CleanUp();

	void OnCollision(PhysBody* physA, PhysBody* physB);

public:

	bool godMode = false;
	bool idle = true;
	bool playerAlive;
	bool onAir;
	bool finish = true;
	bool attacking = false;
	int jumps;
	int dashes;
	bool holdingAnimation = false;
	float startx;
	float starty;
	uint jumpFx = 0;
	uint attackFx = 0;
	uint coinFx = 0;
	uint hitFx = 0;
	uint hpFx = 0;

	PhysBody* pbody;
	int hits;
	int coins;

	int pickCoinFxId;

private:

	//L02: DONE 1: Declare player parameters
	SDL_Texture* texture;
	const char* texturePath;

	// L07 TODO 5: Add physics to the player - declare a Physics body

	float speed = 4.0;
	float impulse = 7.0;

	//Animations
	Animation* currentAnimation;

	Animation PlayerIdleRight;
	Animation PlayerIdleLeft;
	Animation RunningRight;
	Animation RunningLeft;
	Animation StartJumpRight;
	Animation StartJumpLeft;
	Animation FlyRight;
	Animation FlyLeft;
	Animation LandRight;
	Animation LandLeft;
	Animation DieRight;
	Animation DieLeft;
	Animation PlayerAttackRight;
	Animation PlayerAttackLeft;
};

#endif // __PLAYER_H__