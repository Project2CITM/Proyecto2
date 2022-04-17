#include "Enemy.h"
#include "ModulePhysics.h"
#include "DamageArea.h"
#include "SpellSpawnManager.h"

Enemy::Enemy(std::string name) :GameObject(name, "Enemy")
{
	spawnManager = SpellSpawnManager::GetInstance();
}

Enemy::~Enemy()
{
}

void Enemy::Start()
{
}

void Enemy::PreUpdate()
{
	GameObject::PreUpdate();
}

void Enemy::Update()
{
	GameObject::Update();
}

void Enemy::PostUpdate()
{
	GameObject::PostUpdate();
}

void Enemy::CleanUp()
{
	if (!spawnManager->IsDeleted()) spawnManager->SpawnSpell(GetPosition());
}

void Enemy::OnCollisionEnter(PhysBody* col)
{
}

void Enemy::OnCollisionExit(PhysBody* col)
{
}

void Enemy::OnTriggerEnter(std::string trigger, PhysBody* col)
{
	if (col->gameObject == nullptr) return;

	if (col->gameObject->tag == "DamageArea") // If hit by a DamageArea
	{
		DamageArea* takenDamage = (DamageArea*)col->gameObject;

		Hit(takenDamage->GetDamage());
	}
}

void Enemy::Hit(int damage)
{
	health -= damage;
	if (health <= 0) Die();
}

void Enemy::Die()
{
	isDie = true;
	pendingToDelete = true;
}
