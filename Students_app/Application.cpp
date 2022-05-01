#include "Application.h"

#include "Manager.h"
#include "MenuPosition.h"
#include "Tools.h"


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
		{ FMenuFunction("Groups", std::bind(&UApplication::GroupSection, this)) },
		"Main menu", nullptr);
	UMenuPosition* Groups = UMenuPosition::CreateMenuPosition(
		{ FMenuFunction("Show list of groups", [this]() { Group_Show();  Menu->Wait(); }),
		FMenuFunction("Add new group", std::bind(&UApplication::Group_Add, this)),
		FMenuFunction("Remove group", std::bind(&UApplication::Group_Remove, this)),
		FMenuFunction("Edit group", std::bind(&UApplication::Group_Edit, this)) },
		"Groups", MainMenu);
	return {
		MainMenu, Groups
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



void UApplication::GroupSection()
{
	Menu->ChangeMenuPosition(1); //TODO: Change magic numbers
}

void UApplication::Group_Add()
{
	Menu->Print(ApplicationMessages::Group::MSG_Enter);
	std::string input;
	std::cin >> input; // change on getline

	FGroup info(input);
	UGroup* group = UGroup::CreateGroup(info);
	Manager->GetGroupManager()->AddInstance(group);

	Menu->Print(String::format("Group %s created\n", group->GetData().Title.c_str()));
	Menu->Wait();
}

void UApplication::Group_Show()
{
	const std::vector<UGroup*> groups = Manager->GetGroupManager()->GetAllInstances();
	if (!Group_Check()) {
		Menu->Print(ApplicationMessages::Group::MSG_No);
		Menu->Wait();
		return;
	}
	Menu->Print(ApplicationMessages::Group::MSG_Name);
	for (size_t i = 0; i < groups.size(); ++i)
	{
		UGroup* group = groups[i];
		const FGroup& data = group->GetData();
		Menu->Print(String::format("[%d]\t%s\n", i + 1, data.Title.c_str()));
	}
}

void UApplication::Group_Remove()
{
	if (!Group_Check()) {
		Menu->Print(ApplicationMessages::Group::MSG_No);
		Menu->Wait();
		return;
	}
	UInstanceManager<UGroup>* groupManager = Manager->GetGroupManager();
	uint16_t index = 0;
	bool undo = false;
	UGroup* group = SelectInstance<UGroup>(groupManager, std::bind(&UApplication::Group_Show, this), index, undo);
	if (undo) {
		return;
	}
	groupManager->RemoveInstanceAt(index - 1);
	Menu->Print(ApplicationMessages::Group::MSG_Rem);
	Menu->Wait();
}

void UApplication::Group_Edit()
{
	const std::vector<UGroup*> groups = Manager->GetGroupManager()->GetAllInstances();
	const size_t size = groups.size();
	if (size == 0) {
		Menu->Print(ApplicationMessages::Group::MSG_No);
		Menu->Wait();
		return;
	}
	uint16_t index = 0;
	bool undo = false;
	UInstanceManager<UGroup>* groupManager = Manager->GetGroupManager();
	UGroup* group = SelectInstance<UGroup>(groupManager, std::bind(&UApplication::Group_Show, this), index, undo);
	if (undo) {
		return;
	}
	Menu->Print(ApplicationMessages::Group::MSG_Enter);
	std::string input;
	std::cin >> input;
	FGroup& data = group->GetData();
	data.Title = input;
	Menu->Print(ApplicationMessages::Group::MSG_Edit);
	Menu->Wait();
}

bool UApplication::Group_Check()
{
	return Manager->GetGroupManager()->GetAllInstances().size() != 0;
}


