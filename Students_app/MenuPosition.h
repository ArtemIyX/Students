#pragma once
#include <vector>
#include <string>
struct FMenuFunction;
class UMenuPosition
{
public:
	UMenuPosition(const std::vector<FMenuFunction>& Functions, const std::string& Title, UMenuPosition* Owner);
protected:
	std::vector<FMenuFunction> Functions;
	UMenuPosition* Owner;
	std::string Title;
public:
	const std::vector<FMenuFunction>& GetFunctions() const;
	UMenuPosition* GetOwner() const;
	std::string GetTitle() const;
	static UMenuPosition* CreateMenuPosition(const std::vector<FMenuFunction>& Functions, const std::string& Title, UMenuPosition* Owner);
};

