#include "Module.h"
#include "Enemy.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "Window.h"
#include "Animation.h"
#include "FadeToBlack .h"

Enemy::Enemy() : Entity(EntityType::ENEMY)
{
	name.Create("Enemy");

}

Enemy::~Enemy() {

}

bool Enemy::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	for (int i = 0; i < 8; i++) {

		EnemyWalkRight.PushBack({ 32 * (0 + i), 0, 32, 32 });
	}
	EnemyWalkRight.loop = true;
	EnemyWalkRight.speed = 0.1f;


	for (int i = 0; i < 8; i++) {

		EnemyWalkLeft.PushBack({ 32 * (0 + i), 32, 32, 32 });
	}
	EnemyWalkLeft.loop = true;
	EnemyWalkLeft.speed = 0.1f;
		
	return true;
}

bool Enemy::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	// L07 TODO 5: Add physics to the player - initialize physics body
	pbodyEnemy = app->physics->CreateCircle(position.x, position.y, 12, bodyType::DYNAMIC);

	pbodyEnemy->listener = this;
	pbodyEnemy->ctype = ColliderType::ENEMY;

	startx = position.x;
	starty = position.y;

	enemyAlive = true;

	//enemyDeathFx = app->audio->LoadFx("Assets/Audio/Fx/enemyDeath.wav");

	return true;
}


bool Enemy::Update()
{
	// L07 TODO 5: Add physics to the player - updated player position using physics

	b2Vec2 velocity = { 0, pbodyEnemy->body->GetLinearVelocity().y };

	if (enemyAlive)
	{
		if (goingLeft) {

			velocity = { -speed, pbodyEnemy->body->GetLinearVelocity().y };

			if (currentAnimation != &EnemyWalkLeft) {

				currentAnimation = &EnemyWalkLeft;
			}
		}

		if (goingRight) {

			velocity = { speed, pbodyEnemy->body->GetLinearVelocity().y };

			if (currentAnimation != &EnemyWalkRight) {

				currentAnimation = &EnemyWalkRight;
			}
		}
	}

	position.x = METERS_TO_PIXELS(pbodyEnemy->body->GetTransform().p.x) - 32 / 2;
	position.y = METERS_TO_PIXELS(pbodyEnemy->body->GetTransform().p.y) - 32 / 2;

	pbodyEnemy->body->SetLinearVelocity(velocity);

	currentAnimation->Update();

	SDL_Rect EnemyRect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(texture, position.x, position.y, &EnemyRect);

	return true;
}

// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
void Enemy::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{
	case ColliderType::ATTACK:
		LOG("Collision ATTACK");
		enemyAlive = false;
		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		break;
	case ColliderType::WALL:
		LOG("Collision WALL");
		if (goingLeft) {
			goingRight = true;
			goingLeft = false;
		}
		else if (goingRight) {
			goingRight = false;
			goingLeft = true;
		}
		break;
	case ColliderType::DEATH:
		LOG("Collision DEATH");
		enemyAlive = false;
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	case ColliderType::SALIR:
		LOG("Collision UNKNOWN");
		break;
	}
}


bool Enemy::CleanUp()
{

	return true;
}