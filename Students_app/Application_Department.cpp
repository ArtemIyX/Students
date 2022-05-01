#include "Application.h"
#include "Manager.h"
#include "MenuPosition.h"
#include "Department.h"
#include "Tools.h"

void UApplication::Department_Section()
{
	Menu->ChangeMenuPosition(2); //TODO: Change magic numbers
}

void UApplication::Department_Add()
{
	Menu->Print(ApplicationMessages::Departments::MSG_Enter);
	std::string input;
	std::cin >> input; // change on getline

	FDepartment info(input);
	UDepartment* department = UDepartment::CreateDepartment(info);
	Manager->GetDepartmentManager()->AddInstance(department);

	Menu->Print(String::format("Department %s created\n", department->GetData().Title.c_str()));
	Menu->Wait();
}

void UApplication::Department_Show()
{
	const std::vector<UDepartment*> departments = Manager->GetDepartmentManager()->GetAllInstances();
	if (!Group_Check()) {
		Menu->Print(ApplicationMessages::Departments::MSG_No);
		Menu->Wait();
		return;
	}
	Menu->Print(ApplicationMessages::Departments::MSG_Name);
	for (size_t i = 0; i < departments.size(); ++i)
	{
		UDepartment* department = departments[i];
		FDepartment& data = department->GetData();
		Menu->Print(String::format("[%d]\t%s\n", i + 1, data.Title.c_str()));
	}
}

void UApplication::Department_Remove()
{
	if(!Department_Check()) {
		Menu->Print(ApplicationMessages::Departments::MSG_No);
		Menu->Wait();
		return;
	}
	UInstanceManager<UDepartment>* departmentManager = Manager->GetDepartmentManager();
	uint16_t index = 0;
	bool undo = false;
	UDepartment* dep = SelectInstance<UDepartment>(departmentManager, std::bind(&UApplication::Department_Show, this), index, undo);
	if (undo) {
		return;
	}
	departmentManager->RemoveInstanceAt(index - 1);
	Menu->Print(ApplicationMessages::Departments::MSG_Rem);
	Menu->Wait();
}

void UApplication::Department_Edit()
{
	const std::vector<UDepartment*> groups = Manager->GetDepartmentManager()->GetAllInstances();
	const size_t size = groups.size();
	if (size == 0) {
		Menu->Print(ApplicationMessages::Departments::MSG_No);
		Menu->Wait();
		return;
	}
	uint16_t index = 0;
	bool undo = false;
	UInstanceManager<UDepartment>* departmentManager = Manager->GetDepartmentManager();
	UDepartment* dep = SelectInstance<UDepartment>(departmentManager, std::bind(&UApplication::Department_Show, this), index, undo);
	if (undo) {
		return;
	}
	Menu->Print(ApplicationMessages::Departments::MSG_Enter);
	std::string input;
	std::cin >> input;
	FDepartment& data = dep->GetData();
	data.Title = input;
	Menu->Print(ApplicationMessages::Departments::MSG_Edit);
	Menu->Wait();
}

bool UApplication::Department_Check()
{
	return Manager->GetDepartmentManager()->GetAllInstances().size() != 0;
}
