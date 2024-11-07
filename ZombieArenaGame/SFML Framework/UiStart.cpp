#include "stdafx.h"
#include "UiStart.h"

UiStart::UiStart(const std::string& fontId, const std::string& name)
	:TextGo(fontId, name)
{
	sortingLayer = SortingLayers::UI;
}

void UiStart::Init()
{
	SetOrigin(Origins::MC);
	SetFillColor(sf::Color::White);
	SetTextString("PRESS ENTER TO CONTINUE");
	SetScale(sf::Vector2f(2.f, 2.f));
}

void UiStart::Reset()
{
	TextGo::Reset();
}

