#include "stdafx.h"
#include "UiWave.h"

UiWave::UiWave(const std::string& fontId, const std::string& name)
	:TextGo(fontId, name)
{
	waveformat = "wave: ";
	sortingLayer = SortingLayers::UI;

}

void UiWave::Init()
{
	SetOrigin(Origins::MC);
	SetScale(sf::Vector2f(2.f, 2.f));
}

void UiWave::Reset()
{
	TextGo::Reset();
	SetWave(0);
}

void UiWave::SetWave(int wave)
{
	this->wave = wave;
	SetTextString(waveformat + std::to_string(this->wave));
}

void UiWave::AddWave(int wave)
{
	this->wave += wave;
	SetWave(this->wave + wave);
}
