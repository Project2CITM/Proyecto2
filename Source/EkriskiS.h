#pragma once
#include "Spell.h"
class EkriskiS : public Spell
{
public:
	EkriskiS();

	void Execute(int level) override;


private:

	int damage[3];
};

