#include "Player.h"
#include "PlayerController.h"
#include "Application.h"
#include "PlayerStats.h"

Player::Player()
{
	controller = new PlayerController("Player", "Player", this);
}



void Player::CleanUp()
{
	// THE CONTROLLER IS CLEANED UP BY THE SCENE, AS IT IS A GAMEOBJECT AND, THEREFOR, MANAGED BY THE SCENE
	if (stats != nullptr)
	{
		stats->CleanUp();
		RELEASE(stats);
	}
	if (controller != nullptr)controller->pendingToDelete = true;
		
}

void Player::ChangeShield(int num)
{
	shield += num;
	if (shield < 0) shield = 0;
}
