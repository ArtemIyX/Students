#include "Menu.h"

#include <iostream>
#include "Tools.h"
#include "Constants.h"
#include "MenuPosition.h"

std::ostream& operator<<(std::ostream& os, const FMenuFunction& mf)
{
	os << mf.Title;
	return os;
}


UMenu::UMenu()
{
	CurrentMenuPosition = nullptr;
}



void UMenu::Print(const std::string& msg)
{
	std::cout << msg;
}

void UMenu::Warn(const std::string& msg)
{
	std::cout << "WARN: " << msg << '\n';
	Wait();
}

void UMenu::Wait()
{
	system("pause");
}

void UMenu::ClearScreen()
{
	system("cls");
}

uint16_t UMenu::Select(size_t MenuPositionIndex, bool& undo)
{
	std::string input;
	undo = false;
	while (true) {
		Print(MenuMessages::MSG_Select);
		input.clear();
		std::cin >> input;
		int index = std::stoi(input);
		if (index == -1) {
			undo = true;
			return -1;
		}
		if (!(index < 1 || index > MenuPositions[MenuPositionIndex]->GetFunctions().size())) {
			return index;
		}
		else {
			throw std::exception("Index error");
		}
	}
}

int UMenu::GetCurrentMenuPositionIndex() const
{
	if (CurrentMenuPosition) {
		for (size_t i = 0; i < MenuPositions.size(); ++i) {
			if (MenuPositions[i] == CurrentMenuPosition) {
				return i;
			}
		}
	}
	return -1;
}

void UMenu::SetCurrentMenuPosition(UMenuPosition* MenuPosition)
{
	CurrentMenuPosition = MenuPosition;
}

UMenuPosition* UMenu::GetCurrentMenuPosition() const
{
	return CurrentMenuPosition;
}

void UMenu::Init(std::vector<UMenuPosition*> MenuPositions)
{
	this->MenuPositions = MenuPositions;
	CurrentMenuPosition = MenuPositions[0];
}

void UMenu::Draw(size_t MenuPositionIndex)
{
	UMenuPosition* position = MenuPositions[MenuPositionIndex];
	const std::vector<FMenuFunction>& Functions = position->GetFunctions();
	const size_t size = Functions.size();
	if (size == 0) {
		Print(MenuMessages::MSG_NoFunctions);
		return;
	}
	for (size_t i = 0; i < size; ++i) {
		Print(String::format("[%d]\t%s\n", i + 1, Functions[i].Title.c_str()));
	}
}


FMenuFunction::FMenuFunction()
{
	Title = Constants::Misc::NAME_None;
}

FMenuFunction::FMenuFunction(std::string Title, std::function<void()> Func)
{
	this->Title = Title;
	this->Func = Func;
}
