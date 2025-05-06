//duelingGame
#include <iostream>

#include "Player.h"
#include "Enemy.h"
#include "Character.h"
#include "Log.h"


void ProcessOutcome(Player& MainPlayer, Enemy& MainEnemy);

int main()
{
	Player MainPlayer(5, 2, 2, 2, "Adam");
	Enemy MainEnemy(1, 1, 1, 1, "Lady"); 
	int RoundNumber = 1;
	int Heal = 5;

	while (MainPlayer.GetIsAlive())
	{

		Log::Separator();
		Log::LogMessage(LOG_DEFAULT, "Round " + std::to_string(RoundNumber));
		Log::Separator();
		Log::NewLine();

		ProcessOutcome(MainPlayer, MainEnemy);

		
	
 { switch (RoundNumber)
		{ 
	case 1: 
	
		break;
	case 2:
		RoundNumber == 2;
		{
		Log::LogMessage(LOG_INFO, MainEnemy.GetName() + " Dropped apple, Adam ate it and healed");
		MainPlayer.UpdateHealth(Heal);
		}
		break;
		}

	}
		
		if (!MainEnemy.GetIsAlive())
		{
			
			RoundNumber += 1;
	
			if (RoundNumber > 5)
			{
				Log::LogMessage(LOG_INFO, MainEnemy.GetName() + "Man Rules ");
				break;
			}
			Log::LogMessage(LOG_DEFAULT, MainEnemy.GetName() + " has been defeated. A new girl appears " );
			Log::NewLine();


			MainEnemy.IncreaseDifficulty(RoundNumber);
			Log::LogMessage(LOG_WARNING, MainEnemy.GetName() + " looks mad that you beat her sister");
			Log::NewLine();
			MainPlayer.InitStats();
			Log::LogMessage(LOG_WARNING, MainEnemy.GetName() + " glares while, Adam Recovers his stamina ready for the next...");
		
			
		}
		
				
	}
	
	if (!MainPlayer.GetIsAlive())
	{
		Log::LogMessage (LOG_ERROR,  "Adam fell to sin " );
	}
		
	Log::LogMessage (LOG_ERROR, " Game Over  " );
	return 0;

	

}
	

void ProcessOutcome(Player& MainPlayer, Enemy& MainEnemy)
{

	// process round based on actions
	Action PlayerAction = MainPlayer.ChooseAction();
	Action EnemyAction = MainEnemy.ChooseAction();

	std::string PlayerActionStr = (PlayerAction == ATTACK) ? "Attack" : (PlayerAction == DEFEND) ? "Defend " : "Parry";
	std::string EnemyActionStr = (EnemyAction == ATTACK) ? "Attack" : (EnemyAction == DEFEND) ? "Defend " : "Parry";

	Log::NewLine();
	Log::LogMessage (LOG_INFO, "Adam " + PlayerActionStr + "s" );
	Log::LogMessage (LOG_WARNING, "She " + EnemyActionStr + "s" );
	Log::NewLine();

	switch (PlayerAction)
	{
		case ATTACK:
			switch (EnemyAction)
			{
			case ATTACK:
				Log::LogMessage(LOG_DEFAULT, "Clash! wow close one ");
				break;

			case PARRY:
				Log::LogMessage(LOG_ERROR, MainEnemy.GetName() + " Parries the attack! We got hurt ");
				MainPlayer.UpdateHealth(-(MainEnemy.GetAtkPower() * 2));
				break;

			case DEFEND:
			Log::LogMessage(LOG_DEFAULT, MainEnemy.GetName() + " Blocked attack, took less damage");
			MainEnemy.UpdateHealth(-(MainPlayer.GetAtkPower() / 2));
			break;
			}
		break;

	case PARRY:
		switch (EnemyAction)
		{
		case ATTACK:
			Log::LogMessage(LOG_INFO, "Adam Parries and Hurt her ");
			MainEnemy.UpdateHealth(-(MainPlayer.GetAtkPower() * 2));
			break;

		//	case PARRY:
		//	Log::LogMessage(LOG_DEFAULT, "Nothing Happened ");========== MY VERSION OF PARRY before RECOVER METHOD
		//	break;
			case PARRY:
				Log::LogMessage(LOG_DEFAULT, "Both lost stamina by Parrying");
			case DEFEND:
				break;
				Log::LogMessage(LOG_DEFAULT, "Adam loses Stamina while the Enemy recovers!");
			//MainPlayer.UpdateHealth(-(MainEnemy.GetAtkPower() * 2));
			break;
		
		}
		break;

	case DEFEND:
		switch (EnemyAction)
		{
		case ATTACK:
			Log::LogMessage(LOG_WARNING, "Adam defended against the attack! took little damage");
			MainPlayer.UpdateHealth(-(MainEnemy.GetAtkPower() + 1));
			break;

		//case PARRY:===================== My version of PARRY
		//	Log::LogMessage(LOG_INFO, "Adam blocked her Parry and it stung her, now she'll think twice ");
		//	MainEnemy.UpdateHealth(-(MainPlayer.GetAtkPower() * 2));
		//	break;
		case PARRY:
			Log::LogMessage(LOG_DEFAULT, "Enemy loses Stamina while Adam Recovers ");
			break;
		case DEFEND:
			Log::LogMessage(LOG_DEFAULT, "both are recovering ");
			break;
		}

		break;
	}

	Log::NewLine();
}
