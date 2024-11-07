#include "stdafx.h"
#include "UibulletCount.h"

UibulletCount::UibulletCount(const std::string& fontId, Player* player,const std::string& name)
	:TextGo(fontId, name),player(player)
{
	countformat = "Bullet : ";
	sortingLayer = SortingLayers::UI;
}

void UibulletCount::Init()
{
	SetOrigin(Origins::MC);
	SetScale(sf::Vector2f(2.f, 2.f));
}

void UibulletCount::Reset()
{
	TextGo::Reset();
	SetCount(10);

}

void UibulletCount::Update()
{
	if (player)
	{
		SetCount(player->GetBulletCount()); 
	}
}

void UibulletCount::SetCount(int Count)
{
	std::string bulletCountText = countformat + std::to_string(Count);
	SetString(bulletCountText);
}


