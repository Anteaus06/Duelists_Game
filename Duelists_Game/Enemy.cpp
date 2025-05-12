#include "Enemy.h"



//Passes all arguments to Character constructor
Enemy::Enemy(int MaxHealth, int AtkPower, int Heal, int MaxStamina, std::string Name) : 
	Character(MaxHealth, AtkPower, Heal, MaxStamina,Name), Generator(std::random_device{}()), Distribution(0, 2)
{

}

Action Enemy::ChooseAction()
{
	int Input = Distribution(Generator);
	if (Stamina == 0)
	{
		std::uniform_int_distribution<> LimitedDistribution(0, 2);
		Input = LimitedDistribution(Generator) == 1 ? 0 : 2; //make enemy exhausted or dazed
	}
	return GetActionFromInput(Input);
}
void Enemy::IncreaseDifficulty(int RoundNumber)
{
		switch (RoundNumber)
		{
		case 1:
			return;
			
		case 2:
			Health += RoundNumber;
			Name = "teen girl";
			std::cout << "teen girl has extra health" << std::endl;
			return;
		case 3:
			Health += RoundNumber;
			//AtkPower += RoundNumber;
			Name = "Woman";
			std::cout << "This woman is strong and has extra health" << std::endl;    
			return;
		case 4:
			Health += RoundNumber;
			//AtkPower += RoundNumber;
			Name = "Wife";
			std::cout << "Wife has extra health and is stronger" << std::endl;
			return;
		case 5:
			Health += RoundNumber;
			//AtkPower += RoundNumber;
			//AtkPower += RoundNumber / 2;
			Name = "Eve";
			std::cout << "Eve hits harder and has extra health" << std::endl;
			return;
		}

}

