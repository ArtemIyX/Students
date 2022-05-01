#pragma once
#include <vector>
struct FMenuFunction;
class UMenuPosition
{
public:
	UMenuPosition(const std::vector<FMenuFunction>& Functions, UMenuPosition* Owner);
protected:
	std::vector<FMenuFunction> Functions;
	UMenuPosition* Owner;
public:
	const std::vector<FMenuFunction>& GetFunctions() const;
	UMenuPosition* GetOwner() const;
	static UMenuPosition* CreateMenuPosition(const std::vector<FMenuFunction>& Functions, UMenuPosition* Owner);
};

