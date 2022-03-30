#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

#include "Scene.h"

class GUIButton;

class MainMenu : public Scene
{
public:

	// Constructor
	MainMenu();

	// Destructor
	~MainMenu();

	virtual bool InitScene();

	bool Start() override;

	bool PreUpdate() override;

	bool Update() override;

	bool PostUpdate() override;

	bool CleanUp() override;


private:
	GUIButton* PlayBUT = nullptr;
};

#endif //__MAIN_MENU_H__
