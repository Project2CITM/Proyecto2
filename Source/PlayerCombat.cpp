#include "PlayerCombat.h"
#include "Player.h"
#include "ModulePhysics.h"
#include "PlayerController.h"
#include "SpellInfo.h"

PlayerCombat::PlayerCombat(std::string name, std::string tag, Player* player) : GameObject(name, tag)
{
	this->player = player;
}

void PlayerCombat::Start()
{
	revenantAttack = app->physics->CreateRectangleSensor(player->controller->GetPosition(), 12, 20, this);
	revenantAttack->body->SetActive(false);

	// Test Code-----------------------------------------
	availableSpellSlots = 4;

	availableDeckSlots = 6;

	// Attack action stats
	attackCD = 75;
	attackCounter = 0;
	canAttack = true;

	// Attack area stats
	attackAreaActive = false;
	attackAreaCD = 15;
	attackAreaCounter = 0;
	for (int i = 0; i < availableSpellSlots; i++)
	{
		spellSlots.add(new SpellInfo());
	}

	for (int i = 0; i < availableDeckSlots; i++)
	{
		deckSlots.add(new SpellInfo());
	}

	spellSlots[0]->ChangeSpell(SpellID::COVER, 2);

	// Test Code-----------------------------------------

	selectedSpell = 0;
}

void PlayerCombat::Update()
{
	if (!canAttack)
	{
		attackCounter++;
		if (attackCounter >= attackCD)
		{
			canAttack = true;
			attackCounter = 0;
		}
	}

	if (attackAreaActive)
	{
		attackAreaCounter++;
		if (attackAreaCounter >= attackAreaCD)
		{
			attackAreaActive = false;
			revenantAttack->body->SetActive(false);
			attackAreaCounter = 0;
		}
	}
}

void PlayerCombat::Attack()
{
	if (!canAttack) return;

	switch (player->playerClass)
	{
	case PlayerClass::REVENANT:
		RevenantAttack();
		printf("Attack Revenant!\n");
		break;
	case PlayerClass::SAGE:
		printf("Attack Sage!\n");
		break;
	}
	canAttack = false;
}

void PlayerCombat::CastSpell()
{
	if (executeSpellCommand.Execute(spellSlots[selectedSpell])) // Execute the selected spell and get response
	{ 
		// If returns true, the selected spell is deleted from the current spell slot
		spellSlots[selectedSpell]->EmptySpell();
	}
}

void PlayerCombat::ChangeSelectedSpellSlot(int num)
{
	selectedSpell += num; // Change Selected Spell Slot

	if (selectedSpell > availableSpellSlots) // If we are over the limit, go back to first
	{
		selectedSpell = 0;
	}
	else if (selectedSpell < 0) // If we are under the first, go to the last slot
	{
		selectedSpell = availableSpellSlots - 1;
	}

	printf("Current Spell Slot: %d\n", selectedSpell);


}

bool PlayerCombat::AddSpell(SpellInfo spell)
{
	// Check for an empty spell slot.
	for (int i = 0; i < spellSlots.count(); i++)
	{
		if (spellSlots[i]->id == SpellID::NONE)
		{
			spellSlots[i]->ChangeSpell(spell.id, spell.spellLevel);
			PrintSlotsState();
			return true;
		}
	}

	// Check for an empty deck slot.
	for (int i = 0; i < deckSlots.count(); i++)
	{
		if (deckSlots[i]->id == SpellID::NONE)
		{
			deckSlots[i]->ChangeSpell(spell.id, spell.spellLevel);
			PrintSlotsState();
			return true;
		}
	}

	// If neither the spell slots nor the deck slots have an empty slot, return false
	return false;
}

void PlayerCombat::CheckDeck()
{
	for (int i = 0; i < spellSlots.count(); i++)
	{
		// If the spell slot is not empty, check the next one
		if (spellSlots[i]->id != SpellID::NONE) continue;
		
		// If a spell slot is empty, fill it with one of the deck Slots.
		for (int j = 0; j < deckSlots.count(); j++)
		{
			if (deckSlots[j]->id != SpellID::NONE) // Not empty deck slot
			{
				spellSlots[i]->ChangeSpell(deckSlots[j]->id, deckSlots[j]->spellLevel);
				deckSlots[j]->EmptySpell();
			}
		}
		
	}
}

void PlayerCombat::CleanUp()
{
	if (revenantAttack != nullptr) RELEASE(revenantAttack);
	
	executeSpellCommand.CleanUp();
	spellSlots.clearPtr();
	deckSlots.clearPtr();
}

void PlayerCombat::PrintSlotsState()
{
	for (int i = 0; i < spellSlots.count(); i++)
	{
		printf("Spell slot %d contains spell %d at level %d\n", i, (int)spellSlots[i]->id, spellSlots[i]->spellLevel);
	}
	for (int i = 0; i < deckSlots.count(); i++)
	{
		printf("Deck slot %d contains spell %d at level %d\n", i, (int)deckSlots[i]->id, deckSlots[i]->spellLevel);
	}
}

void PlayerCombat::RevenantAttack()
{
	// Set area as active
	revenantAttack->body->SetActive(true);

	// Calculate attack offset and rotation based on looking direction
	b2Vec2 attackOffset;
	float rotation = 0;
	switch (player->controller->lookingDir)
	{
	case LookingDirection::DOWN:
		attackOffset = { 0, 1.5f };
		rotation = 90 * DEGTORAD;
		break;
	case LookingDirection::UP:
		attackOffset = { 0, -1.5f };
		rotation = 90 * DEGTORAD;
		break;
	case LookingDirection::LEFT:
		attackOffset = { -1, 0 };
		break;
	case LookingDirection::RIGHT:
		attackOffset = {1, 0 };
		break;
	}

	// Place on correct position
	revenantAttack->body->SetTransform(player->controller->pBody->body->GetPosition() + attackOffset, rotation);

	attackAreaActive = true;
}
