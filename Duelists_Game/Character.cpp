#include "Character.h"
#include <iostream>



Character::Character(int MaxHealth, int AtkPower, int Heal, int MaxStamina, std::string Name) : 
	MaxHealth(MaxHealth), AtkPower(AtkPower), Heal(Heal), MaxStamina(MaxStamina), Name(Name)  
{
	InitStats();
}

void Character::UpdateHealth(int Amount)
{
	Health += Amount;
	if (Health <= 0) Health = 0;
	std::cout << Name << " has " << Health << " remaining" << std::endl;
}

void Character::UpdateStamina(bool Increase)
{
	Stamina = (Increase) ? Stamina += 1 : Stamina -= 1;
	if (Stamina >= MaxStamina)
	{
		Stamina = MaxStamina;
	}
	else if (Stamina <= 0)
	{
		Stamina = 0;
	}
}
void Character::InitStats()
{
	Health = MaxHealth;
	Stamina = MaxStamina;
}

void Character::GetHeal(int Heal)
{
	Heal = MaxHealth + 2;

	std::cout << Name << " healed " << std::endl;
}

Action Character::GetActionFromInput(int Input)
{
	switch (Input)
	{
	case 0:
		return ATTACK;
	case 1:
		UpdateStamina(false);
		return PARRY;
	case 2:
		UpdateStamina(true);
		return DEFEND;
	}
	return NONE;
}


