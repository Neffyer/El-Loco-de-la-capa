#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Module.h"
#include "Entity.h"
#include "List.h"
#include "App.h"
#include "Scene.h"
#include "Physics.h"

class EntityManager : public Module
{
public:

    EntityManager(bool startEnabled);

    // Destructor
    virtual ~EntityManager();

    // Called before render is available
    bool Awake(pugi::xml_node&);

    // Called after Awake
    bool Start();

    // Called every frame
    bool Update(float dt);

    // Called before quitting
    bool CleanUp();

    // Additional methods
    Entity* CreateEntity(EntityType type);

    void DestroyEntity(Entity* entity);

    void AddEntity(Entity* entity);

    bool EntityManager::SaveState(pugi::xml_node& data)
    {
        pugi::xml_node player = data.append_child("player");

        player.append_attribute("x") = app->scene->player->position.x;
        player.append_attribute("y") = app->scene->player->position.y;

        pugi::xml_node enemy = data.append_child("enemy");

        enemy.append_attribute("x") = app->scene->enemy->position.x;
        enemy.append_attribute("y") = app->scene->enemy->position.y;

        return true;
    }

    bool EntityManager::LoadState(pugi::xml_node& data) {

        float x = data.child("player").attribute("x").as_int();

        float y = data.child("player").attribute("y").as_int();

        app->scene->player->pbody->body->SetTransform({ PIXEL_TO_METERS(x), PIXEL_TO_METERS(y) }, 0);

        x = data.child("enemy").attribute("x").as_int();

        y = data.child("enemy").attribute("y").as_int();

        app->scene->enemy->pbodyEnemy->body->SetTransform({ PIXEL_TO_METERS(x), PIXEL_TO_METERS(y) }, 0);

        return true;
    }


public:

    List<Entity*> entities;

};

#endif // ENTITYMANAGER_H_