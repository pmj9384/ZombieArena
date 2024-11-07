#pragma once
#include "TextGo.h"
class UiScore :
	public TextGo
{
protected:
	int score;
	std::string scoreformat;

public:
	UiScore(const std::string& fontId, const std::string& name = "");
	~UiScore() = default;

	void Init() override;
	void Reset() override;
	void SetScore(int score);
	void AddScore(int score);
};

