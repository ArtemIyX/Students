#pragma once
#include <string>
#include <functional>
#include <vector>
#include <ostream>
class UMenuPosition;
namespace MenuMessages
{
	const std::string MSG_NoFunctions = "There are no functions";
	const std::string MSG_Select = "Select option, -1 for exit\n-->";
	const std::string MSG_IndexError = "Incorrect data, try again or -1 for exit";

}

struct FMenuFunction
{
	FMenuFunction();
	FMenuFunction(std::string Title, std::function<void()> Func);

	std::string Title;
	std::function<void()> Func;
	friend std::ostream& operator<<(std::ostream& os, const FMenuFunction& mf);
};

class UMenu
{
public:
	UMenu();
	UMenu(const std::vector<FMenuFunction>& Functions);
protected:
	std::vector<UMenuPosition*> MenuPositions;
	
public:
	void Init(const std::vector<FMenuFunction>& Functions);
	void Draw(size_t MenuPositionIndex);
	void Print(const std::string& msg);
	void Warn(const std::string& msg);
	uint16_t Select(size_t MenuPositionIndex, bool& undo);
};

