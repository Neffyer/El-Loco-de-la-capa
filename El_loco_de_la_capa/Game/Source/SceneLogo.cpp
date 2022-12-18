#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneLogo.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "FadeToBlack .h"

#include "Defs.h"
#include "Log.h"

SceneLogo::SceneLogo(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneLogo");
}

// Destructor
SceneLogo::~SceneLogo()
{}

// Called before render is available
bool SceneLogo::Awake(pugi::xml_node& config)
{
	LOG("Loading SceneLogo");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool SceneLogo::Start()
{
	teamLogo = app->tex->Load("Assets/Textures/teamLogo.png");

	enableMusic = true;

	return true;
}

// Called each loop iteration
bool SceneLogo::PreUpdate()
{
	app->entityManager->Disable();

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/NoMusic.ogg", 0);
		enableMusic = false;

	}

	return true;
}

// Called each loop iteration
bool SceneLogo::Update(float dt)
{
	
	app->render->DrawTexture(teamLogo, 0, 0);

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {


		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->sceneTitle, dt);
		app->render->camera.x = 0;
		app->render->camera.y = 0;
		app->scene->player->pbody->body->SetTransform({ PIXEL_TO_METERS(app->scene->player->startx),PIXEL_TO_METERS(app->scene->player->starty) }, 0);

	}

	return true;
}

// Called each loop iteration
bool SceneLogo::PostUpdate()
{
	bool ret = true;

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneLogo::CleanUp()
{
	LOG("Freeing scene");

	return true;
}