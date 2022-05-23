#include "Trigger.h"
#include "ModulePhysics.h"
#include "ModuleScene.h"

/// <summary>
/// Create Rectangle Sensor attached to a gameobject
/// </summary>
/// <param name="pos"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="parent"></param>
/// <param name="name"></param>
/// <param name="follow"></param>
Trigger::Trigger(iPoint pos, int width, int height, GameObject* parent, std::string name, bool follow) : GameObject(name, name)
{
	pBody = app->physics->CreateRectangleSensor(pos, width, height, this);
	followFather = follow;
	this->parent = parent;
}

/// <summary>
/// Create a circle sensor attached to a game object
/// </summary>
/// <param name="pos"></param>
/// <param name="radius"></param>
/// <param name="parent"></param>
/// <param name="name"></param>
/// <param name="follow"></param>
Trigger::Trigger(iPoint pos, int radius, GameObject* parent, std::string name, bool follow) : GameObject(name, name)
{
	pBody = app->physics->CreateCircle(pos.x, pos.y, radius, this, true);
	followFather = follow;
	this->parent = parent;
}

void Trigger::Update()
{
	if (!AcceptAction()) return;

	if (!followFather) return;
	
	SetPosition(parent->GetPosition() + positionOffset);

	if (onTriggerStay && trig) parent->OnTriggerStay(this->name, trig);
}

void Trigger::PostUpdate()
{
	onTriggerEnter = false;

	onTriggerExit = false;
}

void Trigger::OnCollisionEnter(PhysBody* col)
{
	onTriggerEnter = true;

	onTriggerStay = true;

	if (!AcceptAction()) return;

	trig = col;

	parent->OnTriggerEnter(this->name, col);
}

void Trigger::OnCollisionExit(PhysBody* col)
{
	trig = nullptr;

	onTriggerExit = true;

	onTriggerStay = false;

	if (!AcceptAction()) return;
	
   parent->OnTriggerExit(this->name, col);
}

void Trigger::Destroy()
{
	pendingToDelete = true;

	parent = nullptr;

	pendingToDelete = true;
}

bool Trigger::AcceptAction()
{
	if (app->Exiting()) return false;

	if (app->scene->isChangingScene) return false;

	if (pendingToDelete) return false;

	if (parent == nullptr || !parent->enable) return;

	if (parent->pendingToDelete)
	{
		pendingToDelete = true;
		return false;
	}

	return true;
}