#include "stdafx.h"
#include "UiScore.h"

UiScore::UiScore(const std::string& fontId, const std::string& name)
	:TextGo(fontId, name)
{
	scoreformat = "Score : ";
	sortingLayer = SortingLayers::UI;
}

void UiScore::Init()
{
	SetOrigin(Origins::MC);
	SetScale(sf::Vector2f(2.f, 2.f));
}

void UiScore::Reset()
{
	TextGo::Reset();
	SetScore(0);
}

void UiScore::SetScore(int score)
{
	this->score = score;
	SetTextString(scoreformat + std::to_string(this->score));

}

void UiScore::AddScore(int score)
{
	SetScore(this->score + score);
}
