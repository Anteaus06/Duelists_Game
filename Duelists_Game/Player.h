#pragma once
#include "Character.h"
#include <iostream>

class Player : public Character
{
public:
	Player(int MaxHealth, int AtkPower, int Heal, int MaxStamina, std::string Name);
	
	Action ChooseAction() override;
	void GetHeal(int MaxHealth);

};





/*

public members of character remain public in Player
protected members of Character remain protected in Player.
Private members of Character remain inaccessible in Player 
(though Player can access them indirectly via public or protected methods in character).

*/