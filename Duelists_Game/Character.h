#pragma once
#include <string>
#include <vector>
#include "raylib.h"


enum Action
{
	ATTACK,
	PARRY,
	DEFEND,
	NONE
};

struct SpriteComponent
{
	std::vector<Texture2D> TextureArray;
	int CurrentSprite = 0;

};

class Character
{

public:
	Character(int MaxHealth, int AtkPower, int Heal, int MaxStamina, std::string Name);

	SpriteComponent SpriteC;
	int GetHealth() const { return Health; } // typed all on 1 line to show not editing
	std::string GetName() const { return Name; }
	bool GetIsAlive() const { return Health > 0; }
	int GetAtkPower() const { return AtkPower; }
	int GetStamina() const { return Stamina; }

	void GetHeal(int Heal);
	void AddTextureSprite(const char *TexturePath);
	void SwapTextureSet(const std::vector<const char*>& NewTextures);
	Texture2D GetCurrentTexture();
	void UnloadTextures();
	void UpdateHealth(int Amount);
	void UpdateStamina(bool Increase);
	
	virtual Action ChooseAction() = 0;
	void InitStats();
	Action GetActionFromInput(int Input);

protected:
	std::string Name;
	int MaxHealth;
	int Health;
	int AtkPower;
	int Heal;
	int MaxStamina;
	int Stamina;
};