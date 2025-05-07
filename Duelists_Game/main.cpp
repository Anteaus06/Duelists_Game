/*******************************************************************************************
*
* raylib[core] example - Basic window
*
*Example complexity rating : [★☆☆☆] 1 / 4
*
*Welcome to raylib!
*
*To test examples, just press F6 and execute 'raylib_compile_execute' script
* Note that compiled executable is placed in the same folder as.c file
*
*To test the examples on Web, press F6 and execute 'raylib_compile_execute_web' script
* Web version of the program is generated in the same folder as.c file
*
*You can find all basic examples on C : \raylib\raylib\examples folder or
*raylib official webpage : www.raylib.com
*
*Enjoy using raylib. : )
*
* Example originally created with raylib 1.0, last time updated with raylib 1.0
*
*Example licensed under an unmodified zlib / libpng license, which is an OSI - certified,
* BSD - like license that allows static linking with closed source software
*
*Copyright(c) 2013 - 2025 Ramon Santamaria(@raysan5)
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}







/*
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
	int Heal = 1;

	while (MainPlayer.GetIsAlive())
	{

		Log::Separator();
		Log::LogMessage(LOG_DEFAULT, "Round " + std::to_string(RoundNumber));
		Log::Separator();
		Log::NewLine();

		ProcessOutcome(MainPlayer, MainEnemy);

		
	
		static bool executed = false;

		if (RoundNumber == 3 && !executed)
		{
			Log::LogMessage(LOG_INFO, MainEnemy.GetName() + " Dropped apple, Adam ate it and healed");
			MainPlayer.UpdateHealth(Heal);
			executed = true;
		}
		
		if (!MainEnemy.GetIsAlive())
		{
			
			RoundNumber += 1;
	
			if (RoundNumber > 5)
			{
				Log::LogMessage(LOG_INFO, MainEnemy.GetName() + " bows down! Man Rules ");
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
*/