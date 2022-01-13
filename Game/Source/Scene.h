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

	bool menuDisplay = true;
	bool pauseDisplay = false;
	int menuCount;
	bool credit;
	bool settings;

	bool tick1 = false;
	bool tick2 = false;
	int tickAux = 1;
	int tickAux2 = 1;
	
	float menuCoords[20] = { 510,630,205,45,
						510,685,205,45,
						510,740,205,45,
						510,790,205,45,
						510,845,205,45 };
	
	float enemy1x =1900;
	float enemy1y = 755;
	bool killer_mode = false;

	float enemy2x = 5000;
	float enemy2y = 700;

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

	bool killcount1 = false;
	bool killcount2 = false;
	bool killcount3 = false;
	int vidas = 3;
	bool heart = true;
	bool heart2 = true;
	float currentTicks_hit = 0;
	float aux_pos;

	bool aux_check1 = false;
	bool aux_check2 = false;

	bool enemy_movement = true;
	bool enemy1_state = false;
	bool enemy2_state = false;
	bool helicopter = false;
	bool activate1 = false;
	bool activate2 = false;

	float people_hitboxes[12] = { 800,905,37,54,
								3000,715,37,54,
								5400, 490,37,54};

	float heart_hitboxes[8] = { 200,645,20,18,
								5650,915,20,18};
	float clock_hitboxes[8] = {3100,905,38,45,
								7410,500,38,45};

	bool people_aux = true;
	bool people_aux2 = true;
	bool people_aux3 = true;
	int people_aux_int;
	int clock_aux_int;
	bool stop = false;
	bool shot_state = false;
	float shotx = enemy2x;
	float shoty = enemy2y + 40;

	int h = 4;
	float sliderAux;
	float sliderAux_;
	float sliderAux2;

	int score = 000000;
	int time = 000;
	int scoreaux;
	SDL_Rect nums[10];
	SDL_Texture* font;

	float timer;
	bool timeraux = false;
	bool timeraux_ = false;
	float timeraux2;
	float timeraux3 = 180;
	float timeraux4 = 180;
	int t = 0;

	bool clock_ = true;
	bool clock2_ = true;

	bool end = false;
	bool end2 = false;

	int i = 0;

	float musica;
	float fx;


	void Font();

	void PrintFont(int x, int y, uint score_);
	void PrintFont2(int x, int y, uint score_);

	void Reset();

	bool LoadState(pugi::xml_node&);

	bool SaveState(pugi::xml_node&) const;

	void DebugPath();
	

private:

	void CalculateFPS();
	void stop_and_shot();
	void gameLoop();

	SDL_Texture* fondo;
	SDL_Texture* menu;
	SDL_Texture* menu2;
	SDL_Texture* credits;
	SDL_Texture* setting;
	SDL_Texture* slider;
	SDL_Texture* tick;
	SDL_Texture* pause;
	SDL_Texture* candado;
	SDL_Texture* img;
	SDL_Texture* pantalla1;
	SDL_Texture* pantalla2;
	SDL_Texture* pantalla0;
	SDL_Texture* pantalla3;

	SDL_Texture* HelDer;
	SDL_Texture* HelIzq;
	SDL_Texture* helicopter_death;

	SDL_Texture* SoldDer1;
	SDL_Texture* SoldDer1_;
	SDL_Texture* SoldDer2;
	SDL_Texture* SoldDer3;
	SDL_Texture* SoldIzq1;
	SDL_Texture* SoldIzq1_;
	SDL_Texture* SoldIzq2;
	SDL_Texture* SoldIzq3;
	SDL_Texture* enemy_death;

	SDL_Texture* corazon;
	SDL_Texture* corazon_2;

	SDL_Texture* Personas;
	SDL_Texture* Personas_muertas;
	SDL_Texture* blood;
	SDL_Texture* exclamacion;
	SDL_Texture* controls;
	SDL_Texture* controls2;

	SDL_Texture* checkpoint1;
	SDL_Texture* checkpoint2;

	SDL_Texture* bullet1;
	SDL_Texture* clock;
	SDL_Texture* clock2;
	SDL_Texture* seconds;

	uint eat = 1;
	uint click = 3;
	uint hold = 2;
	uint music = 4;


	float _fps;
	float _maxFPS = 60.0f;
	float _frameTime;


};

#endif // __SCENE_H__