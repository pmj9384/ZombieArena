#pragma once
#include "TextGo.h"
class UiStart : public TextGo
{

protected:
	bool active;
public:
	UiStart(const std::string& fontId, const std::string& name = "");
	virtual ~UiStart() = default;

	void Init() override;

	void Reset() override;
};


