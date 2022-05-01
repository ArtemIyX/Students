#include "Application.h"

#include "Manager.h"
#include "MenuPosition.h"
#include "Tools.h"
#include "Constants.h"

UApplication::UApplication()
{
	Menu = new UMenu();
	Manager = new UManager();
}

UApplication::~UApplication()
{
	delete Menu;
	delete Manager;
}

std::vector<UMenuPosition*> UApplication::GenerateMenuPositions()
{
	UMenuPosition* MainMenu = UMenuPosition::CreateMenuPosition(
		{ FMenuFunction("Groups", std::bind(&UApplication::Group_Section, this)),
		FMenuFunction("Departments", std::bind(&UApplication::Department_Section, this)),
		FMenuFunction("Students", std::bind(&UApplication::Student_Section, this)) },
		"Main menu", nullptr);
	UMenuPosition* Groups = UMenuPosition::CreateMenuPosition(
		{ FMenuFunction("Show list of groups", [this]() { Group_Show();  Menu->Wait(); }),
		FMenuFunction("Add new group", std::bind(&UApplication::Group_Add, this)),
		FMenuFunction("Remove group", std::bind(&UApplication::Group_Remove, this)),
		FMenuFunction("Edit group", std::bind(&UApplication::Group_Edit, this)) },
		"Groups", MainMenu);
	UMenuPosition* Departments = UMenuPosition::CreateMenuPosition(
		{ FMenuFunction("Show list of departments", [this]() { Department_Show();  Menu->Wait(); }),
		FMenuFunction("Add new department", std::bind(&UApplication::Department_Add, this)),
		FMenuFunction("Remove department", std::bind(&UApplication::Department_Remove, this)),
		FMenuFunction("Edit department", std::bind(&UApplication::Department_Edit, this)) },
		"Departments", MainMenu);
	UMenuPosition* Students = UMenuPosition::CreateMenuPosition(
		{ FMenuFunction("Show list of students", [this]() { Student_Show();  Menu->Wait(); }),
		FMenuFunction("Add new student", std::bind(&UApplication::Student_Add, this)),
		FMenuFunction("Remove student", std::bind(&UApplication::Student_Remove, this)),
		FMenuFunction("Edit student", std::bind(&UApplication::Student_Edit, this)) },
		"Students", MainMenu);
	return {
		MainMenu, Groups, Departments, Students
	};
}



UMenu* UApplication::GetMenu() const
{
	return Menu;
}

UManager* UApplication::GetManager() const
{
	return Manager;
}

void UApplication::Run()
{
	std::vector<UMenuPosition*> MenuFunctions = GenerateMenuPositions();
	Menu->Init(MenuFunctions);
	StartCycle();
}

void UApplication::Select(uint16_t& index, bool& undo)
{
	int menuIndex = Menu->GetCurrentMenuPositionIndex();
	index = 0;
	undo = false;
	while (true) {
		Menu->ClearScreen();
		Menu->Draw(menuIndex);
		try {
			index = Menu->Select(menuIndex, undo);
			break;
		}
		catch (std::exception ex) {
			Menu->Warn("Try again");
		}
	}
}

int UApplication::GetInt(const std::string& Prompt, int min, int max)
{
	std::string input;
	int res = 0;
	while (true)
	{
		Menu->Print(Prompt);
		input.clear();
		std::cin >> input;
		try
		{
			res = std::stoi(input);
			if (res == -1) 
			{
				return -1;
			}
			if (res < min || res > max)
			{
				throw std::exception();
			}
			return res;
		}
		catch (...)
		{
			Menu->Print("Try again\n");
		}
	}
	return -1;
}

std::string UApplication::GetString(const std::string& Prompt)
{
	Menu->Print(Prompt);
	std::string input;
	std::cin >> input;
	return input;
}

bool UApplication::GetBool(const std::string& Prompt)
{
	char ch;
	while (true) 
	{
		Menu->Print(String::format("%s (y/n) ", Prompt.c_str()));
		std::cin >> ch;
		if (ch == Constants::Misc::yes1 || ch == Constants::Misc::yes2) 
		{
			return true;
		}
		else if (ch == Constants::Misc::no1 || ch == Constants::Misc::no2)
		{
			return false;
		}
		Menu->Print("Try again\n");
	}
	
	return false; //never call this
}

void UApplication::StartCycle()
{
	do
	{
		Menu->ClearScreen();
		int menuIndex = Menu->GetCurrentMenuPositionIndex();
		if (menuIndex == -1) {
			return; //never call this
		}

		uint16_t index = 0;
		bool undo = false;
		Select(index, undo);

		if (undo) {
			if (UMenuPosition* menuPos = Menu->GetCurrentMenuPosition()->GetOwner()) {
				Menu->SetCurrentMenuPosition(menuPos);
			}
			else {
				return; //exit
			}
		}
		else {
			Menu->GetCurrentMenuPosition()->GetFunctions()[index - 1].Func();
		}
	} while (true);
}





