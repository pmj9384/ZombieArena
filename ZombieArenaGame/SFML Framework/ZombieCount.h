#pragma once
#include "TextGo.h"
class ZombieCount : public TextGo
{
protected:
	int count;
	std::string Zombieformat;

public:
	ZombieCount(const std::string& fontId, const std::string& name = "");
	~ZombieCount() = default;

	void Init() override;
	void Reset() override;
	void SetCount(int count);
	void AddCount(int count);
};

