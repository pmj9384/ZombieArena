#pragma once

class HitBox
{
public:
	HitBox();


	sf::RectangleShape rect;
	sf::RectangleShape& GetRect() { return rect; }
	void UpdateTr(const sf::Transformable& tr, const sf::FloatRect& localBound);
	void Draw(sf::RenderWindow& window);

};