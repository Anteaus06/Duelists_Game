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
	SpriteC.CurrentSprite = Input+1;
	return GetActionFromInput(Input);
}
void Enemy::IncreaseDifficulty(int RoundNumber)
{
	/*static std::vector<const char*> GoblinTexture =
	{

	"../SourceArt/Characters/Goblin/Goblin_IdleBlinking_Sprite.png",
	"../SourceArt/Characters/Goblin/Goblin_Attacking_Sprite.png",
	"../SourceArt/Characters/Goblin/Goblin_Defend_Sprite.png",
	"../SourceArt/Characters/Goblin/Goblin_Parry_Sprite.png",

	};*/
	static std::vector<const char*> SkeletonTexture =
	{

	"../SourceArt/Characters/Skeleton/Skeleton_Idle_Sprite.png",
	"../SourceArt/Characters/Skeleton/Skeleton_Attacking_Sprite.png",
	"../SourceArt/Characters/Skeleton/Skeleton_Defend_Sprite.png",
	"../SourceArt/Characters/Skeleton/Skeleton_Parry_Sprite.png",

	};
	static std::vector<const char*> CyclopTexture =
	{

	"../SourceArt/Characters/Cyclop/Cyclop_Idle_Sprite.png",
	"../SourceArt/Characters/Cyclop/Cyclop_Attacking_Sprite.png",
	"../SourceArt/Characters/Cyclop/Cyclop_Defend_Sprite.png",
	"../SourceArt/Characters/Cyclop/Cyclop_Parry_Sprite.png",

	};
	static std::vector<const char*> OgreTexture =
	{

	"../SourceArt/Characters/Ogre/Ogre_IdleBlinking_Sprite.png",
	"../SourceArt/Characters/Ogre/Ogre_Attacking_Sprite.png",
	"../SourceArt/Characters/Ogre/Ogre_Defend_Sprite.png",
	"../SourceArt/Characters/Ogre/Ogre_Parry_Sprite.png",

	};
	switch (RoundNumber)
	{
	case 1:
		return;

	case 2:
		Health += RoundNumber;
		Name = "Maidservant";
		SwapTextureSet(OgreTexture);
		return;
	case 3:
		Health += RoundNumber;
		//AtkPower += RoundNumber;
		Name = "Concubine";
		SwapTextureSet(SkeletonTexture);
		return;
	case 4:
		Health += RoundNumber;
		AtkPower += RoundNumber;
		Name = "Eve";
		SwapTextureSet(CyclopTexture);
		return;


	}
}

