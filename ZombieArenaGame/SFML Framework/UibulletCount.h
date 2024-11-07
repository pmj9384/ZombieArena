#pragma once
#include "TextGo.h"
#include "Player.h"


class UibulletCount : public TextGo
{
protected:
	Player* player;
	std::string countformat;
	
public:
	UibulletCount(const std::string& fontId, Player* player,const std::string& name = "");
	~UibulletCount() = default;

	void Init() override;
	void Reset() override;
	void Update();
	void SetCount(int Count);
};



