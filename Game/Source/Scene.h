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
	float enemy1x =610;
	float enemy1y = 905;

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

	bool killcount1 = false;
	bool killcount2 = false;
	bool killcount3 = false;
	int vidas = 3;
	bool heart = true;
	bool heart2 = true;
	float currentTicks_hit = 0;
	float aux_pos;

	float people_hitboxes[12] = { 800,905,37,54,
								3000,715,37,54,
								5400, 490,37,54};

	float heart_hitboxes[8] = { 200,645,20,18,
								5650,915,20,18};

	bool people_aux = true;
	bool people_aux2 = true;
	bool people_aux3 = true;
	int people_aux_int;

	bool LoadState(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;

	void DebugPath();
	
	

private:

	void CalculateFPS();
	void gameLoop();

	SDL_Texture* img;
	SDL_Texture* pantalla1;
	SDL_Texture* pantalla2;
	SDL_Texture* pantalla0;
	SDL_Texture* pantalla3;

	SDL_Texture* HelDer;
	SDL_Texture* HelIzq;

	SDL_Texture* SoldDer1;
	SDL_Texture* SoldDer2;
	SDL_Texture* SoldDer3;
	SDL_Texture* SoldIzq1;
	SDL_Texture* SoldIzq2;
	SDL_Texture* SoldIzq3;
	SDL_Texture* corazon;
	SDL_Texture* corazon_2
		;

	SDL_Texture* Personas;
	SDL_Texture* Personas_muertas;
	SDL_Texture* blood;

	float _fps;
	float _maxFPS;
	float _frameTime;


};

#endif // __SCENE_H__