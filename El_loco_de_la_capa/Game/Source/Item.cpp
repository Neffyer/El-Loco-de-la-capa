#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Audio.h"
#include "Input.h"
#include "Render.h"
#include "Scene.h"
#include "Log.h"
#include "Point.h"
#include "Physics.h"
#include "SceneTitle.h"

Item::Item() : Entity(EntityType::ITEM)
{
	name.Create("item");
}

Item::~Item() {}

bool Item::Awake() {

	position.x = parameters.attribute("x").as_int();
	position.y = parameters.attribute("y").as_int();
	texturePath = parameters.attribute("texturepath").as_string();
	if (SString(parameters.attribute("type").as_string()) == SString("Coin"))
		type = ItemType::COIN;
	if (SString(parameters.attribute("type").as_string()) == SString("Life"))
		type = ItemType::LIFE;

	return true;
}

bool Item::Start() {

	//initilize textures
	texture = app->tex->Load(texturePath);

	// L07 TODO 4: Add a physics to an item - initialize the physics body

	int width = 32;
	int height = 32;

	if (type == ItemType::COIN) {
		pbody = app->physics->CreateCircleSensor(position.x + width / 2, position.y + height / 2, 12, bodyType::KINEMATIC, ColliderType::COIN);
	}

	if (type == ItemType::LIFE) {
		pbody = app->physics->CreateCircleSensor(position.x + width / 2, position.y + height / 2, 14, bodyType::KINEMATIC, ColliderType::LIFE);
	}

	pbody->listener = this;

	return true;
}

bool Item::Update()
{
	// L07 TODO 4: Add a physics to an item - update the position of the object from the physics.  

	b2Transform transform = pbody->body->GetTransform();
	b2Vec2 pos = transform.p;

	if (type == ItemType::COIN) {

		position.x = METERS_TO_PIXELS(pos.x) - 16;
		position.y = METERS_TO_PIXELS(pos.y) - 18;

		app->render->DrawTexture(texture, position.x, position.y);

	}

	if (type == ItemType::LIFE) {

		position.x = METERS_TO_PIXELS(pos.x) - 15;
		position.y = METERS_TO_PIXELS(pos.y) - 15;

		app->render->DrawTexture(texture, position.x, position.y);

	}

	return true;
}

bool Item::CleanUp()
{
	return true;
}

void Item::OnCollision(PhysBody* physA, PhysBody* physB) {

	switch (physB->ctype)
	{
	case ColliderType::COIN:
		LOG("Collision ITEM");

		break;
	case ColliderType::LIFE:
		LOG("Collision ITEM");

		break;
	case ColliderType::PLATFORM:
		LOG("Collision PLATFORM");

		break;
	case ColliderType::UNKNOWN:
		LOG("Collision UNKNOWN");

		break;

	case ColliderType::PLAYER:
		LOG("Collision PLAYER");

		if (type == ItemType::COIN || type == ItemType::LIFE) {

			Disable();
			pbody->body->DestroyFixture(pbody->body->GetFixtureList());

		}

		break;

	}

}