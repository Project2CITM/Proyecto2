#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Application.h"
#include "External/Box2D/Box2D/Box2D.h"
#include "RenderObject.hpp"

struct SDL_Texture;
class PhysBody;

#define MAX_GAMEOBJECT_TEXTURES 5

class GameObject 
{
public:

	GameObject();

	GameObject(std::string name = "Default", std::string tag = "None");

	GameObject(GameObject& obj);

	virtual ~GameObject();

	/// <summary>
	/// IMPORTANT: Do not destroy or disable anythink related to body in Trigger or Collision
	/// </summary>
	/// <param name="col"></param>
	virtual void OnCollisionEnter(PhysBody* col);

	/// <summary>
	/// IMPORTANT: Do not destroy or disable anythink related to body in Trigger or Collision
	/// </summary>
	/// <param name="col"></param>
	virtual void OnCollisionExit(PhysBody* col);

	/// <summary>
	/// IMPORTANT: Do not destroy or disable anythink related to body in Trigger or Collision
	/// </summary>
	/// <param name="col"></param>
	virtual void OnTriggerEnter(std::string trigger, PhysBody* col);

	/// <summary>
	/// IMPORTANT: Do not destroy or disable anythink related to body in Trigger or Collision
	/// </summary>
	/// <param name="col"></param>
	virtual void OnTriggerStay(std::string trigger, PhysBody* col);

	/// <summary>
	/// IMPORTANT: Do not destroy or disable anythink related to body in Trigger or Collision
	/// </summary>
	/// <param name="col"></param>
	virtual void OnTriggerExit(std::string trigger, PhysBody* col);

	virtual void Start();

	virtual void PreUpdate();

	virtual void Update();

	virtual void PostUpdate();

	virtual void CleanUp();

	bool CompareTag(std::string tag);

	iPoint GetDrawPosition(int index = 0);

	void UpdateOrderInLayer(int index = 0);

	/// <summary>
	/// Si exixte pBody devuelve angluo de pBody, si no el de GameObject 
	/// </summary>
	/// <returns>angulo en degradado</returns>
	float GetDegreeAngle();
	
	/// <summary>
	/// Si exixte pBody devuelve position de pBody, si no el de GameObject (px)
	/// </summary>
	/// <returns>position en pixel</returns>
	iPoint GetPosition();

	iPoint GetScreenPosition();

	/// <summary>
	/// Si exixte pBody devuelve position de pBody, si no {0,0}
	/// </summary>
	b2Vec2 GetLinearVelocity();

	/// <summary>
	/// Si exixte pBody, cambia la position de pBody, si no la de GameObject
	/// </summary>
	/// <param name="pos">= position in pixel</param>
	void SetPosition(iPoint pos);

	/// <summary>
	/// Si exixte pBody, cambia el amgulo de pBody, si no el de GameObject
	/// </summary>
	/// <param name="angle">= angle in deg</param>
	void SetRotation(float angle);

	/// <summary>
	/// Si exixte pBody, cambia la velocidad de pBody, si no saldra un aviso en Console
	/// </summary>
	/// <param name="vel"></param>
	void SetLinearVelocity(b2Vec2 vel);

	void SetLinearVelocity(fPoint vel);

protected:
	void InitRenderObjectWithXml(std::string texName = "null", int index = 0);

protected:
	Application* app = nullptr;

	iPoint position = { 0,0 };

	float rotation = 0;

public:
	std::string name = "";

	std::string tag = "";

	PhysBody* pBody = nullptr;

	RenderObject renderObjects[MAX_GAMEOBJECT_TEXTURES];

	bool pendingToDelete = false;

	bool adjustToGrid = false;

	bool isDie = false;

	bool enable = true;
};

#endif // !__GAMEOBJECT_H__