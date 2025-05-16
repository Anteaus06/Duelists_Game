#include <iostream>
#include "raylib.h"
#include "CombatLog.h"
#include "Player.h"
#include "Enemy.h"
#include <map>
#include <functional>


enum GameState { WAITING_FOR_INPUT, PROCESSING, GAME_OVER};
void DrawOutcome(Player& MainPlayer, Enemy& MainEnemy, Action PlayerAction, GameState& State, int& RoundNumber);
void ProcessOutcome(Player& Mainplayer, Enemy& MainEnemy, Action PlayerAction);
void DrawWaitForInput(Action& PlayerAction, GameState& State, Player& MainPlayer) ;

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
	//Texture2D AdamText = LoadTexture("../SourceArt/Characters/Knight/Knight_IdleBlinking_Sprite.png");

	SetTargetFPS(60);

	Player MainPlayer(5, 2, 2, 2, "Adam");
	Enemy MainEnemy(1, 1, 0, 1, "This Lady");
	int RoundNumber = 1;
	int Heal = 1;
	bool GameOver = false;
	int Wait = 3;
	GameState State = WAITING_FOR_INPUT;
	

	Action PlayerAction = NONE;



	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		

		BeginDrawing();      //~~~~ Begin frame rendering  ~~~~~~~//
		ClearBackground(BLACK); 
		DrawTexture(Background, 0,0, WHITE);
		//DrawTexture(AdamText, 75, 210, WHITE);

		CombatLog::DrawMessages();

		if (State == GAME_OVER)
		{

			DrawText("Game Over. Press ESC to exit. ", 160, 200, 30, RAYWHITE);
			EndDrawing();                   // Finalizes frame rendering
			continue;

		}

		DrawText(("Round " + std::to_string(RoundNumber)).c_str(), 700, 400, 22, LIGHTGRAY);

		if (State == WAITING_FOR_INPUT)
		{
			DrawWaitForInput(PlayerAction, State, MainPlayer);

		}

		else if (State == PROCESSING)
		{
			DrawOutcome(MainPlayer, MainEnemy, PlayerAction, State, RoundNumber);

		}
		EndDrawing();


	}
		UnloadTexture(Background);
		CloseWindow();
		return 0;
}

	void DrawWaitForInput(Action& PlayerAction, GameState& State, Player& MainPlayer)
	{
		DrawText("Choose Action (1 Tempt, 2 Rebuke, 3 Repent)", 10, 400, 20, BLACK);
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
				
				CombatLog::AddMessage("Adam is too tired to rebuke, he needs to repent", RED, 1.0f);
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
	

void DrawOutcome(Player& MainPlayer, Enemy& MainEnemy, Action PlayerAction, GameState& State, int& RoundNumber)
{
	ProcessOutcome(MainPlayer, MainEnemy, PlayerAction);

	static bool executed = false;	

	if (RoundNumber == 3 && !executed)
	{
		DrawText((MainEnemy.GetName() + " Dropped apple, Adam ate it and healed").c_str(), 100, 560, 25, LIME);
		MainPlayer.UpdateHealth(2);
		executed = true;
		State = WAITING_FOR_INPUT;
	}

	if (!MainEnemy.GetIsAlive())
	{

		RoundNumber++; 

		if (RoundNumber > 5)
		{

			CombatLog::AddMessage((MainEnemy.GetName() + " bows down! Man Rules ").c_str(), GREEN, 1.5f);
			State = GAME_OVER;
		}
		else
		{
			CombatLog::AddMessage((MainEnemy.GetName() + " fell to sin. A new girl appears ").c_str(), LIGHTGRAY, 1.5f);
			MainEnemy.IncreaseDifficulty(RoundNumber);
			CombatLog::AddMessage((MainEnemy.GetName() + " looks mad.").c_str(), LIGHTGRAY, 1.5f);
			MainPlayer.InitStats();
			CombatLog::AddMessage("Adam recovers energy..", YELLOW, 1.5f);

		}
	}

	if (!MainPlayer.GetIsAlive())
	{
		CombatLog::AddMessage("Adam fell to sin ", RED, 15.5f);
		State = GAME_OVER;
	}
	State = WAITING_FOR_INPUT;
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
			case ATTACK: return "Tempt";
			case PARRY: return "Rebuke";
			case DEFEND: return "Repent";
			default: return "";
			}
		};

	std::string PlayerActionStr = GetActionString(PlayerAction);
	std::string EnemyActionStr = GetActionString(EnemyAction);

	// Display player and enemy actions
	CombatLog::AddMessage(("Adam " + PlayerActionStr + "s").c_str(), LIGHTGRAY, 1.5f);
	CombatLog::AddMessage(("She " + EnemyActionStr + "s").c_str(), LIGHTGRAY, 1.5f);

	static std::map<std::pair<Action, Action>, CombatOutcome> OutcomeMap = 

	{

		{ { ATTACK, ATTACK }, { "Both failed to tempt! ", ORANGE, [](Player& player, Enemy& enemy) {} } },
		{ { ATTACK, PARRY }, {MainEnemy.GetName() + " Rebuke hurt Adam.", RED, [](Player& player, Enemy& enemy) {player.UpdateHealth(-(enemy.GetAtkPower() * 2)); }}},
		{ { ATTACK, DEFEND }, {MainEnemy.GetName() + " repent interupted, hurt her.", LIGHTGRAY,[](Player& player, Enemy& enemy) {enemy.UpdateHealth(-(player.GetAtkPower() / 2)); } } },
		{ { PARRY, ATTACK }, {"Adam rebuke hurt her. ", LIGHTGRAY,[](Player& player, Enemy& enemy) {enemy.UpdateHealth(-(player.GetAtkPower() * 2)); }} },
		{ { PARRY, PARRY }, {"Both spent energy rebuking.", GOLD,[](Player& player, Enemy& enemy) {} }},
		{ { PARRY, DEFEND }, {"Adam spent energy, while she repents!", GOLD,[](Player& player, Enemy& enemy) {} }},
		{ { DEFEND, ATTACK }, {"Adam's repent was interupted and it hurt.", YELLOW,[](Player& player, Enemy& enemy) {player.UpdateHealth(-(enemy.GetAtkPower() + 1)); }} },
		{ { DEFEND, PARRY }, {"She wasted energy! Adam repents! ", RAYWHITE,[](Player& player, Enemy& enemy) {}} },
		{ { DEFEND, DEFEND }, {"Both are repenting ", RAYWHITE,[](Player& player, Enemy& enemy) {}} }
	};

	CombatOutcome Outcome = OutcomeMap[{PlayerAction, EnemyAction}];
	//DISPLAY OUTCOME TEXT
	CombatLog::AddMessage(Outcome.OutcomeText.c_str(), Outcome.TextColor, 1.5f);
	Outcome.GameplayResult(MainPlayer, MainEnemy);
}