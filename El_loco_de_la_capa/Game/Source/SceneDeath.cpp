#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneDeath.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "FadeToBlack .h"

#include "Defs.h"
#include "Log.h"

SceneDeath::SceneDeath(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneEnding");
}

// Destructor
SceneDeath::~SceneDeath()
{}

// Called before render is available
bool SceneDeath::Awake(pugi::xml_node& config)
{
	LOG("Loading SceneLogo");
	bool ret = true;


	return ret;
}

// Called before the first frame
bool SceneDeath::Start()
{

	deathScreen = app->tex->Load("Assets/Textures/deathScreen.png");

	enableMusic = true;

	return true;
}

// Called each loop iteration
bool SceneDeath::PreUpdate()
{
	app->entityManager->Disable();

	//app->physics->debug = false;

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/NoMusic.ogg", 0);
		enableMusic = false;

	}

	return true;
}

// Called each loop iteration
bool SceneDeath::Update(float dt)
{

	app->render->DrawTexture(deathScreen, 0, 0);

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {


		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->scene, dt);
		app->render->camera.x = 0;
		app->render->camera.y = 0;
		app->scene->player->playerAlive = true;
		app->scene->player->idle = true;
		app->scene->player->hits = 0;
		app->scene->player->pbody->body->SetTransform({ PIXEL_TO_METERS(app->scene->player->startx),PIXEL_TO_METERS(app->scene->player->starty) }, 0);

	}

	return true;
}

// Called each loop iteration
bool SceneDeath::PostUpdate()
{
	bool ret = true;

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneDeath::CleanUp()
{
	LOG("Freeing scene");

	return true;
}