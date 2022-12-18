#pragma once

#include "Module.h"
#include "Player.h"
#include "Item.h"

struct SDL_Texture;

class SceneWin : public Module
{
public:

	SceneWin(bool startEnabled);

	// Destructor
	virtual ~SceneWin();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

public:

	bool enableMusic;

private:

	SDL_Texture* winScreen;

};