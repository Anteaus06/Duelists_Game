#pragma once
#include "Character.h"
#include <random>
#include <iostream>

class Enemy : public Character
{
public:
	Enemy(int MaxHealth, int AtkPower, int Heal, int MaxStamina, std::string Name);

	
	Action ChooseAction() override;
	void IncreaseDifficulty(int RoundNumber);

private:

	std::mt19937 Generator;
	std::uniform_int_distribution<> Distribution;
};
