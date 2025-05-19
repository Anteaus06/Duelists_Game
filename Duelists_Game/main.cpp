#include <iostream>
#include "raylib.h"
#include "CombatLog.h"
#include "Player.h"
#include "Enemy.h"
#include <map>
#include <functional>

float SHORT_MESSAGE_DURATION = 3.0f;
float LONG_MESSAGE_DURATION = 6.0f;
bool CAN_INPUT = true;
float INPUT_COOLDOWN = 2.5f;
float TIME_SINCE_LAST_INPUT = 0.0f;

enum GameState { WAITING_FOR_INPUT, PROCESSING, GAME_OVER};
void DrawOutcome(Player& MainPlayer, Enemy& MainEnemy, Action PlayerAction, GameState& State, int& RoundNumber);
void ProcessOutcome(Player& Mainplayer, Enemy& MainEnemy, Action PlayerAction);
void DrawWaitForInput(Action& PlayerAction, GameState& State, Player& MainPlayer) ;

struct CombatOutcome
{
	std::string OutcomeText;
	Color TextColor;
	std::function<void(Player&, Enemy&)> GameplayResult; // insert before closing semicolon [](Player&, Enemy&) {};
};

int main(void)
{ // RAYLIB INIT
	const int screenWidth = 800;
	const int screenHeight = 600;
	InitWindow(screenWidth, screenHeight, "Adams Temptation");
	// Game init
	Texture2D Background = LoadTexture("../SourceArt/Arena.png");
	int FramesCounter = 0;
	int FramesSpeed = 8;
	int CurrentFrame = 0;
	SetTargetFPS(60);
	
	// player sprite testing
	Player MainPlayer(5, 2, 2, 2, "Adam");
	Vector2 PlayerPosition = { 290.0f, 150.0f };
	// player init
	MainPlayer.AddTextureSprite("../SourceArt/Characters/Knight/Knight_IdleBlinking_Sprite.png");
	MainPlayer.AddTextureSprite("../SourceArt/Characters/Knight/Knight_Attacking_Sprite.png");
	MainPlayer.AddTextureSprite("../SourceArt/Characters/Knight/Knight_Defend_Sprite.png");
	MainPlayer.AddTextureSprite("../SourceArt/Characters/Knight/Knight_Parry_Sprite.png");
	Rectangle PlayerRect = { 0.0f, 0.0f, static_cast<float>(MainPlayer.SpriteC.TextureArray[MainPlayer.SpriteC.CurrentSprite].width / 4), static_cast<float>(MainPlayer.SpriteC.TextureArray[MainPlayer.SpriteC.CurrentSprite].height / 3)};

	// enemy init
	Enemy MainEnemy(1, 1, 0, 1, "This Lady");
	Vector2 EnemyPosition = { 375.0f, 160.0f };
	MainEnemy.AddTextureSprite("../SourceArt/Characters/Goblin/Goblin_IdleBlinking_Sprite.png");
	MainEnemy.AddTextureSprite("../SourceArt/Characters/Goblin/Goblin_Attacking_Sprite.png");
	MainEnemy.AddTextureSprite("../SourceArt/Characters/Goblin/Goblin_Defend_Sprite.png");
	MainEnemy.AddTextureSprite("../SourceArt/Characters/Goblin/Goblin_Parry_Sprite.png");
	Rectangle EnemyRect = { 0.0f, 0.0f, static_cast<float>(MainEnemy.SpriteC.TextureArray[MainEnemy.SpriteC.CurrentSprite].width / 4), static_cast<float>(MainEnemy.SpriteC.TextureArray[MainEnemy.SpriteC.CurrentSprite].height / 3)};
	EnemyRect.width = -EnemyRect.width;
	
	int RoundNumber = 1;
	int Heal = 1;
	bool GameOver = false;
	
	GameState State = WAITING_FOR_INPUT;
	Action PlayerAction = NONE;


	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		TIME_SINCE_LAST_INPUT += GetFrameTime();
		// player test
		FramesCounter++;

		if (FramesCounter >= (60/ FramesSpeed))
		{
			FramesCounter = 0;
			CurrentFrame++;
			if (CurrentFrame > 3)
			{
				CurrentFrame = 0;
			}
			PlayerRect.x = static_cast<float>(CurrentFrame) * MainPlayer.GetCurrentTexture().width / 4;
			PlayerRect.y = static_cast<float>(CurrentFrame) * MainPlayer.GetCurrentTexture().height / 3;
		
			EnemyRect.x = static_cast<float>(CurrentFrame) * MainEnemy.GetCurrentTexture().width / 4;
			EnemyRect.y = static_cast<float>(CurrentFrame) * MainEnemy.GetCurrentTexture().height / 3;
		}

		BeginDrawing();      //~~~~ Begin frame rendering  ~~~~~~~//
		ClearBackground(BLACK); 
		DrawTexture(Background, 0,0, WHITE);
		DrawTextureRec(MainPlayer.GetCurrentTexture(), PlayerRect, PlayerPosition, WHITE);
		DrawTextureRec(MainEnemy.GetCurrentTexture(), EnemyRect, EnemyPosition, WHITE);

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
		if (CAN_INPUT) {
			MainPlayer.SpriteC.CurrentSprite = 0;
			MainEnemy.SpriteC.CurrentSprite = 0;
		}
		EndDrawing();


	}
		UnloadTexture(Background);
		MainPlayer.UnloadTextures();
		MainEnemy.UnloadTextures();
		CloseWindow();
		return 0;
}

	void DrawWaitForInput(Action& PlayerAction, GameState& State, Player& MainPlayer)
	{

		if (State != WAITING_FOR_INPUT) return;

			DrawText("Choose Action (1 Tempt, 2 Rebuke, 3 Repent)", 10, 20, 20, GOLD);
			if (CAN_INPUT)
			{
				switch (GetKeyPressed())
				{
				case KEY_ONE:
					PlayerAction = ATTACK;
					State = PROCESSING;
					CAN_INPUT = false;
					TIME_SINCE_LAST_INPUT = 0.0f;
					MainPlayer.SpriteC.CurrentSprite = 1;
					break;

				case KEY_TWO:
					if (MainPlayer.GetStamina() > 0)
					{
						MainPlayer.UpdateStamina(false);
						PlayerAction = PARRY;
						State = PROCESSING;
						CAN_INPUT = false;
						TIME_SINCE_LAST_INPUT = 0.0f;
						MainPlayer.SpriteC.CurrentSprite = 2;
						break;
					}
					else
					{
						CombatLog::AddMessage("Adam is too tired to rebuke, he needs to repent", RED, 1.0f);
						CAN_INPUT = false;
						TIME_SINCE_LAST_INPUT = 0.0f;
						break;
					}
				case KEY_THREE:
					PlayerAction = DEFEND;
					State = PROCESSING;
					MainPlayer.UpdateStamina(true);
					CAN_INPUT = false;
					TIME_SINCE_LAST_INPUT = 0.0f;
					MainPlayer.SpriteC.CurrentSprite = 3;
					break;

				default:
					break;
				}
			}
			if (TIME_SINCE_LAST_INPUT > INPUT_COOLDOWN)
			{
				CAN_INPUT = true;
	
			}
	}
	

void DrawOutcome(Player& MainPlayer, Enemy& MainEnemy, Action PlayerAction, GameState& State, int& RoundNumber)
{
	ProcessOutcome(MainPlayer, MainEnemy, PlayerAction);
	State = WAITING_FOR_INPUT;
	static bool executed = false;	// my code for apple
	
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

			CombatLog::AddMessage((MainEnemy.GetName() + " bows down! Man Rules ").c_str(), GREEN, SHORT_MESSAGE_DURATION);
			State = GAME_OVER;
		}
		else
		{
			CombatLog::AddMessage((MainEnemy.GetName() + " fell to sin. A new girl appears ").c_str(), LIGHTGRAY, SHORT_MESSAGE_DURATION);
			MainEnemy.IncreaseDifficulty(RoundNumber);
			CombatLog::AddMessage((MainEnemy.GetName() + " looks mad.").c_str(), LIGHTGRAY, SHORT_MESSAGE_DURATION);
			MainPlayer.InitStats();
			CombatLog::AddMessage("Adam recovers energy..", YELLOW, SHORT_MESSAGE_DURATION);

		}
	
	}

	if (!MainPlayer.GetIsAlive())
	{
		CombatLog::AddMessage("Adam fell to sin ", RED, 15.5f);
		State = GAME_OVER;
	}
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
	CombatLog::AddMessage(("Adam " + PlayerActionStr + "s").c_str(), LIGHTGRAY, SHORT_MESSAGE_DURATION);
	CombatLog::AddMessage(("She " + EnemyActionStr + "s").c_str(), LIGHTGRAY, SHORT_MESSAGE_DURATION);

	static std::map<std::pair<Action, Action>, CombatOutcome> OutcomeMap = 

	{

		{ { ATTACK, ATTACK }, { "Both failed to tempt! ", ORANGE, [](Player& player, Enemy& enemy) 
		{
			
		} } },
		{ { ATTACK, PARRY }, {MainEnemy.GetName() + " Rebuke hurt Adam.", RED, [](Player& player, Enemy& enemy) 
		{
			player.UpdateHealth(-(enemy.GetAtkPower() * 2)); 
		
		
		}}},
		{ { ATTACK, DEFEND }, {MainEnemy.GetName() + " repent interrupted, hurt her.", LIGHTGRAY,[](Player& player, Enemy& enemy) 
		{
			enemy.UpdateHealth(-(player.GetAtkPower() / 2)); 
		
			
		
		} } },
		{ { PARRY, ATTACK }, {"Adam rebuke hurt her. ", LIGHTGRAY,[](Player& player, Enemy& enemy) 
		{
			enemy.UpdateHealth(-(player.GetAtkPower() * 2)); 
			
		
		
		}} },
		{ { PARRY, PARRY }, {"Both spent energy rebuking.", GOLD,[](Player& player, Enemy& enemy) 
		{
		
		

		} }},
		{ { PARRY, DEFEND }, {"Adam spent energy, while she repents!", GOLD,[](Player& player, Enemy& enemy) 
		{
			
			

		} }},
		{ { DEFEND, ATTACK }, {"Adam's repent was interrupted and it hurt.", YELLOW,[](Player& player, Enemy& enemy)
		{
			player.UpdateHealth(-(enemy.GetAtkPower() + 1)); 
			
			
		}} },
		{ { DEFEND, PARRY }, {"She wasted energy! Adam repents! ", RAYWHITE,[](Player& player, Enemy& enemy) 
		{
		
		}} },
		{ { DEFEND, DEFEND }, {"Both are repenting ", RAYWHITE,[](Player& player, Enemy& enemy) 
		{
			
		}} }
	};

	CombatOutcome Outcome = OutcomeMap[{PlayerAction, EnemyAction}];
	//DISPLAY OUTCOME TEXT
	CombatLog::AddMessage(Outcome.OutcomeText.c_str(), Outcome.TextColor, SHORT_MESSAGE_DURATION);
	Outcome.GameplayResult(MainPlayer, MainEnemy);
}