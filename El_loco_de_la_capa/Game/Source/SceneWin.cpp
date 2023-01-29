#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneWin.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "FadeToBlack .h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"

SceneWin::SceneWin(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneWin");
}

// Destructor
SceneWin::~SceneWin()
{}

// Called before render is available
bool SceneWin::Awake(pugi::xml_node& config)
{
	LOG("Loading SceneWin");
	bool ret = true;


	return ret;
}

// Called before the first frame
bool SceneWin::Start()
{

	winScreen = app->tex->Load("Assets/Textures/winScreen.png");

	enableMusic = true;

	return true;
}

// Called each loop iteration
bool SceneWin::PreUpdate()
{
	app->entityManager->Disable();
	/*app->entityManager->Disable();

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/Intro.ogg", 0);
		enableMusic = false;

	}*/

	return true;
}

// Called each loop iteration
bool SceneWin::Update(float dt)
{
	app->render->DrawTexture(winScreen, 0, 0);

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {


		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->sceneTitle, dt);
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
bool SceneWin::PostUpdate()
{
	bool ret = true;

	app->render->camera.x = 0;
	app->render->camera.y = 0;


	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneWin::CleanUp()
{
	LOG("Freeing scene");

	return true;
}