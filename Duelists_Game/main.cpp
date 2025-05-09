

//duelingGame
#include "raylib.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
//#include "Character.h"


void ProcessOutcome(Player& MainPlayer, Enemy& MainEnemy);

int main(void)
{


	const int screenWidth = 800;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Adams Temptation");
	SetTargetFPS(60);

	Player MainPlayer(5, 2, 2, 2, "Adam");
	Enemy MainEnemy(1, 1, 1, 1, "Lady");
	int RoundNumber = 1;
	int Heal = 1;
	bool GameOver = false;

	//	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Refreshes screen every loop

		BeginDrawing();      //~~~~ Begin frame rendering  ~~~~~~~//
		ClearBackground(BLACK); // CLEAR THE BACKGROUND

		if (GameOver)
		{

			DrawText("Game Over. Press ESC to exit. ", 190, 200, 20, LIGHTGRAY);
			EndDrawing();                   // Finalizes frame rendering
			continue;

		}

		DrawText(("Round " + std::to_string(RoundNumber)).c_str(), 10, 15, 20, LIGHTGRAY);
		ProcessOutcome(MainPlayer, MainEnemy);

		/*----------------------------- MY CODE FOR DROPING AN APPLE ------------------------------------
			static bool executed = false;

		if (RoundNumber == 3 && !executed)
		//	{
				DrawText((MainEnemy.GetName() + " Dropped apple, Adam ate it and healed").c_str(), 190, 200, 20, LIGHTGRAY);
				MainPlayer.UpdateHealth(Heal);
				executed = true;
		//	}
		*/
		if (!MainEnemy.GetIsAlive())
		{

			RoundNumber++; // += 1; WAS ORIGINAL SUPPOSDELY THE SAME OUTCOME

			if (RoundNumber > 5)
			{
				DrawText((MainEnemy.GetName() + " bows down! Man Rules ").c_str(), 190, 200, 20, GREEN);
				GameOver = true;
			}

			DrawText((MainEnemy.GetName() + " has been defeated. A new girl appears ").c_str(), 190, 200, 20, LIGHTGRAY);
			MainEnemy.IncreaseDifficulty(RoundNumber);
			DrawText((MainEnemy.GetName() + " looks mad that you beat her sister").c_str(), 190, 200, 20, LIGHTGRAY);
			MainPlayer.InitStats();
			DrawText((MainEnemy.GetName() + " glares while, Adam Recovers his stamina ready for the next...").c_str(), 190, 200, 20, GREEN);

		}

		if (!MainPlayer.GetIsAlive())
		{
			DrawText("Adam fell to sin ", 190, 200, 20, RED);
			GameOver = true;
		}
		EndDrawing();

	}

	CloseWindow();
	return 0;
}

	void ProcessOutcome(Player & MainPlayer, Enemy & MainEnemy)
	{

		// process round based on actions
		Action PlayerAction = MainPlayer.ChooseAction();
		Action EnemyAction = MainEnemy.ChooseAction();

		std::string PlayerActionStr = (PlayerAction == ATTACK) ? "Attack" : (PlayerAction == DEFEND) ? "Defend " : "Parry";
		std::string EnemyActionStr = (EnemyAction == ATTACK) ? "Attack" : (EnemyAction == DEFEND) ? "Defend " : "Parry";

		// Display player and enemy actions
		DrawText(("Adam " + PlayerActionStr + "s").c_str(), 10, 40, 20, LIGHTGRAY);
		DrawText(("She " + EnemyActionStr + "s").c_str(), 10, 60, 20, LIGHTGRAY);

		switch (PlayerAction)
		{
		case ATTACK:
			switch (EnemyAction)
			{
			case ATTACK:
				DrawText("Clash! wow close one ", 10, 120, 20, DARKGRAY);
				break;

			case PARRY:
				DrawText((MainEnemy.GetName() + " Parries the attack! We got hurt ").c_str(), 10, 120, 20, RED);
				MainPlayer.UpdateHealth(-(MainEnemy.GetAtkPower() * 2));
				break;

			case DEFEND:
				DrawText((MainEnemy.GetName() + " Blocked attack, took less damage").c_str(), 10, 120, 20, LIGHTGRAY);
				MainEnemy.UpdateHealth(-(MainPlayer.GetAtkPower() / 2));
				break;
			}
			break;

		case PARRY:

			switch (EnemyAction)
			{
			case ATTACK:
				DrawText("Adam Parries and Hurt her ", 190, 200, 20, LIGHTGRAY);
				MainEnemy.UpdateHealth(-(MainPlayer.GetAtkPower() * 2));
				break;

			case PARRY:
				DrawText("Both lost stamina by Parrying", 190, 200, 20, LIGHTGRAY);
			case DEFEND:
				break;
				DrawText("Adam loses Stamina while the Enemy recovers!", 190, 200, 20, LIGHTGRAY);
				//MainPlayer.UpdateHealth(-(MainEnemy.GetAtkPower() * 2));
				break;

			}
			break;

		case DEFEND:
			switch (EnemyAction)
			{
			case ATTACK:
				DrawText("Adam defended against the attack! took little damage", 190, 200, 20, LIGHTGRAY);
				MainPlayer.UpdateHealth(-(MainEnemy.GetAtkPower() + 1));
				break;

			case PARRY:
				DrawText("Enemy loses Stamina while Adam Recovers ", 190, 200, 20, LIGHTGRAY);
				break;
			case DEFEND:
				DrawText("both are recovering ", 190, 200, 20, LIGHTGRAY);
				break;
			}

			break;

		}
	}

	

	


/*
int main()
{

	while (MainPlayer.GetIsAlive())
	{


		
	
		
				
	}
	
		
	DrawText (" Game Over  ", 190, 200, 20, LIGHTGRAY);
	return 0;

	

}*/

		//	case PARRY:
		//	DrawText(LOG_DEFAULT, "Nothing Happened ");========== MY VERSION OF PARRY before RECOVER METHOD
		//	break;

		//case PARRY:===================== My version of PARRY
		//	DrawText(LOG_INFO, "Adam blocked her Parry and it stung her, now she'll think twice ");
		//	MainEnemy.UpdateHealth(-(MainPlayer.GetAtkPower() * 2));
		//	break;