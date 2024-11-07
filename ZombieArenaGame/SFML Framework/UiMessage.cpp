#include "stdafx.h"
#include "UiMessage.h"

UiMessage::UiMessage(const std::string& fontId, const std::string& name)
	:TextGo(fontId, name)
{
	sortingLayer = SortingLayers::UI;
}

void UiMessage::Init()
{
	SetOrigin(Origins::MC);
	SetFillColor(sf::Color::White);
	SetTextString("GAME OVER!");
	SetScale(sf::Vector2f(2.f,2.f));
}

void UiMessage::Reset()
{
	TextGo::Reset();
	active = false;
}
