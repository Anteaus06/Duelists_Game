#include "Player.h"
#include <iostream>
#include "raylib.h"

//Passes all arguments to Character constructer
Player::Player(int MaxHealth, int AtkPower, int Heal, int MaxStamina, std::string Name) : Character(MaxHealth, AtkPower, Heal, MaxStamina, Name)
{

}


Action Player::ChooseAction()
{
	return GetActionFromInput(3);
}

void Player::GetHeal(int Heal)
{
	Heal = MaxHealth;
	MaxHealth + 2;
}
/*
int Input;
	while (true) 
	{

		DrawText("Choose Action fool: 1 Attack 2 Parry 3 Defend: ", 10, 30, 20, ORANGE) ;
		std::cin >> Input; 

		

		if (std::cin.fail() || Input < 1 || Input > 3) 
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //stating too many buttons typed or too long continue on new line
			DrawText("Invalid Input: Press 1 Attack 2 Parry 3 Defend: ", 10, 45, 20, RED);
			
		}
		else if(Input == 2 && Stamina == 0)
		{
			DrawText("Too tired to Parry, lets defend to rest ", 10, 180, 20, RED);
		
		}
		else 
		{
			break;
		}
	}

	Input -= 1;

	return GetActionFromInput(Input);
}

void Player::GetHeal(int Heal)
{
	Heal = MaxHealth;
	MaxHealth + 2;
	
}
*/


