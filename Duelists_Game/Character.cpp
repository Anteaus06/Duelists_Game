#include <iostream>
#include "Character.h"
#include "CombatLog.h"




Character::Character(int MaxHealth, int AtkPower, int Heal, int MaxStamina, std::string Name) : 
	MaxHealth(MaxHealth), AtkPower(AtkPower), Heal(Heal), MaxStamina(MaxStamina), Name(Name)  
{
	InitStats();
}

void Character::UpdateHealth(int Amount)
{
	Health += Amount;
	if (Health <= 0) Health = 0;
	//std::cout << Name << " has " << Health << " remaining" << std::endl;
	DrawText((Name + " has " + std::to_string(Health) + " Health remaining.").c_str(), 190, 440, 20, GOLD);
}

void Character::UpdateStamina(bool Increase)
{
	Stamina = (Increase) ? Stamina += 1 : Stamina -= 1;
	if (Stamina >= MaxStamina)
	{
		Stamina = MaxStamina;
	}
	else if (Stamina <= 0)
	{
		Stamina = 0;
	}
}
void Character::InitStats()
{
	Health = MaxHealth;
	Stamina = MaxStamina;
}

void Character::GetHeal(int Heal)
{
	Heal = MaxHealth + 2;

}


void Character::AddTextureSprite(const char* TexturePath)
{
	SpriteC.TextureArray.push_back(LoadTexture(TexturePath));
}

void Character::SwapTextureSet(const std::vector<const char*>& NewTextures)
{
	std::vector<Texture2D> TempTextureArray;
	for (const char* TexturePath : NewTextures)
	{
		TempTextureArray.push_back(LoadTexture(TexturePath));
	}

	UnloadTextures();
	SpriteC.TextureArray = std::move(TempTextureArray);
	SpriteC.CurrentSprite == 0;
}

Texture2D Character::GetCurrentTexture()
{
	if (!SpriteC.TextureArray.empty() && SpriteC.CurrentSprite < SpriteC.TextureArray.size())
	{

	return SpriteC.TextureArray[SpriteC.CurrentSprite];
	}
	return{};
}

void Character::UnloadTextures()
{
	for (Texture2D& Texture : SpriteC.TextureArray)
	{
		if (Texture.id > 0)
		{

		UnloadTexture(Texture);
		}
	}

	SpriteC.TextureArray.clear();
}

Action Character::GetActionFromInput(int Input)
{
	switch (Input)
	{
	case 0:
		return ATTACK;
	case 1:
		UpdateStamina(false);
		return PARRY;
	case 2:
		UpdateStamina(true);
		return DEFEND;
	}
	return NONE;
}


