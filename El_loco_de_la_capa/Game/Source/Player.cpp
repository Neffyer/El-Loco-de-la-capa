#include "Module.h"
#include "Player.h"
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

Player::Player() : Entity(EntityType::PLAYER)
{
	name.Create("Player");
	for (int i = 0; i < 8; i++) {

		PlayerIdleRight.PushBack({ 32 * (0 + i), 0, 32, 32 });
	}
	PlayerIdleRight.loop = true;
	PlayerIdleRight.speed = 0.05f;

	for (int i = 0; i < 8; i++) {

		PlayerIdleLeft.PushBack({ 32 * (0 + i), 32, 32, 32 });
	}
	PlayerIdleLeft.loop = true;
	PlayerIdleLeft.speed = 0.05f;

	for (int i = 0; i < 8; i++) {

		RunningRight.PushBack({ 32 * (0 + i), 32 * 2, 32, 32 });
	}
	RunningRight.loop = true;
	RunningRight.speed = 0.2f;
	
	for (int i = 0; i < 8; i++) {

		RunningLeft.PushBack({ 32 * (0 + i), 32 * 3, 32, 32 });
	}
	RunningLeft.loop = true;
	RunningLeft.speed = 0.2f;

	for (int i = 0; i < 5; i++) {

		StartJumpRight.PushBack({ 32 * (0 + i), 32 * 4, 32, 32 });
	}
	StartJumpRight.loop = true;
	StartJumpRight.speed = 0.2f;

	for (int i = 0; i < 5; i++) {

		StartJumpLeft.PushBack({ 32 * (0 + i), 32 * 5, 32, 32 });
	}
	StartJumpLeft.loop = true;
	StartJumpLeft.speed = 0.2f;

	FlyRight.PushBack({ 32 * 5, 32 * 4, 32, 32 });
	FlyRight.loop = true;
	FlyRight.speed = 1.0f;

	FlyLeft.PushBack({ 32 * 5, 32 * 5, 32, 32 });
	FlyLeft.loop = true;
	FlyLeft.speed = 1.0f;

	for (int i = 5; i < 8; i++) {

		LandRight.PushBack({ 32 * (0 + i), 32 * 4, 32, 32 });
	}
	LandRight.loop = false;
	LandRight.speed = 1.0f;

	for (int i = 5; i < 8; i++) {

		LandLeft.PushBack({ 32 * (0 + i), 32 * 5, 32, 32 });
	}
	LandLeft.loop = false;
	LandLeft.speed = 1.0f;

	for (int i = 0; i < 8; i++) {

		DieRight.PushBack({ 32 * (0 + i), 32 * 6, 32, 32 });
	}
	DieRight.loop = false;
	DieRight.speed = 0.2f;
	DieRight.pingpong = true;

	for (int i = 0; i < 8; i++) {

		DieLeft.PushBack({ 32 * (0 + i), 32 * 7, 32, 32 });
	}
	DieLeft.loop = false;
	DieLeft.speed = 0.2f;
	DieLeft.pingpong = true;
}

Player::~Player() {

}

bool Player::Awake() {

	//L02: DONE 1: Initialize Player parameters
	//pos = position;
	//texturePath = "Assets/Textures/player/idle1.png";

	//L02: DONE 5: Get Player parameters from XML
	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();

	return true;
}

bool Player::Start() {
	
	

	//initilize textures
	texture = app->tex->Load(texturePath);

	// L07 TODO 5: Add physics to the player - initialize physics body
	pbody = app->physics->CreateCircle(position.x, position.y, 14, bodyType::DYNAMIC);

	startx = position.x;
	starty = position.y;

	jump = 0;
	
	jumpFx = app->audio->LoadFx("Assets/Audio/Fx/JumpFx.wav");

	
	return true;
}


bool Player::Update()
{


	// L07 TODO 5: Add physics to the player - updated player position using physics

	if (idle) {
		if (flying)
		{
			currentAnimation = &FlyRight;
		}
		else
		{
			currentAnimation = &PlayerIdleRight;
		}
	}
	else {
		if (flying)
		{
			currentAnimation = &FlyLeft;
		}
		else
		{
			currentAnimation = &PlayerIdleLeft;
		}

	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		gameStart = true;
	}
	
	if (!godMode) {
		if (gameStart)
		{
			if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {

				app->render->camera.x = 0;
				app->render->camera.y = 0;
				app->scene->player->pbody->body->SetTransform({ PIXEL_TO_METERS(startx),PIXEL_TO_METERS(starty) }, 0);
			}

			b2Vec2 velocity = { 0, pbody->body->GetLinearVelocity().y };
			//L02: DONE 4: modify the position of the player using arrow keys and render the texture

			if (app->input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT) {
				if (idle) {

					currentAnimation = &DieRight;
				}
				else
				{
					currentAnimation = &DieLeft;
				}
			}

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

				idle = false;

				velocity = { -speed, pbody->body->GetLinearVelocity().y };

				if (currentAnimation != &RunningLeft) {

					currentAnimation = &RunningLeft;
				}
			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

				idle = true;

				velocity = { speed, pbody->body->GetLinearVelocity().y };

				if (currentAnimation != &RunningRight) {

					currentAnimation = &RunningRight;
				}
			}

			/*if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {

				if (jump < 2) {
					velocity = { pbody->body->GetLinearVelocity().x, -impulse };
					jump++;

					if (idle)
					{
						currentAnimation = &StartJumpRight;
					}
					else
					{
						currentAnimation = &StartJumpLeft;
					}

				}

			}*/


			if (app->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {

				app->audio->PlayFx(jumpFx);

				velocity = { pbody->body->GetLinearVelocity().x, -impulse };


				if (idle)
				{
					currentAnimation = &StartJumpRight;
				}
				else
				{
					currentAnimation = &StartJumpLeft;
				}


			}
			position.x = METERS_TO_PIXELS(pbody->body->GetTransform().p.x) - 32 / 2;
			position.y = METERS_TO_PIXELS(pbody->body->GetTransform().p.y) - 32 / 2;

			pbody->body->SetLinearVelocity(velocity);

			currentAnimation->Update();
			SDL_Rect rect = currentAnimation->GetCurrentFrame();
			app->render->DrawTexture(texture, position.x, position.y, &rect);
		}
	}

	else {

		if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {

			app->render->camera.x = 0;
			app->render->camera.y = 0;
			app->scene->player->pbody->body->SetTransform({ PIXEL_TO_METERS(startx),PIXEL_TO_METERS(starty) }, 0);
		}

		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {

			position.y -= speed;
			currentAnimation = &PlayerIdleRight;

		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {

			position.y += speed;
			currentAnimation = &PlayerIdleRight;

		}
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {

			position.x -= speed;
			idle = false;

			if (currentAnimation != &RunningLeft) {

				currentAnimation = &RunningLeft;
			}

		}
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {

			position.x += speed;
			idle = true;

			if (currentAnimation != &RunningRight) {

				currentAnimation = &RunningRight;
			}

		}

	}

	currentAnimation->Update();

	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(texture, position.x, position.y, &playerRect);

	return true;
}


// L07 DONE 6: Define OnCollision function for the player. Check the virtual function on Entity class
void Player::OnCollision(PhysBody* physA, PhysBody* physB) {

	// L07 DONE 7: Detect the type of collision

	switch (physB->ctype)
	{
	case ColliderType::ITEM:
		LOG("Collision ITEM");
		app->audio->PlayFx(pickCoinFxId);
		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");
		jump = 0;
		flying = false;
		break;
	case ColliderType::WALL:
		LOG("Collision WALL");
		break;
	case ColliderType::DEATH:
		LOG("Collision DEATH");
		if (idle) {

			currentAnimation = &DieRight;
		}
		else
		{
			currentAnimation = &DieLeft;
		}
		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");
		break;
	}
}


bool Player::CleanUp()
{

	return true;
}