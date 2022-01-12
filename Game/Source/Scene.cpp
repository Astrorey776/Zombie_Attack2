#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "windows.h"

#include "Defs.h"
#include "Log.h"
#include <iostream>

Scene::Scene() : Module(), _maxFPS(60.0f)
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

// Called before the first frame
bool Scene::Start()
{


	// L03: DONE: Load map
	//app->map->Load("hello.tmx");
	score = 500;
	if (app->map->Load("Ciudad_3.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;

		RELEASE_ARRAY(data);
	}

	fondo = app->tex->Load("Assets/textures/fondo1.png");
	menu = app->tex->Load("Assets/textures/MENU1.png");
	menu2 = app->tex->Load("Assets/textures/MENU.png");
	credits = app->tex->Load("Assets/textures/Credits.png");
	setting = app->tex->Load("Assets/textures/Settings.png");
	slider = app->tex->Load("Assets/textures/slider.png");
	tick = app->tex->Load("Assets/textures/tick.png");
	pause = app->tex->Load("Assets/textures/PAUSE.png");

	img = app->tex->Load("Assets/textures/zombie_sprites.png");

	HelDer = app->tex->Load("Assets/textures/HelicopDer.png");
	HelIzq = app->tex->Load("Assets/textures/HelicopIzq.png");
	helicopter_death = app->tex->Load("Assets/textures/Helicopter_death.png");

	SoldDer1= app->tex->Load("Assets/textures/SoldPos1Der.png");
	SoldDer1_= app->tex->Load("Assets/textures/SoldPos1Der_.png");
	SoldDer2 = app->tex->Load("Assets/textures/SoldPos2Der.png");
	SoldDer3 = app->tex->Load("Assets/textures/SoldPos3Der.png");

	SoldIzq1 = app->tex->Load("Assets/textures/SoldPos1Izq.png");
	SoldIzq1_ = app->tex->Load("Assets/textures/SoldPos1Izq_.png");
	SoldIzq2 = app->tex->Load("Assets/textures/SoldPos2Izq.png");
	SoldIzq3 = app->tex->Load("Assets/textures/SoldPos3Izq.png");
	enemy_death = app->tex->Load("Assets/textures/enemy_death.png");

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

	bullet1 = app->tex->Load("Assets/textures/bullet1.png");

	blood = app->tex->Load("Assets/Textures/sangre.png");
	exclamacion = app->tex->Load("Assets/textures/exclamacion.png");

	controls = app->tex->Load("Assets/textures/Controls.png");
	controls2 = app->tex->Load("Assets/textures/controls2.png");

	eat = app->audio->LoadFx("Assets/audio/fx/eat.wav");
	click = app->audio->LoadFx("Assets/audio/fx/click.wav");
	hold = app->audio->LoadFx("Assets/audio/fx/hold.wav");

	font = app->tex->Load("Assets/textures/nums_score.png");
	clock = app->tex->Load("Assets/textures/clock.png");

	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");
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
	app->render->DrawTexture(fondo,0,405);

	app->map->Draw();
	app->render->DrawTexture(controls, 300, 645);
	app->render->DrawTexture(controls2, 750, 785);
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
		app->SaveGameRequest();
	}

	if (playerx == 6100) {
		app->SaveGameRequest();
	}

	if (aux_check2 == false) {
		app->render->DrawTexture(checkpoint1, 6100, 905);
	}
	if (playerx > 6100 ||aux_check2 == true) {
		aux_check2 = true;
		app->render->DrawTexture(checkpoint2, 6100, 905);
	}

	aux_pos = playerx;

	if (currentTicks_hit >= 5000) {
		//app->render->DrawCircle(100, 300, 25, 250, 100, 100);
		//vely = 200;
		currentTicks_hit = 0;
		velx = 10;
	}


	if (currentTicks_hit >= 1) {
		currentTicks_hit = SDL_GetTicks();
	}


	if (playerx < 8400) {
		for (int i = 0; i < vidas; i++) {
			app->render->DrawTexture(corazon, playerx - 75 + 40 * i, 420);
		}
	}

    // L02: DONE 3: Request Load / Save when pressing F5/F6
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
		menuCount = 1;
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
		if (app->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && menuDisplay == false) {
			playery -= velx / 2;
		}
		if (app->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && menuDisplay == false) {
			playery += velx / 2;
		}
	}

	if (app->map->aux_col != app->scene->playerx) {
		app->map->colisionsx = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && initial_screen >= 1 && playerx < 8400 && app->map->colisionsx == false && menuDisplay == false) {
		app->render->camera.x -= velx;
	}

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && initial_screen >= 1 && playerx < 8400 && app->map->colisionsx == false && menuDisplay == false) {
		app->render->camera.x += velx;
	}

	if (playerx + 700 >= enemy1x && activate1 == false && menuDisplay == false) {
		enemy1_state = true;
		activate1 = true;
	}

	if (playerx + 700 >= enemy2x && activate2 == false && menuDisplay == false) {
		enemy2_state = true;
		activate2 = true;
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

	//SDL_Rect enemyRect = {enemy1x, enemy1y, 44, 44 };
	//SDL_Rect enemyRect_kill = {enemy1x, enemy1y-10, 44, 10 };


	if (people_aux == true && people_aux_int == 0) {
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
	for (int i = people_aux_int; i < 12; i += 4) {//colisions amb les persones que pots matar
		if (playerx > people_hitboxes[i]- people_hitboxes[i + 2] && playerx < people_hitboxes[i] + people_hitboxes[i + 2] && playery > people_hitboxes[i+1] && playery < people_hitboxes[i + 1] + people_hitboxes[i + 3] && app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {
			if (i == 0) {
				people_aux = false;
				killcount1 = true;
				score += 200;
				app->audio->PlayFx(eat);
			}
			if (i == 4) {
				people_aux2 = false;
				killcount2 = true;
				score += 200;
				app->audio->PlayFx(eat);
			}
			if (i == 8) {
				people_aux3 = false;
				killcount3 = true;
				score += 200;
				app->audio->PlayFx(eat);
			}

			people_aux_int = i+4;
			app->render->DrawTexture(blood, people_hitboxes[i], people_hitboxes[i + 1] + 10, sangre);
			//app->render->DrawCircle(100, 200, 50, 250, 250, 0);

		}
	}

	//200, 645, 20, 18
	for (int i = 0; i < 8; i += 4) {//Colisions amb les vides
		if (((playerx > heart_hitboxes[i]-20 && playerx < heart_hitboxes[i] + heart_hitboxes[i + 2]+20))
			&& playery > heart_hitboxes[i+1]-30 && playery < heart_hitboxes[i+1] + heart_hitboxes[i+3]+30 ) {
			//app->render->DrawCircle(200, 100, 50, 250, 100, 0);

			if (i == 0 && heart == true) {
				heart = false;
				score += 50;
				vidas += 1;
			}
			if (i == 4 && heart2 == true) {
				heart2 = false;
				score += 50;
				vidas += 1;
			}
		}
	}
	//colisions enemic terrestre
	if (playerx + 50 > enemy1x && playerx<enemy1x + 44 && playery > enemy1y && playery < enemy1y + 64 && enemy1_state == true) {
		//app->render->DrawCircle(300, 300, 50,100, 100, 100);

		if (playerx < enemy1x && God_Mode == 0) {
			playerx -= 40;
			app->render->camera.x += 40;
			app->scene->vidas -= 1;
			score -= 100;
		}

		if (playerx > enemy1x  && God_Mode == 0) {
			playerx += 40;
			app->render->camera.x -= 40;
			app->scene->vidas -= 1;
			score -= 100;
		}

		app->scene->currentTicks_hit = 1;

	}

	if (playerx + 50 > enemy1x && playerx < enemy1x + 44 && playery > enemy1y -10 && playery < enemy1y && enemy1_state == true && app->input->GetKey(SDL_SCANCODE_K) == KEY_REPEAT && menuDisplay == false) {//Matar enemic1
		enemy1_state = false;
		score += 500;
		app->render->DrawTexture(blood, enemy1x +10, enemy1y, sangre);
	}

	enemy1y += 3;
	if (enemy1_state == true && activate1 == true && killer_mode == false) {//Enemy1 movement
		if (enemy1x > 1572 && enemy_movement == true) {
			app->render->DrawTexture(SoldDer1_, enemy1x, enemy1y);
			if (menuDisplay == false) {
				enemy1x += 3;
			}
			
		}
		if (enemy1x >= 2175) {
			enemy_movement = false;
		}
		if (enemy1x <= 2176 && enemy_movement == false) {
			app->render->DrawTexture(SoldIzq1_, enemy1x, enemy1y);
			if (menuDisplay == false) {
				enemy1x -= 3;
			}
		}
		if (enemy1x <= 1575) {
			enemy_movement = true;
		}
		//enemy1y -= gravity;
	}

	if (playerx > enemy1x - 200 && killer_mode == false) {
		killer_mode = true;
		app->render->DrawTexture(exclamacion, enemy1x+9, enemy1y - 140);
	}

	if (killer_mode == true && enemy1_state == true) {
		//enemy1y -= gravity;
		//app->render->DrawCircle(200, 200, 50, 70, 90, 100);
		if (playerx > enemy1x) {
			app->render->DrawTexture(SoldDer1, enemy1x, enemy1y);
			if (menuDisplay == false) {
				enemy1x += 5;
			}
			
		}
		if (playerx < enemy1x) {
			app->render->DrawTexture(SoldIzq1, enemy1x, enemy1y);
			if (menuDisplay == false) {
				enemy1x -= 5;
			}
		}
		if (playerx == enemy1x) {
			app->render->DrawTexture(SoldIzq1, enemy1x, enemy1y);
		}

	}
	if (playerx + 50 > enemy2x && playerx < enemy2x + 145 && playery>enemy2y + 57 && playery < enemy2y + 67 && God_Mode == 0 && enemy2_state == true && activate2 == true && jumping == true && menuDisplay == false) {
		enemy2_state = false;
		helicopter = true;
		score += 1000;
	}
	if (enemy2_state == true && activate2 == true) {//enemy2 movement
		if (playerx > enemy2x) {
			app->render->DrawTexture(HelDer, enemy2x, enemy2y);
			if (menuDisplay == false) {
				enemy2x += 3;
			}
			
		}
		if (playerx > enemy2x+300) {
			app->render->DrawTexture(HelDer, enemy2x, enemy2y);
			if (menuDisplay == false) {
				enemy2x += 4.2;
			}
		}
		if (playerx < enemy2x) {
			app->render->DrawTexture(HelIzq, enemy2x, enemy2y);
			if (menuDisplay == false) {
				enemy2x -= 3;
			}
		}
		if (playery < enemy2y && menuDisplay == false) {
			enemy2y-=1.5;
		}
		if (playery > enemy2y && menuDisplay == false) {
			enemy2y+=3.5;
		}

		if (playerx +50>enemy2x && playerx < enemy2x +145 && playery + 3 >enemy2y && playery < enemy2y + 57 && God_Mode == 0) {//enemy2 colisions
			//app->render->DrawCircle(300, 300, 50, 100, 100, 100);
			app->render->DrawTexture(blood, playerx + 10, playery, sangre);
			if (playerx < enemy2x) {
				playerx -= 40;
				app->render->camera.x += 40;
				app->scene->vidas -= 1;
			}

			if (playerx > enemy2x) {
				playerx += 40;
				app->render->camera.x -= 40;
				app->scene->vidas -= 1;
			}

			app->scene->currentTicks_hit = 1;
		}


	}


	if (playerx < 8400) {
		if (killcount3 == true) {
			app->render->DrawTexture(Personas_muertas, playerx + 1095, 410, people3);
		}

		if (killcount1 == true) {
			app->render->DrawTexture(Personas_muertas, playerx + 1070, 410, people);
		}

		if (killcount2 == true) {
			app->render->DrawTexture(Personas_muertas, playerx + 1085, 430, people2);
		}
		if (enemy1_state == false && activate1 == true) {
			app->render->DrawTexture(enemy_death, playerx + 1000, 400);
		}
		if (helicopter == true) {
			app->render->DrawTexture(helicopter_death, playerx + 800, 410);
		}
	}


	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && initial_screen >= 1 && menuDisplay == false) {
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

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && initial_screen >=1 && menuDisplay == false) {
		playerx -= velx;
		playeran->x = left3->x;
		playeran->y = left3->y;
		playeran->w = left3->w;
		playeran->h = left3->h;
		app->render->DrawTexture(img, playerx+2, playery, playeran);
	}

	if ((app->input->GetKey(SDL_SCANCODE_A) == NULL && app->input->GetKey(SDL_SCANCODE_D) == NULL) || menuDisplay == true){
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

	if (app->map->colisionsy_enemy == true) {
		enemy1y -= 3;
	}

	if (app->map->colisionsy == false) {
		vely -= gravity;
	}

	app->map->colisionsy = false;
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && jumping==false && God_Mode == 0 && menuDisplay == false) {
		app->map->colisionsy = false;
		vely = -10;
		jumping = true;
	}
	if (menuDisplay == false) {
		playery += vely;
	}
	
	

	// Draw map

	app->map->colisionsy_enemy = false;

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
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
				return 0;
		}
		enemy1_state = false;
		enemy2_state = false;
		// cambiar la imatge a la d victoria
	}

	if (vidas <= 0 && God_Mode == 0) {
		app->map->death = true;
	}

	if (app->map->death == true) {
		app->render->DrawTexture(app->scene->pantalla3, app->scene->playerx -100, 400, NULL);
		velx = 0;
		vely = 0;
		enemy1_state = false;
		enemy2_state = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && menuDisplay == false && pauseDisplay == false && vidas > 0 && initial_screen != 0 && playerx < 8400) {
		menuDisplay = true;
		pauseDisplay = true;

		app->audio->PlayFx(hold);
	}
	int x, y;
	Uint32 buttons;

	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);

	SDL_Rect rect1 = { playerx + 410,630,205,45 };
	SDL_Rect rect2 = { playerx + 410,685,205,45 };
	SDL_Rect rect3 = { playerx + 410,740,205,45 };
	SDL_Rect rect4 = { playerx + 410,790,205,45 };
	SDL_Rect rect5 = { playerx + 410,845,205,45 };

	if (pauseDisplay == true && playerx < 8400) {
		timeraux = false;
		timeraux3 = time;
		app->render->DrawTexture(pause, playerx + 250, 500);
		for (int i = 0; i < 20; i += 4) {
			if ((x >= menuCoords[i] && x <= menuCoords[i] + menuCoords[i + 2]) && y >= menuCoords[i + 1] - 400 && y <= menuCoords[i + 3] + menuCoords[i + 1] - 400) {
				//app->audio->PlayFx(hold);

				if (i == 0 && credit == false) {	
					app->render->DrawRectangle(rect1, 0, 250, 0);
					
					if (app->input->GetMouseButtonDown(1)) {
						pauseDisplay = false;
						timeraux = true;
						
					}
				}
				
				if (i == 4 && credit == false && settings == false) {
					app->render->DrawRectangle(rect2, 0, 250, 0);
					if (app->input->GetMouseButtonDown(1)) {
						app->audio->PlayFx(click);
						Reset();
					}
				}
				if (i == 8 && credit == false && settings == false) {
					app->render->DrawRectangle(rect3, 0, 250, 0);
					if (app->input->GetMouseButtonDown(1)) {
						app->audio->PlayFx(click);
						settings = true;
					}
				}
				if (i == 12 && credit == false && settings == false) {
					app->render->DrawRectangle(rect4, 250, 0, 0);
					if (app->input->GetMouseButtonDown(1)) {
						return false;
					}
				}
			}
		}
	}

	if (menuDisplay == true && initial_screen >= 1 && pauseDisplay == false) {
		if (menuCount == 0) {
			app->render->DrawTexture(menu, playerx + 250, 500);
		}
		if (menuCount == 1) {
			app->render->DrawTexture(menu2, playerx + 250, 500);
		}
		
		int x, y;
		Uint32 buttons;

		SDL_PumpEvents();  // make sure we have the latest mouse state.

		buttons = SDL_GetMouseState(&x, &y);
		
		SDL_Rect rect1 = { playerx + 410,630,205,45 };
		SDL_Rect rect2 = { playerx + 410,685,205,45 };
		SDL_Rect rect3 = { playerx + 410,740,205,45 };
		SDL_Rect rect4 = { playerx + 410,790,205,45 };
		SDL_Rect rect5 = { playerx + 410,845,205,45 };

		for (int i = 0; i < 20; i += 4) {
			if((x >= menuCoords[i] && x <= menuCoords[i] + menuCoords[i+2]) && y >= menuCoords[i+1]-400 && y<=menuCoords[i+3] + menuCoords[i+1]-400){
				//app->audio->PlayFx(hold);
				if (i == 0 && credit == false && settings == false) {
					app->render->DrawRectangle(rect1, 0, 250, 0);
					
					if (app->input->GetMouseButtonDown(1)) {
						app->audio->PlayFx(click);
						menuDisplay = false;
						timeraux = true;
					}
				}
				if (i == 4 && menuCount == 1 && credit == false && settings == false) {
					app->render->DrawRectangle(rect2, 0, 250, 0);
					if (app->input->GetMouseButtonDown(1)) {
						app->audio->PlayFx(click);
						app->LoadGameRequest();
						menuDisplay = false;
					}
				}
				if (i == 4 && menuCount == 0 && credit == false && settings == false) {
					app->render->DrawRectangle(rect2, 127, 127, 127);
					
				}
				if (i == 8 && credit == false && settings == false) {
					app->render->DrawRectangle(rect3, 0, 250, 0);
					if (app->input->GetMouseButtonDown(1)) {
						app->audio->PlayFx(click);
						settings = true;
					}
				}
				if (i == 12) {
					app->render->DrawRectangle(rect4, 0, 250, 0);
					if (app->input->GetMouseButtonDown(1)) {
						app->audio->PlayFx(click);
						credit = true;
					}

				}
				if (i == 16 && credit == false && settings == false) {
					app->render->DrawRectangle(rect5, 250, 0, 0);
					if (app->input->GetMouseButtonDown(1)) {
						return false;
					}
				}
				
			}
		}
	}

	SDL_PumpEvents();  // make sure we have the latest mouse state.

	buttons = SDL_GetMouseState(&x, &y);
	if (credit == true) {
		app->render->DrawTexture(credits, playerx-110, 400);
		SDL_Rect rect6 = { playerx + 95,540,30,30 };
		
		if (x >= 195 && x <= 225 && y >= 140 && y <= 170) {
			app->render->DrawRectangle(rect6, 250, 0, 0);
			if (app->input->GetMouseButtonDown(1)) {
				app->audio->PlayFx(click);
				credit = false;
			}
		}
		
	}

	if (settings == true) {

		app->render->DrawTexture(setting, playerx - 110, 400);
		app->render->DrawTexture(slider, sliderAux + playerx + 350, 675);
		app->render->DrawTexture(slider, sliderAux2 + playerx + 350, 745);
		SDL_Rect rect6 = { playerx + 95,540,30,30 };
		if (x >= 195 && x <= 225 && y >= 140 && y <= 170) {
			app->render->DrawRectangle(rect6, 250, 0, 0);
			if (app->input->GetMouseButtonDown(1)) {
				app->audio->PlayFx(click);
				settings = false;
			}
		}
		if (x >= sliderAux + 450 && x <= sliderAux + 500 && y >= 275 && y <= 325) {
			if (app->input->GetMouseButtonDown(1)) {
				if (x > 925) {
					x = 925;
				}
				if (x < 475) {
					x = 475;
				}
				sliderAux = x - 450 - 25;
				
			}
		}
		if (x >= sliderAux2 + 450 && x <= sliderAux2 + 500 && y >= 345 && y <= 395) {
			if (app->input->GetMouseButtonDown(1)) {
				if (x > 925) {
					x = 925;
				}
				if (x < 475) {
					x = 475;
				}
				sliderAux2 = x - 450 - 25;

			}
		}
		if (x > 465 && x < 465 + 58 && y >= 500 && y <= 550) {
			//SDL_Rect rect8 = { playerx + 365,900,58,50 };
			//app->render->DrawRectangle(rect8, 0, 250, 0);
			if (app->input->GetMouseButtonDown(1) && tick1 == false) {
				tick1 = true;
			}
			else if (app->input->GetMouseButtonDown(1) && tick1 == true) {
				tick1 = false;
			}
		}
		if (x > 788 && x < 788 + 58 && y >= 500 && y <= 550) {
			//SDL_Rect rect8 = { playerx + 688,900,58,50 };
			//app->render->DrawRectangle(rect8, 0, 250, 0);
			if (app->input->GetMouseButtonDown(1) && tick2 == false) {
				tick2 = true;
			}
			else if (app->input->GetMouseButtonDown(1) && tick2 == true) {
				tick2 = false;

			}
		}
		
		if (tick1 == true) {
			app->render->DrawTexture(tick, playerx + 365, 900);
		}
		if (tick2 == true) {
			app->render->DrawTexture(tick, playerx + 688, 900);
		}

	}

	Font();

	if (initial_screen >= 1 && app->map->death == false  && playerx < 8400) {
		PrintFont(playerx + 400, 450, score);
	}
	if (playerx >= 8400) {
		PrintFont(8800, 450, score);
	}

	if (app->map->death == true) {
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
			score = 0;
			return 0;
		}
		PrintFont(playerx + 450, 975, score);
	}

	timer = SDL_GetTicks() / 1000;

	if (timeraux == false ) {
		timeraux2 = timer;
		timer = timer - timer;
	}

	if (timeraux == true && playerx < 8400 && app->map->death == false && playerx < 9500) {

		time =  timeraux3 - (timer - timeraux2);
		PrintFont2(playerx + 450, 1000, time);
	}
	if (initial_screen >= 1 && playerx < 8400 && app->map->death == false && playerx < 9500) {
		app->render->DrawTexture(clock, playerx + 400, 995);
	}
	if (playerx >= 8400 && app->map->death == false && playerx < 9500) {
		time = 180 - (timer - timeraux2);
		PrintFont2(8850, 1000, time);
		app->render->DrawTexture(clock,8800, 995);
	}
	
	gameLoop();
	return true;
}
// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	

	
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

void Scene::Font()
{
	for (int x = 0; x < 10; x++) {
		nums[x] = { x * 22, 0, 23,44 };
	}
}

void Scene::PrintFont(int x, int y, uint score_) {

	int score_temp = score_;
	for (int i = 8; i >= 0; i--) {
		int temp = score_temp % 10;
		app->render->DrawTexture(font, i * 22 + x, y, &nums[temp]);
		score_temp = score_temp / 10;
	}


}

void Scene::PrintFont2(int x, int y, uint score_) {

	int score_temp = score_;
	for (int i = 2; i >= 0; i--) {
		int temp = score_temp % 10;
		app->render->DrawTexture(font, i * 22 + x, y, &nums[temp]);
		score_temp = score_temp / 10;
	}


}

void Scene :: Reset() {

	app->scene->pauseDisplay = false;
	
	app->render->camera.x = 0;
	app->render->camera.y = -400;

	app->scene->tick1 = false;
	app->scene->tick2 = false;
	app->scene->tickAux = 1;
	app->scene->tickAux2 = 1;

	app->scene->enemy1x = 1900;
	app->scene->enemy1y = 755;
	app->scene->killer_mode = false;

	app->scene->enemy2x = 5000;
	app->scene->enemy2y = 700;

	app->scene->enemy3x = 0;
	app->scene->enemy3y = 0;

	app->scene->enemy4x = 0;
	app->scene->enemy4y = 0;

	app->scene->enemy5x = 0;
	app->scene->enemy5y = 0;

	app->scene->playerx = 100.0;
	app->scene->playery = 510.0;
	app->scene->velx = 10;
	app->scene->vely = 200;

	app->scene->gravity = -0.5;
	app->scene->initial_y1;
	app->scene->jumping;
	app->scene->Show_colliders = 0;
	app->scene->God_Mode = 0;
	app->scene->initial_screen = -1.0;

	app->scene->killcount1 = false;
	app->scene->killcount2 = false;
	app->scene->killcount3 = false;
	app->scene->vidas = 3;
	app->scene->heart = true;
	app->scene->heart2 = true;
	app->scene->currentTicks_hit = 0;
	app->scene->aux_pos;

	app->scene->aux_check1 = false;
	app->scene->aux_check2 = false;

	app->scene->enemy_movement = true;
	app->scene->enemy1_state = false;
	app->scene->enemy2_state = false;
	app->scene->helicopter = false;
	app->scene->activate1 = false;
	app->scene->activate2 = false;

	app->scene->people_aux = true;
	app->scene->people_aux2 = true;
	app->scene->people_aux3 = true;
	app->scene->people_aux_int = 0;
	app->scene->stop = false;
	app->scene->shot_state = false;
	app->scene->shotx = enemy2x;
	app->scene->shoty = enemy2y + 40;

	app->scene->h = 0;
	app->scene->sliderAux;
	app->scene->sliderAux_;
	app->scene->sliderAux2;

	app->map->colisionsy;
	app->map->colisionsx = false;
	app->map->colisionsy_enemy;
	app->map->colisionsx_enemy = false;
	app->map->aux_col;
	app->map->death = false;

	app->map->klk;
	app->map->klk_;

	app->scene->score = 500;

}

bool Scene::SaveState(pugi::xml_node& configRenderer) const
{

		pugi::xml_node player = configRenderer.child("player");
		pugi::xml_node camera = configRenderer.child("camera");

		pugi::xml_node enemy3 = configRenderer.child("enemy3");
		pugi::xml_node enemy4 = configRenderer.child("enemy4");
		pugi::xml_node enemy5 = configRenderer.child("enemy5");

		player.attribute("x").set_value(playerx);
		player.attribute("y").set_value(playery);

		enemy3.attribute("x").set_value(enemy3x);
		enemy3.attribute("y").set_value(enemy3y);

		enemy4.attribute("x").set_value(enemy4x);
		enemy4.attribute("y").set_value(enemy4y);

		enemy5.attribute("x").set_value(enemy5x);
		enemy5.attribute("y").set_value(enemy5y);

		camera.attribute("x").set_value(app->render->camera.x);
		camera.attribute("y").set_value(app->render->camera.y);




	return true;
}

void Scene::gameLoop() {

	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN && _maxFPS == 60.0f) {
		_maxFPS = 30.0f;
	}
	if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN && _maxFPS == 30.0f) {
		_maxFPS = 60.0f;
	}

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

void Scene::stop_and_shot() {

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
		_fps = _maxFPS;
	}

}
