#pragma once
#include <string>
#include <functional>
#include <vector>
#include <ostream>

namespace MenuMessages
{
	const std::string MSG_NoFunctions = "There are no functions";
}

struct FMenuFunction
{
	std::string Title;
	std::function<void()> Func;
	friend std::ostream& operator<<(std::ostream& os, const FMenuFunction& mf);
};

class UMenu
{
public:
	UMenu(const std::vector<FMenuFunction>& Functions);
protected:
	std::vector<FMenuFunction> Functions;
protected:
	void Print(const std::string& msg);
	void Warn(const std::string& msg);
public:
	void Init(const std::vector<FMenuFunction>& Functions);
	void Draw();

};

