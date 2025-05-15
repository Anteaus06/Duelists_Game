//duelingGame
#include <iostream>
#include "raylib.h"
#include "Player.h"
#include "Enemy.h"
#include "Character.h"
#include <map>
#include <functional>


enum GameState {WAITING_FOR_INPUT, PROCESSING, GAME_OVER, INFO};
void DrawOutcome(Player& MainPlayer, Enemy& MainEnemy, Action PlayerAction, GameState& State, GameState& StateBuffer, int& RoundNumber, int& Wait);
void ProcessOutcome(Player& MainPlayer, Enemy& MainEnemy, Action PlayerAction);
void DrawWaitForInput(Action& PlayerAction, GameState& State, Player& MainPlayer, GameState& StateBuffer);

struct CombatOutcome
{
	std::string OutcomeText;
	Color TextColor;
	std::function<void(Player&, Enemy&)> GameplayResult;
};

int main(void)
{


	const int screenWidth = 800;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Adams Temptation");

	Texture2D Background = LoadTexture("../SourceArt/Arena.png");

	SetTargetFPS(60);

	Player MainPlayer(5, 2, 2, 2, "Adam");
	Enemy MainEnemy(1, 1, 1, 1, "Lady");
	int RoundNumber = 1;
	int Heal = 1;
	bool GameOver = false;
	int Wait = 3;
	GameState State = WAITING_FOR_INPUT;
	GameState StateBuffer = WAITING_FOR_INPUT;

	Action PlayerAction = NONE;
	bool ActionChosen = false;

	//	DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Refreshes screen every loop
		if (State == INFO)
		{
			WaitTime(Wait);
			State = StateBuffer;
			Wait = 3;
		}

		BeginDrawing();      //~~~~ Begin frame rendering  ~~~~~~~//
	//	ClearBackground(BLACK); // THIS CODE WAS DELETED
		DrawTexture(Background, 0,0, WHITE);

		if (State == GAME_OVER)
		{

			DrawText("Game Over. Press ESC to exit. ", 190, 200, 20, LIGHTGRAY);
			EndDrawing();                   // Finalizes frame rendering
			continue;

		}

		DrawText(("Round " + std::to_string(RoundNumber)).c_str(), 10, 10, 20, LIGHTGRAY);

		if (State == WAITING_FOR_INPUT)
		{
			DrawWaitForInput(PlayerAction, State, MainPlayer, StateBuffer);

		}

		else if (State == PROCESSING)
		{
			DrawOutcome(MainPlayer, MainEnemy, PlayerAction, State, StateBuffer, RoundNumber, Wait);

		}
		EndDrawing();


		UnloadTexture(Background);
		CloseWindow();
		return 0;
	}
}

	void DrawWaitForInput(Action & PlayerAction, GameState & State, Player & MainPlayer, GameState & StateBuffer)
	{
		DrawText("Choose Action 1 attack 2 parry 3 defend", 10, 30, 20, GREEN);
		switch (GetKeyPressed())
		{
		case KEY_ONE:
			PlayerAction = ATTACK;
			State = PROCESSING;
			break;

		case KEY_TWO: 
			if (MainPlayer.GetStamina() > 0)
			{
				MainPlayer.UpdateStamina(false);
				PlayerAction = PARRY;
				State = PROCESSING;
				break;
			}
			else
			{
				State = INFO;
				StateBuffer = WAITING_FOR_INPUT;
				DrawText(" you are drained Defend to regain strength", 10, 300, 20, RED);
				break;
			}
		case KEY_THREE:
			PlayerAction = DEFEND;
			State = PROCESSING;
			MainPlayer.UpdateStamina(true);
			break;

		default:
			break;

		}
	}
	

void DrawOutcome(Player& MainPlayer, Enemy& MainEnemy, Action PlayerAction, GameState& State, GameState& StateBuffer, int& RoundNumber, int& Wait)
{
	ProcessOutcome(MainPlayer, MainEnemy, PlayerAction);
	StateBuffer = WAITING_FOR_INPUT;

	static bool executed = false;	

	if (RoundNumber == 3 && !executed)
	{
		DrawText((MainEnemy.GetName() + " Dropped apple, Adam ate it and healed").c_str(), 10, 320, 20, GREEN);
		MainPlayer.UpdateHealth(2);
		executed = true;
		StateBuffer = WAITING_FOR_INPUT;
	}

	if (!MainEnemy.GetIsAlive())
	{

		RoundNumber++; // += 1; WAS ORIGINAL SUPPOSDELY THE SAME OUTCOME

		if (RoundNumber > 5)
		{
			DrawText((MainEnemy.GetName() + " bows down! Man Rules ").c_str(), 190, 200, 20, GREEN);
			StateBuffer = GAME_OVER;
		}
		else
		{
			DrawText((MainEnemy.GetName() + " has been defeated. A new girl appears ").c_str(), 190, 200, 20, LIGHTGRAY);
			MainEnemy.IncreaseDifficulty(RoundNumber);
			DrawText((MainEnemy.GetName() + " looks mad that you beat her sister").c_str(), 190, 220, 20, LIGHTGRAY);
			MainPlayer.InitStats();
			DrawText((MainEnemy.GetName() + " glares while, Adam Recovers his stamina\n ready for the next...").c_str(), 190, 240, 20, YELLOW);
			StateBuffer = WAITING_FOR_INPUT;
			Wait = 5;

		}
	}

	if (!MainPlayer.GetIsAlive())
	{
		DrawText("Adam fell to sin ", 10, 350, 20, RED);
		StateBuffer = GAME_OVER;
	}
	State = INFO;
}



void ProcessOutcome(Player& MainPlayer, Enemy& MainEnemy, Action PlayerAction)
{
	// process round based on actions
	Action EnemyAction = MainEnemy.ChooseAction();
	//Lambda for mapping Action to String
	auto GetActionString = [](Action action)-> std::string
		{
			switch (action)
			{
			case ATTACK: return "Attack";
			case DEFEND: return "Defend";
			case PARRY: return "Parry";
			default: return "";
			}
		};

	std::string PlayerActionStr = GetActionString(PlayerAction);
	std::string EnemyActionStr = GetActionString(EnemyAction);

	// Display player and enemy actions
	DrawText(("Adam " + PlayerActionStr + "s").c_str(), 10, 60, 20, LIGHTGRAY);
	DrawText(("She " + EnemyActionStr + "s").c_str(), 10, 80, 20, LIGHTGRAY);

	static std::map<std::pair<Action, Action>, CombatOutcome> OutcomeMap =

	{

		{ { ATTACK, ATTACK }, { "Clash! wow close one ", DARKGRAY, [](Player& player, Enemy& enemy) {} } },
		{ { ATTACK, PARRY }, {MainEnemy.GetName() + " Parries the attack! We got hurt ", RED, [](Player& player, Enemy& enemy) {player.UpdateHealth(-(enemy.GetAtkPower() * 2)); }}},
		{ { ATTACK, DEFEND }, {MainEnemy.GetName() + " Blocked attack, took less damage", LIGHTGRAY,[](Player& player, Enemy& enemy) {enemy.UpdateHealth(-(player.GetAtkPower() / 2)); } } },
		{ { PARRY, ATTACK }, {"Adam Parries and Hurt her ", LIGHTGRAY,[](Player& player, Enemy& enemy) {enemy.UpdateHealth(-(player.GetAtkPower() * 2)); }} },
		{ { PARRY, PARRY }, {"Both lost stamina by Parrying", DARKGRAY,[](Player& player, Enemy& enemy) {} }},
		{ { PARRY, DEFEND }, {"Adam loses Stamina while the Enemy recovers!", DARKGRAY,[](Player& player, Enemy& enemy) {} }},
		{ { DEFEND, ATTACK }, {"Adam defended against the attack! took little damage", DARKGRAY,[](Player& player, Enemy& enemy) {player.UpdateHealth(-(enemy.GetAtkPower() + 1)); }} },			{ { DEFEND, PARRY }, {"Enemy loses Stamina while Adam Recovers ",DARKGRAY,[](Player& player, Enemy& enemy) {} }},
		{ { DEFEND, PARRY }, {"she parried! waste of energy ", DARKGRAY,[](Player& player, Enemy& enemy) {}} },
		{ { DEFEND, DEFEND }, {"both are recovering ", DARKGRAY,[](Player& player, Enemy& enemy) {}} }
	};

	CombatOutcome Outcome = OutcomeMap[{PlayerAction, EnemyAction}];
	//DISPLAY OUTCOME TEXT
	DrawText(Outcome.OutcomeText.c_str(), 10, 120, 20, Outcome.TextColor);
	Outcome.GameplayResult(MainPlayer, MainEnemy);
}