#include "Player.h"
#include "Enemy.h"
#include "Log.h"

//Passes all arguments to Character constructer
Player::Player(int MaxHealth, int AtkPower, int Heal, int MaxStamina, std::string Name) : Character(MaxHealth, AtkPower, Heal, MaxStamina, Name)
{

}

Action Player::ChooseAction()
{
	int Input;
	while (true) 
	{

		Log::LogMessage(LOG_DEFAULT, "Choose Action fool: 1 Attack 2 Parry 3 Defend: ");
		std::cin >> Input;

		

		if (std::cin.fail() || Input < 1 || Input > 3) 
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //stating too many buttons typed or too long continue on new line
			Log::LogMessage(LOG_ERROR, "Invalid Input: Press 1 Attack 2 Parry 3 Defend: ");
		}
		else if(Input == 2 && Stamina == 0)
		{
			Log::LogMessage(LOG_ERROR, "Too tired to Parry, lets defend to rest ");
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


