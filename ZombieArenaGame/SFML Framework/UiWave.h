#pragma once
#include "TextGo.h"
class UiWave :
    public TextGo
{
protected:

    std::string waveformat;
	int wave = 0;

public:
	UiWave(const std::string& fontId, const std::string& name = "");
	~UiWave() = default;

	void Init() override;
	void Reset() override;
	void SetWave(int wave);
	void AddWave(int wave);

	int GetWave() const { return wave; }//wave 받아오기
};

