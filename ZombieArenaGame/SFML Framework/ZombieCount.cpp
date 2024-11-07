#include "stdafx.h"
#include "ZombieCount.h"

ZombieCount::ZombieCount(const std::string& fontId, const std::string& name)
	:TextGo(fontId, name)
{
	Zombieformat = "Zombies : ";
	sortingLayer = SortingLayers::UI;
}

void ZombieCount::Init()
{		
	SetOrigin(Origins::MC);
	SetScale(sf::Vector2f(2.f, 2.f));
}

void ZombieCount::Reset()
{
	TextGo::Reset();
	SetCount(0);
}

void ZombieCount::SetCount(int count)
{
	this->count = count;
	SetTextString(Zombieformat + std::to_string(this->count));

}

void ZombieCount::AddCount(int count)
{
	SetCount(this->count + count);
}
