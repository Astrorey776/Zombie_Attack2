
#include "App.h"
#include "Render.h"
#include "Textures.h"
#include "Map.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>

Map::Map() : Module(), mapLoaded(false)
{
    name.Create("map");
}

// Destructor
Map::~Map()
{}

// L06: TODO 7: Ask for the value of a custom property
int Properties::GetProperty(const char* value, int defaultValue) const
{
	//...

	ListItem<Property*>* item = list.start;

	while (item)
	{
		if (item->data->name == value)
			return item->data->value;
		item = item->next;
	}

	return defaultValue;
}

// Called before render is available
bool Map::Awake(pugi::xml_node& config)
{
    LOG("Loading Map Parser");
    bool ret = true;

    folder.Create(config.child("folder").child_value());

    return ret;
}

void Map::ResetPath()
{
	frontier.Clear();
	visited.clear();

	frontier.Push(iPoint(19, 4), 0);
	visited.add(iPoint(19, 4));
}

void Map::DrawPath()
{
	iPoint point;

	// Draw visited
	ListItem<iPoint>* item = visited.start;

	while (item)
	{
		point = item->data;
		TileSet* tileset = GetTilesetFromTileId(26);

		SDL_Rect rec = tileset->GetTileRect(26);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);

		item = item->next;
	}

	// Draw frontier
	for (uint i = 0; i < frontier.Count(); ++i)
	{
		point = *(frontier.Peek(i));
		TileSet* tileset = GetTilesetFromTileId(25);

		SDL_Rect rec = tileset->GetTileRect(25);
		iPoint pos = MapToWorld(point.x, point.y);

		app->render->DrawTexture(tileset->texture, pos.x, pos.y, &rec);
	}

}

bool Map::IsWalkable(int x, int y) const
{
	// L10: DONE 3: return true only if x and y are within map limits
	// and the tile is walkable (tile id 0 in the navigation layer)

	bool isWalkable = false;
	if (x >= 0 && y >= 0 && x <= mapData.width && y <= mapData.height) {

		//gets the second layer
		MapLayer* layer = mapData.layers.start->next->data;
		int tileId = layer->Get(x, y);
		if (tileId != 26) isWalkable = true;
	}

	isWalkable = true;
	return isWalkable;
}

int Map::MovementCost(int x, int y) const
{
	int ret = -1;

	if ((x >= 0) && (x < mapData.width) && (y >= 0) && (y < mapData.height))
	{
		int id = mapData.layers.start->next->data->Get(x, y);

		if (id == 0) ret = 1;
		else ret = -1;
	}

	return ret;
}

void Map::PropagateBFS()
{
	// L10: DONE 1: If frontier queue contains elements
	// pop the last one and calculate its 4 neighbors
	iPoint curr;
	if (frontier.Pop(curr))
	{
		// L10: DONE 2: For each neighbor, if not visited, add it
		// to the frontier queue and visited list
		iPoint neighbors[4];
		neighbors[0].create(curr.x + 1, curr.y + 0);
		neighbors[1].create(curr.x + 0, curr.y + 1);
		neighbors[2].create(curr.x - 1, curr.y + 0);
		neighbors[3].create(curr.x + 0, curr.y - 1);

		for (uint i = 0; i < 4; ++i)
		{
			if (MovementCost(neighbors[i].x, neighbors[i].y) > 0)
			{
				if (visited.find(neighbors[i]) == -1)
				{
					frontier.Push(neighbors[i], 0);
					visited.add(neighbors[i]);

					// L11: TODO 1: Record the direction to the previous node 
					// with the new list "breadcrumps"

				}
			}
		}
	}
}

// Draw the map (all requried layers)
void Map::Draw()
{
	if (mapLoaded == false) return;

	// L04: DONE 5: Prepare the loop to draw all tilesets + DrawTexture()
	ListItem<MapLayer*>* mapLayerItem;
	mapLayerItem = mapData.layers.start;

	while (mapLayerItem != NULL) {
		if (mapLayerItem->data->properties.GetProperty("Draw") == 1) {
			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					// L04: DONE 9: Complete the draw function
					int gid = mapLayerItem->data->Get(x, y);

					if (gid > 0) {

						//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
						//now we always use the firt tileset in the list
						TileSet* tileset = mapData.tilesets.start->data;


						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);

						app->render->DrawTexture(tileset->texture,
							pos.x,
							pos.y,
							&r);
					}

				}
				
			}
		}
		if (mapLayerItem->data->properties.GetProperty("Draw") == 0  && mapLayerItem->data->properties.GetProperty("Navigation") == 1) {
			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					// L04: DONE 9: Complete the draw function
					int gid = mapLayerItem->data->Get(x, y);

					/*if (app->scene->playery = y * 32 - 56) {
						app->scene->playery = 710;
					}*/

					if (gid > 0) {

						//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
						//now we always use the firt tileset in the list
						TileSet* tileset = mapData.tilesets.start->data;


						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);
						if (app->scene->Show_colliders == 1) {
							//w = 42	h = 46
							SDL_Rect playerRect = { app->scene->playerx, app->scene->playery, 42, 52 };
							app->render->DrawRectangle(playerRect, 0, 250, 0);
							if (app->scene->enemy1_state == true) {
								SDL_Rect enemyRect = { app->scene->enemy1x + 10, app->scene->enemy1y, 44, 64 };
								app->render->DrawRectangle(enemyRect, 0, 250, 250);
								SDL_Rect enemyRect_kill = { app->scene->enemy1x + 10, app->scene->enemy1y - 10, 44, 10 };
								app->render->DrawRectangle(enemyRect_kill, 255, 0, 0);
							}
							app->render->DrawTexture(tileset->texture,
								pos.x,
								pos.y,
								&r);
						}

						if (app->scene->playery < (y * 32) + 32 && app->scene->playery >y * 32 && app->scene->playerx+42>x*32 && app->scene->playerx <x*32+32) {
							klk = true;
							app->render->DrawCircle(500, 100, 50, 255, 255, 255);
						}

						if ((app->scene->playerx + 42 > (x * 32)) && (app->scene->playerx < (x * 32) + 32) &&
							(app->scene->playery + 52 + app->scene->vely > (y * 32)) && (app->scene->playery - app->scene->vely + 48 < (y * 32)) && app->scene->God_Mode == 0) {
							//Colliding vertical
							app->render->DrawCircle(100, 100, 50, 250, 0, 0);
							colisionsy = true;
							klk = false;
						}
						if ((app->scene->playerx + 32 + app->scene->velx > (x * 32)) && (app->scene->playerx < (x * 32) + 32) &&
							((app->scene->playery + 52 - 5 > (y * 32)) && (app->scene->playery - 32 < (y * 32))||((app->scene->playery + 52 - 5 > (y-1 * 32)) && (app->scene->playery - 32 < (y-1 * 32)))) 
							&& klk == false && app->scene->God_Mode == 0) {
							//Colliding horitzontal
							
							colisionsx = true;
							if (app->scene->playerx +10 <(x*32) +32 ) {// Passa de esquerra a dreta
								app->scene->playerx = (x * 32) - 42;
								aux_col = app->scene->playerx;
								app->render->DrawCircle(300, 100, 50, 255, 0, 255);
							}
							if (app->scene->playerx - 10 > (x * 32)) {	//Passa d'esquerra a dreta
								app->scene->playerx = (x * 32) + 32;
								aux_col = app->scene->playerx;
								app->render->DrawCircle(400, 100, 50, 255, 255, 255);
							}
							app->render->DrawCircle(200, 100, 50, 0, 0, 255);
						}
					}
				}

			}
		}
		if (mapLayerItem->data->properties.GetProperty("Draw") == 0 && mapLayerItem->data->properties.GetProperty("Navigation") == 2) {
			for (int x = 0; x < mapLayerItem->data->width; x++)
			{
				for (int y = 0; y < mapLayerItem->data->height; y++)
				{
					// L04: DONE 9: Complete the draw function
					int gid = mapLayerItem->data->Get(x, y);

					/*if (app->scene->playery = y * 32 - 56) {
						app->scene->playery = 710;
					}*/

					if (gid > 0) {

						//L06: TODO 4: Obtain the tile set using GetTilesetFromTileId
						//now we always use the firt tileset in the list
						TileSet* tileset = mapData.tilesets.start->data;


						SDL_Rect r = tileset->GetTileRect(gid);
						iPoint pos = MapToWorld(x, y);
						if(app->scene->Show_colliders == 1)
						app->render->DrawTexture(tileset->texture,
							pos.x,
							pos.y,
							&r);

						//w = 42	h = 46
						if ((app->scene->playerx + 42 > (x * 32)) && (app->scene->playerx < (x * 32) + 32) &&
							(app->scene->playery + 52 > (y * 32)) && (app->scene->playery < (y * 32) + 32) && (colisionsy == false)&& app->scene->God_Mode == 0
							&& app->scene->currentTicks_hit == 0) {
							//Colliding muerte
							if (app->scene->vely != 0) {
								app->scene->vely *= -(1.1);
							}
							else {
								app->scene->vely = -10;
							}
							app->scene->currentTicks_hit = 1;
							app->scene->vidas -= 1;
							//death = true;
							
							app->render->DrawCircle(200, 100, 50, 0, 255, 0);
						}
					}
				}
			}
		}
		mapLayerItem = mapLayerItem->next;
	}
}



// L04: DONE 8: Create a method that translates x,y coordinates from map positions to world positions
iPoint Map::MapToWorld(int x, int y) const
{
	iPoint ret;
	if (mapData.type == MAPTYPE_ISOMETRIC) {

		ret.x = (x - y) * (mapData.tileWidth * 0.5f);
		ret.y = (x + y) * (mapData.tileHeight * 0.5f);
	}
	if (mapData.type == MAPTYPE_ORTHOGONAL) {
		ret.x = x * mapData.tileWidth;
		ret.y = y * mapData.tileHeight;
	}

	// L05: TODO 1: Add isometric map to world coordinates


	return ret;
}


iPoint Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	// L05: TODO 2: Add orthographic world to map coordinates

	// L05: TODO 3: Add the case for isometric maps to WorldToMap


	return ret;
}

// L06: TODO 3: Pick the right Tileset based on a tile id
TileSet* Map::GetTilesetFromTileId(int id) const
{
	ListItem<TileSet*>* item = mapData.tilesets.start;
	TileSet* set = item->data;

	while (item)
	{
		if (id < item->data->firstgid)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}

	return set;
}

// Get relative Tile rectangle
SDL_Rect TileSet::GetTileRect(int id) const
{
	SDL_Rect rect = { 0 };

	// L04: DONE 7: Get relative Tile rectangle
	int relativeId = id - firstgid;
	rect.w = tileWidth;
	rect.h = tileHeight;
	rect.x = margin + ((rect.w + spacing) * (relativeId % columns));
	rect.y = margin + ((rect.h + spacing) * (relativeId / columns));
	
	return rect;
}

// Called before quitting
bool Map::CleanUp()
{
    LOG("Unloading map");

    // L03: DONE 2: Make sure you clean up any memory allocated from tilesets/map
    // Remove all tilesets
	ListItem<TileSet*>* item;
	item = mapData.tilesets.start;

	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	mapData.tilesets.clear();

	// L04: DONE 2: clean up all layer data
	// Remove all layers
	ListItem<MapLayer*>* item2;
	item2 = mapData.layers.start;

	while (item2 != NULL)
	{
		RELEASE(item2->data);
		item2 = item2->next;
	}
	mapData.layers.clear();

    return true;
}

// Load new map
bool Map::Load(const char* filename)
{
    bool ret = true;
    SString tmp("%s%s", folder.GetString(), filename);

	pugi::xml_document mapFile; 
    pugi::xml_parse_result result = mapFile.load_file(tmp.GetString());

    if(result == NULL)
    {
        LOG("Could not load map xml file %s. pugi error: %s", filename, result.description());
        ret = false;
    }

	// Load general info
    if(ret == true)
    {
        // L03: DONE 3: Create and call a private function to load and fill all your map data
		ret = LoadMap(mapFile);
	}

    // L03: DONE 4: Create and call a private function to load a tileset
    // remember to support more any number of tilesets!
	if (ret == true)
	{
		ret = LoadTileSets(mapFile.child("map"));
	}

	// L04: DONE 4: Iterate all layers and load each of them
	// Load layer info
	if (ret == true)
	{
		ret = LoadAllLayers(mapFile.child("map"));
	}
    
    if(ret == true)
    {
        // L03: TODO 5: LOG all the data loaded iterate all tilesets and LOG everything
		 
		LOG("Successfully parsed map XML file: %s", filename);
		LOG("width: %d", mapData.width);
		LOG("height: %d", mapData.height);
		LOG("tile width: %d", mapData.tileWidth);
		LOG("tile height: %d", mapData.tileHeight);
		if (mapData.type == MAPTYPE_ORTHOGONAL)
		{
			LOG("orientation: orthogonal");
		}
		else if (mapData.type == MAPTYPE_ISOMETRIC)
		{
			LOG("orientation: isometric");
		}

		ListItem<TileSet*>* tileset;
		tileset = mapData.tilesets.start;
		int tilesetCtr = 0;
		while (tileset != NULL)
		{
			LOG("Tileset %d", tilesetCtr +1);
			LOG("name: %s", tileset->data->name.GetString());
			LOG("first gid: %d", tileset->data->firstgid);
			LOG("margin: %d", tileset->data->margin);
			LOG("spacing: %d", tileset->data->spacing);
			LOG("tile width: %d", tileset->data->tileWidth);
			LOG("tile height: %d", tileset->data->tileHeight);
			LOG("width: %d", tileset->data->texWidth);
			LOG("height: %d", tileset->data->texHeight);

			tileset = tileset->next;
			tilesetCtr++;
		}

		// L04: TODO 4: LOG the info for each loaded layer
		ListItem<MapLayer*>* layer;
		layer = mapData.layers.start;
		int layerCtr = 0;

		while (layer != NULL)
		{
			LOG("Layer %d", layerCtr + 1);
			LOG("name: %s", layer->data->name.GetString());
			LOG("width: %d", layer->data->width);
			LOG("height: %d", layer->data->height);
			
			layerCtr++;
			layer = layer->next;
		}
    }

    mapLoaded = ret;

    return ret;
}

// L03: TODO: Load map general properties
bool Map::LoadMap(pugi::xml_node mapFile)
{
	bool ret = true;
	pugi::xml_node map = mapFile.child("map");

	if (map == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'map' tag.");
		ret = false;
	}
	else
	{
		// L03: DONE 3: Load map general properties
		mapData.height = map.attribute("height").as_int();
		mapData.width = map.attribute("width").as_int();
		mapData.tileHeight = map.attribute("tileheight").as_int();
		mapData.tileWidth = map.attribute("tilewidth").as_int();

		// L05: DONE 1: Add formula to go from isometric map to world coordinates
		mapData.type = MAPTYPE_UNKNOWN;
		if (strcmp(map.attribute("orientation").as_string(), "isometric") == 0)
		{
			mapData.type = MAPTYPE_ISOMETRIC;
		}
		if (strcmp(map.attribute("orientation").as_string(), "orthogonal") == 0)
		{
			mapData.type = MAPTYPE_ORTHOGONAL;
		}
	}

	return ret;
}

// L03: DONE 4: Implement the LoadTileSet function to load the tileset properties
bool Map::LoadTileSets(pugi::xml_node mapFile) {

	bool ret = true;

	pugi::xml_node tileset;
	for (tileset = mapFile.child("tileset"); tileset && ret; tileset = tileset.next_sibling("tileset"))
	{
		TileSet* set = new TileSet();
		if (ret == true) ret = LoadTilesetDetails(tileset, set);
		if (ret == true) ret = LoadTilesetImage(tileset, set);
		mapData.tilesets.add(set);
	}

	return ret;
}

// L03: DONE 4: Load Tileset attributes
bool Map::LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;

	// L03: DONE 4: Load Tileset attributes
	set->name.Create(tileset_node.attribute("name").as_string());
	set->firstgid = tileset_node.attribute("firstgid").as_int();
	set->tileWidth = tileset_node.attribute("tilewidth").as_int();
	set->tileHeight = tileset_node.attribute("tileheight").as_int();
	set->margin = tileset_node.attribute("margin").as_int();
	set->spacing = tileset_node.attribute("spacing").as_int();
	set->tilecount = tileset_node.attribute("tilecount").as_int();
	set->columns = tileset_node.attribute("columns").as_int();

	return ret;
}

// L03: DONE 4: Load Tileset image
bool Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		// L03: DONE 4: Load Tileset image
		SString tmp("%s%s", folder.GetString(), image.attribute("source").as_string());
		set->texture = app->tex->Load(tmp.GetString());
	}

	return ret;
}

// L04: DONE 3: Implement a function that loads a single layer layer
bool Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	//Load the attributes
	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();

	//L06: TODO 6 Call Load Properties
	LoadProperties(node, layer->properties);

	//Reserve the memory for the tile array
	layer->data = new uint[layer->width * layer->height];
	memset(layer->data, 0, layer->width * layer->height);

	//Iterate over all the tiles and assign the values
	pugi::xml_node tile;
	int i = 0;
	for (tile = node.child("data").child("tile"); tile && ret; tile = tile.next_sibling("tile"))
	{
		layer->data[i] = tile.attribute("gid").as_int();
		i++;
	}

	return ret;
}

// L04: DONE 4: Iterate all layers and load each of them
bool Map::LoadAllLayers(pugi::xml_node mapNode) {
	bool ret = true;
	for (pugi::xml_node layerNode = mapNode.child("layer"); layerNode && ret; layerNode = layerNode.next_sibling("layer"))
	{
		//Load the layer
		MapLayer* mapLayer = new MapLayer();
		ret = LoadLayer(layerNode, mapLayer);

		//add the layer to the map
		mapData.layers.add(mapLayer);
	}

	return ret;
}

// L06: TODO 6: Load a group of properties from a layer and fill a list with it
bool Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	for (pugi::xml_node propertieNode = node.child("properties").child("property"); propertieNode; propertieNode = propertieNode.next_sibling("property"))
	{
		Properties::Property* p = new Properties::Property();
		p->name = propertieNode.attribute("name").as_string();
		p->value = propertieNode.attribute("value").as_int();

		properties.list.add(p);
	}

	return ret;
}
