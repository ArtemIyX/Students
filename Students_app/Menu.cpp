#include "Menu.h"
#include "Tools.h"
#include <iostream>



std::ostream& operator<<(std::ostream& os, const FMenuFunction& mf)
{
	os << mf.Title;
	return os;
}


UMenu::UMenu(const std::vector<FMenuFunction>& Functions)
{
	Init(Functions);
}


void UMenu::Print(const std::string& msg)
{
	std::cout << msg;
}

void UMenu::Warn(const std::string& msg)
{
	std::cout << "WARN: " << msg << '\n';
	getchar();
}

void UMenu::Init(const std::vector<FMenuFunction>& Functions)
{
	this->Functions = Functions;
}

void UMenu::Draw()
{
	const size_t size = Functions.size();
	if (size == 0) {
		Print(MenuMessages::MSG_NoFunctions);
		return;
	}
	for (size_t i = 0; i < size; ++i) {
		Print(String::format("[%d]\t%s\n", i + 1, Functions[i].Title.c_str()));
	}
}

