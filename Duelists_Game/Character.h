#pragma once
#include <string>


enum Action
{
	ATTACK,
	PARRY,
	DEFEND,
	NONE
};
class Character
{

public:
	Character(int MaxHealth, int AtkPower, int Heal, int MaxStamina, std::string Name);

	int GetHealth() const { return Health; } // typed all on 1 line to show not editing
	std::string GetName() const { return Name; }
	bool GetIsAlive() const { return Health > 0; }
	int GetAtkPower() const { return AtkPower; }
	void UpdateHealth(int Amount);
	void UpdateStamina(bool Increase);
	int GetStamina() const { return Stamina; }
	void GetHeal(int Heal);

	virtual Action ChooseAction() = 0;
	void InitStats();
	Action GetActionFromInput(int Input);

protected:
	std::string Name;
	int MaxHealth;
	int Health;
	int AtkPower;
	int Heal;
	int MaxStamina;
	int Stamina;
};