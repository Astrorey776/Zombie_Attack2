#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"

#include "Defs.h"
#include "Log.h"
#include <iostream>

Scene::Scene() : Module(), _maxFPS(100.0f)
{

	name.Create("scene");
}
// Destructor
Scene::~Scene()
{}
// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

/*void Scene::DebugPath() {
	const DynArray<iPoint>* path = app->pathfinding->GetLastPath();
	for (uint i = 0; i < path->Count(); ++i) {
		iPoint pos = app->map->MapToWorld(path->At(i)->x, path->At(i) - y);
		app->render->DrawTexture(pathTex, pos.x, pos.y);
	}
}
*/


// Called before the first frame
bool Scene::Start()
{


	// L03: DONE: Load map
	//app->map->Load("hello.tmx");

	if (app->map->Load("Ciudad_3.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		RELEASE_ARRAY(data);
	}

	img = app->tex->Load("Assets/textures/zombie_sprites.png");

	HelDer = app->tex->Load("Assets/textures/HelicopDer.png");
	HelIzq = app->tex->Load("Assets/textures/HelicopIzq.png");

	SoldDer1= app->tex->Load("Assets/textures/SoldPos1Der.png");
	SoldDer2 = app->tex->Load("Assets/textures/SoldPos2Der.png");
	SoldDer3 = app->tex->Load("Assets/textures/SoldPos3Der.png");

	SoldIzq1 = app->tex->Load("Assets/textures/SoldPos1Izq.png");
	SoldIzq2 = app->tex->Load("Assets/textures/SoldPos2Izq.png");
	SoldIzq3 = app->tex->Load("Assets/textures/SoldPos3Izq.png");

	corazon = app->tex->Load("Assets/textures/corazon.png");
	corazon_2 = app->tex->Load("Assets/textures/corazon_2.png");

	app->map->Load("Ciudad_3.tmx");
	pantalla0 = app->tex->Load("Assets/textures/Logo.png");
	pantalla1 = app->tex->Load("Assets/textures/Pantalla_inicio.png");
	pantalla2 = app->tex->Load("Assets/textures/Pantalla_win.png");
	pantalla3 = app->tex->Load("Assets/textures/Pantalla_muerte.png");

	Personas = app->tex->Load("Assets/textures/Personas.png");
	Personas_muertas = app->tex->Load("Assets/textures/Personas_muertas.png");

	checkpoint1 = app -> tex->Load("Assets/textures/checkpoint1.png");
	checkpoint2 = app -> tex->Load("Assets/textures/checkpoint2.png");


	blood = app->tex->Load("Assets/Textures/sangre.png");
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{	
	app->map->Draw();

	if (heart == true) {
		app->render->DrawTexture(corazon_2, 200, 645);
	}

	if (heart2 == true) {
		app->render->DrawTexture(corazon_2, 5650, 915);
	}
	if (aux_check1 == false) {
		app->render->DrawTexture(checkpoint1, 3300, 905);
	}	
	if (playerx > 3300 || aux_check1 == true) {
		aux_check1 = true;
		app->render->DrawTexture(checkpoint2, 3300, 905);
	}

	if (playerx == 3300) {
		//app->SaveGameRequest();
	}

	if (playerx == 6100) {
		//app->SaveGameRequest();
	}

	if (aux_check2 == false) {
		app->render->DrawTexture(checkpoint1, 6100, 905);
	}	
	if (playerx > 6100 ||aux_check2 == true) {
		aux_check2 = true;
		app->render->DrawTexture(checkpoint2, 6100, 905);
	}

	aux_pos = playerx;

	if (currentTicks_hit >= 10000) {
		app->render->DrawCircle(100, 300, 25, 250, 100, 100);
		//vely = 200;
		currentTicks_hit = 0;
	}

	
	if (currentTicks_hit >= 1) {
		currentTicks_hit = SDL_GetTicks();
	}

	//app->render->DrawTexture(SoldDer1, enemy1x, enemy1y);
	if (playerx < 8400) {
		for (int i = 0; i < vidas; i++) {
			app->render->DrawTexture(corazon, playerx - 75 + 40 * i, 420);
		}
	}

    // L02: DONE 3: Request Load / Save when pressing L/S
	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN) {
		app->LoadGameRequest();
	}
	/*if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		playerx = 100.0;
		playery = 900.0;
		app->render->camera.x 
		app->render->camera.y = 900.0;
	}*/

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {
		app->SaveGameRequest();
	}

	if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN) {
		playery = 510;
		playerx = 100;
		playeran->y = 510;
		playeran->x = 100;
		app->render->camera.x = 0;
		app->render->camera.y = -400;
	}

	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) {
		if (Show_colliders == 1) {
			Show_colliders = 0;
		}
		else if (Show_colliders == 0) {
			Show_colliders = 1;
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		if (God_Mode == 1) {
			
			gravity = -0.5;
			God_Mode = 0;
		}
		else if (God_Mode == 0) {
			God_Mode = 1;
			vely = 0;
			gravity = 0;
		}
	}
	if(God_Mode == 1){
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
			playery -= velx / 2;
		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
			playery += velx / 2;
		}
	}
	
	if (app->map->aux_col != app->scene->playerx) {
		app->map->colisionsx = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && initial_screen >= 1 && playerx < 8400 && app->map->colisionsx == false) {
		app->render->camera.x -= velx;	
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && initial_screen >= 1 && playerx < 8400 && app->map->colisionsx == false) {
		app->render->camera.x += velx;
	}

	
	SDL_Rect *left1 = new SDL_Rect();
	left1->x = 0;
	left1->y = 0;
	left1->w = 42;
	left1->h = 56;
	SDL_Rect* left2 = new SDL_Rect();
	left2->x = 43;
	left2->y = 0;
	left2->w = 42;
	left2->h = 56;
	SDL_Rect* left3 = new SDL_Rect();
	left3->x = 88;
	left3->y = 0;
	left3->w = 50;
	left3->h = 56;
	SDL_Rect* right1 = new SDL_Rect();
	right1->x = 139;
	right1->y = 0;
	right1->w = 50;
	right1->h = 56;
	SDL_Rect* right2 = new SDL_Rect();
	right2->x = 189;
	right2->y = 0;
	right2->w = 46;
	right2->h = 56;
	SDL_Rect* right3 = new SDL_Rect();
	right3->x = 235;
	right3->y = 1;
	right3->w = 46;
	right3->h = 56;

	SDL_Rect* people = new SDL_Rect();
	people->x = 0;
	people->y = 0;
	people->w = 37;
	people->h = 54;
	SDL_Rect* people2 = new SDL_Rect();
	people2->x = 0;
	people2->y = 56;
	people2->w = 37;
	people2->h = 54;
	SDL_Rect* people3 = new SDL_Rect();
	people3->x = 37;
	people3->y = 0;
	people3->w = 37;
	people3->h = 54;

	SDL_Rect* sangre = new SDL_Rect();
	sangre->x = 0;
	sangre->y = 0;
	sangre->w = 53;
	sangre->h = 42;

	if (people_aux == true && people_aux_int ==0) {
		app->render->DrawTexture(Personas, 800, 905, people);
	}

	if (people_aux2 == true) {
		app->render->DrawTexture(Personas, 3000, 715, people2);
	}
	
	if (people_aux3 == true) {
		app->render->DrawTexture(Personas, 5400, 490, people3);
	}


	if (app->render->camera.x > 0) {
		app->render->camera.x = -2;

	 }
	if (playerx < 99) {
		playerx = 100;

	}

	//800,905,37,54
	people_aux_int;
	for (int i = people_aux_int; i < 12; i += 4) {
		if (playerx > people_hitboxes[i]- people_hitboxes[i + 2] && playerx < people_hitboxes[i] + people_hitboxes[i + 2] && playery > people_hitboxes[i+1] && playery < people_hitboxes[i + 1] + people_hitboxes[i + 3] && app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
			if (i == 0) {
				people_aux = false;
				killcount1 = true;
			}
			if (i == 4) {
				people_aux2 = false;
				killcount2 = true;
			}
			if (i == 8) {
				people_aux3 = false;
				killcount3 = true;
			}

			people_aux_int = i+4;
			app->render->DrawTexture(blood, people_hitboxes[i], people_hitboxes[i + 1] + 10, sangre);
			app->render->DrawCircle(100, 200, 50, 250, 250, 0);

		}
	}
	
	//200, 645, 20, 18
	for (int i = 0; i < 8; i += 4) {
		if (((playerx > heart_hitboxes[i]-20 && playerx < heart_hitboxes[i] + heart_hitboxes[i + 2]+20))
			&& playery > heart_hitboxes[i+1]-30 && playery < heart_hitboxes[i+1] + heart_hitboxes[i+3]+30 ) {
			app->render->DrawCircle(200, 100, 50, 250, 100, 0);
			
			if (i == 0 && heart == true) {
				heart = false;
				vidas += 1;
			}
			if (i == 4 && heart2 == true) {
				heart2 = false;
				vidas += 1;
			}
		}
	}
	if (playerx < 8400) {
		if (killcount3 == true) {
			app->render->DrawTexture(Personas_muertas, playerx + 1115, 410, people3);
		}

		if (killcount1 == true) {
			app->render->DrawTexture(Personas_muertas, playerx + 1090, 410, people);
		}

		if (killcount2 == true) {
			app->render->DrawTexture(Personas_muertas, playerx + 1105, 430, people2);
		}
	}
	

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && initial_screen >= 1) {
		playerx += velx;
		/*dreta.PushBack({139,0,50,56});
		dreta.PushBack({189,0,46,56});
		dreta.PushBack({235,2,46,56});
		dreta.loop = true;
		dreta.speed = 2;*/

		playeran->x = right1->x;
		playeran->y = right1->y;
		playeran->w = right1->w;
		playeran->h = right1->h;


		app->render->DrawTexture(img, playerx-15, playery, playeran);
	}
		
	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && initial_screen >=1) {
		playerx -= velx;
		playeran->x = left3->x;
		playeran->y = left3->y;
		playeran->w = left3->w;
		playeran->h = left3->h;
		app->render->DrawTexture(img, playerx+2, playery, playeran);
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == NULL && app->input->GetKey(SDL_SCANCODE_D) == NULL){
		playeran->x = right3->x;
		playeran->y = right3->y;
		playeran->w = right3->w;
		playeran->h = right3->h;
		app->render->DrawTexture(img, playerx, playery, playeran);
		
	}

	if (app->map->colisionsy == true) {//gravetat sempre fins el terra	
		
		vely = 0;
		jumping = false;
	}


	if (app->map->colisionsy == false) {
		vely -= gravity;
	}


	app->map->colisionsy = false;
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && jumping==false && God_Mode == 0) {
		app->map->colisionsy = false;
		vely = -10;
		jumping = true;
	}

	playery += vely;

	// Draw map


	// Placeholder not needed any more
   // L03: DONE 7: Set the window title with map/tileset info
	SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		app->map->mapData.width, app->map->mapData.height,
		app->map->mapData.tileWidth, app->map->mapData.tileHeight,
		app->map->mapData.tilesets.count());

	app->win->SetTitle(title.GetString());

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) {
		initial_screen += 1;
	}

	if (initial_screen == -1) {
		app->render->DrawTexture(pantalla0, 0, 400, NULL);
	}

	if (initial_screen == 0) {
		app->render->DrawTexture(pantalla1, 0, 400, NULL);
	}

	if (playerx >= 9500) {
		initial_screen = 0;
		app->render->DrawTexture(pantalla2, playerx - 1200, 400, NULL);
		// cambiar la imatge a la d victoria
	}

	if (vidas == 0) {
		app->map->death = true;
	}

	if (app->map->death == true) {
		app->render->DrawTexture(app->scene->pantalla3, app->scene->playerx -100, 400, NULL);
		velx = 0;
		vely = 0;
	}
	gameLoop();
	return true;
}
// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	
	if(app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool Scene::LoadState(pugi::xml_node& configRenderer)
{

	playerx = configRenderer.child("player").attribute("x").as_int();
	playery = configRenderer.child("player").attribute("y").as_int();

	enemy1x = configRenderer.child("enemy1").attribute("x").as_int();
	enemy1y = configRenderer.child("enemy1").attribute("y").as_int();

	enemy2x = configRenderer.child("enemy2").attribute("x").as_int();
	enemy2y = configRenderer.child("enemy2").attribute("y").as_int();

	enemy3x = configRenderer.child("enemy3").attribute("x").as_int();
	enemy3y = configRenderer.child("enemy3").attribute("y").as_int();

	enemy4x = configRenderer.child("enemy4").attribute("x").as_int();
	enemy4y = configRenderer.child("enemy4").attribute("y").as_int();

	enemy5x = configRenderer.child("enemy5").attribute("x").as_int();
	enemy5y = configRenderer.child("enemy5").attribute("y").as_int();


	app->render->camera.x = configRenderer.child("camera").attribute("x").as_int();
	app->render->camera.y = configRenderer.child("camera").attribute("y").as_int();

	return true;
}
bool Scene::SaveState(pugi::xml_node& configRenderer) const
{
	pugi::xml_node player = configRenderer.child("player");
	pugi::xml_node camera = configRenderer.child("camera");
	pugi::xml_node enemy1 = configRenderer.child("enemy1");
	pugi::xml_node enemy2 = configRenderer.child("enemy2");
	pugi::xml_node enemy3 = configRenderer.child("enemy3");
	pugi::xml_node enemy4 = configRenderer.child("enemy4");
	pugi::xml_node enemy5 = configRenderer.child("enemy5");
	
	player.attribute("x").set_value(playerx);
	player.attribute("y").set_value(playery);

	camera.attribute("x").set_value(app->render->camera.x);
	camera.attribute("y").set_value(app->render->camera.y);




	return true;
}

void Scene::gameLoop() {

	float startTicks = SDL_GetTicks();

	CalculateFPS();
	std::cout << _fps << std::endl;

	static int frameCounter = 0;
	if (frameCounter == 10) {
		std::cout << _fps << std::endl;
		frameCounter = 0;
	}


	float frameTicks = SDL_GetTicks() - startTicks;

	if (1000.0f / _maxFPS > frameTicks) {
		SDL_Delay(1000.0f / _maxFPS - frameTicks);
	}

}

void Scene::CalculateFPS() {
	static const int NUM_SAMPLES = 10;
	static float frameTimes[NUM_SAMPLES];
	static int currentFrame = 0;

	static float prevTicks = SDL_GetTicks();

	float currentTicks;
	currentTicks = SDL_GetTicks();

	_frameTime = currentTicks - prevTicks;
	frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

	prevTicks = currentTicks;

	int count;
	currentFrame++;
	if (currentFrame < NUM_SAMPLES) {
		count = currentFrame;
	}
	else {
		count = NUM_SAMPLES;
	}

	float frameTimeAverage = 0;
	for (int i = 0; i < count; i++) {
		frameTimeAverage += frameTimes[i];
	}
	frameTimeAverage /= count;

	if (frameTimeAverage > 0) {
		_fps = 1000.0f / frameTimeAverage;
	}
	else {
		_fps = 60.0f;
	}

}
