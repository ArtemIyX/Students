#include "Application.h"
#include "Manager.h"
#include "MenuPosition.h"
#include "Tools.h"

void UApplication::Group_Section()
{
	Menu->ChangeMenuPosition(1); //TODO: Change magic numbers
}

void UApplication::Group_Add()
{
	std::string input = GetString(ApplicationMessages::Group::MSG_Enter);

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
	if (!Group_Check()) {
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
	std::string input = GetString(ApplicationMessages::Group::MSG_Enter);
	FGroup& data = group->GetData();
	data.Title = input;
	Menu->Print(ApplicationMessages::Group::MSG_Edit);
	Menu->Wait();
}

bool UApplication::Group_Check()
{
	return Manager->GetGroupManager()->GetAllInstances().size() != 0;
}


