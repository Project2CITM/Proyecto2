#ifndef __MAPLOADER_H__
#define __MAPLOADER_H__

#include "GameObject.h"
#include "ModulePhysics.h"
#include "Room.h"

class MapLoader
{
public:
	MapLoader() {
		this->app = Application::GetInstance();
	}

	//Create colliders from TMX to room collider array.
	void ExtractMapColliders(Room* r);

private:
	void LoadMap(short id);
	void CreateColliders(Room* r);

private:
	Application* app;
	pugi::xml_document mapDoc;
	pugi::xml_node mapNode;
};

#endif //_MAPLOADER_H_