#pragma once
#include <string>
#include <functional>
#include <vector>
#include <ostream>
class UMenuPosition;
namespace MenuMessages
{
	const std::string MSG_NoFunctions = "There are no functions";
	const std::string MSG_Select = "Select option, -1 for exit\n-->  ";
	const std::string MSG_IndexError = "Try again";

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
protected:
	std::vector<UMenuPosition*> MenuPositions;
	UMenuPosition* CurrentMenuPosition;
protected:
	
public:
	void Init(std::vector<UMenuPosition*> Positions);
	void Draw(size_t MenuPositionIndex);
	void Print(const std::string& msg);
	void Warn(const std::string& msg);
	void Wait();
	void ClearScreen();
	uint16_t Select(size_t MenuPositionIndex, bool& undo);
	int GetCurrentMenuPositionIndex() const;
	void SetCurrentMenuPosition(UMenuPosition* MenuPosition);
	UMenuPosition* GetCurrentMenuPosition() const;
};

