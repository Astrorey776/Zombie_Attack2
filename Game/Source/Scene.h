#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();
	SDL_Rect* playeran = new SDL_Rect();
	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

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
	float enemy1x = 0;
	float enemy1y = 0;

	float enemy2x = 0;
	float enemy2y = 0;

	float enemy3x = 0;
	float enemy3y = 0;

	float enemy4x = 0;
	float enemy4y = 0;

	float enemy5x = 0;
	float enemy5y = 0;

	float playerx = 100.0;
	float playery = 510.0;

	float velx = 10;
	float vely = 200;

	float gravity = -0.5;
	float initial_y1;
	bool jumping;
	int Show_colliders = 0;
	int God_Mode = 0;
	float initial_screen = -1.0;
	Animation dreta;
	Animation esquerra;

	bool LoadState(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;
	
	

private:

	void CalculateFPS();
	void gameLoop();

	SDL_Texture* img;
	SDL_Texture* pantalla1;
	SDL_Texture* pantalla2;
	SDL_Texture* pantalla0;

	float _fps;
	float _maxFPS;
	float _frameTime;


};

#endif // __SCENE_H__