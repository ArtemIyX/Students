#include "Application.h"
#include "Manager.h"
#include "MenuPosition.h"
#include "Department.h"
#include "Group.h"
#include "Student.h"
#include "Tools.h"

void UApplication::Student_Section()
{
	Menu->ChangeMenuPosition(3);
}

void UApplication::Student_Add()
{

	UInstanceManager<UGroup>* groupManager = Manager->GetGroupManager();
	if (groupManager->GetAllInstances().size() == 0)
	{
		Menu->Warn("There are no groups, so you cant add student");
		return;
	}
	UInstanceManager<UDepartment>* departmentManager = Manager->GetDepartmentManager();
	if (departmentManager->GetAllInstances().size() == 0)
	{
		Menu->Warn("There are no departments, so you cant add student");
		return;
	}
	std::string name = GetString(ApplicationMessages::Student::MSG_Enter_Name);
	int age = GetInt(ApplicationMessages::Student::MSG_Enter_Age, 1, 100);
	Menu->Print(ApplicationMessages::Student::MSG_Enter_Group);

	uint16_t index = 0;
	bool undo = false;
	Menu->Print(ApplicationMessages::Student::MSG_Enter_Group);
	UGroup* group = SelectInstance<UGroup>(groupManager, std::bind(&UApplication::Group_Show, this), index, undo);
	if (undo)
		return;

	Menu->Print(ApplicationMessages::Student::MSG_Enter_Department);
	UDepartment* dep = SelectInstance<UDepartment>(departmentManager, std::bind(&UApplication::Department_Show, this), index, undo);
	if (undo)
		return;

	UStudent* student = UStudent::CreateStudent(FStudent(name, age, group, dep));
	if (!Manager->GetStudentsManager()->AddInstance(student))
	{
		delete student;
		return;
	}

	Menu->Print(String::format("Student %s created\n", student->GetData().FullName.c_str()));
	Menu->Wait();
}

void UApplication::Student_Show()
{

	if (!Student_Check())
	{
		Menu->Print(ApplicationMessages::Student::MSG_No);
		return;
	}
	const std::vector<UStudent*> students = Manager->GetStudentsManager()->GetAllInstances();
	for (size_t i = 0; i < students.size(); ++i)
	{
		FStudent& data = students[i]->GetData();
		Menu->Print(String::format("[%d]\t%s %d years (%s - %s)\n", i + 1,
			data.FullName.c_str(),
			data.Age,
			data.Group->GetData().Title.c_str(),
			data.Department->GetData().Title.c_str()));
	}

}

void UApplication::Student_Remove()
{
	if (!Student_Check())
	{
		Menu->Print(ApplicationMessages::Student::MSG_No);
		return;
	}
	UInstanceManager<UStudent>* studentsManager = Manager->GetStudentsManager();
	uint16_t index = 0;
	bool undo = false;
	UStudent* student = SelectInstance<UStudent>(studentsManager, std::bind(&UApplication::Student_Show, this), index, undo);
	if (undo)
	{
		return;
	}
	
	studentsManager->RemoveInstanceAt(index - 1);
	Menu->Print(ApplicationMessages::Student::MSG_Rem);
	Menu->Wait();
}

void UApplication::Student_Edit()
{
	if (!Student_Check())
	{
		Menu->Print(ApplicationMessages::Student::MSG_No);
		return;
	}
	UInstanceManager<UStudent>* studentsManager = Manager->GetStudentsManager();
	uint16_t index = 0;
	bool undo = false;
	UStudent* student = SelectInstance<UStudent>(studentsManager, std::bind(&UApplication::Student_Show, this), index, undo);
	if (undo)
	{
		return;
	}
	FStudent& data = student->GetData();
	bool editName = GetBool(ApplicationMessages::Student::Question::MSG_Edit_Name);
	if (editName)
	{
		std::string input = GetString(ApplicationMessages::Student::MSG_Enter_Name);
		data.FullName = input;
	}
	bool editAge = GetBool(ApplicationMessages::Student::Question::MSG_Edit_Age);
	if (editAge)
	{
		int age = GetInt(ApplicationMessages::Student::MSG_Enter_Age, 1, 100);
		data.Age = age;
	}
	if (Manager->GetGroupManager()->GetAllInstances().size() > 1)
	{
		bool editGroup = GetBool(ApplicationMessages::Student::Question::MSG_Edit_Group);
		if (editGroup)
		{
			UInstanceManager<UGroup>* groupManager = Manager->GetGroupManager();
			UGroup* group = SelectInstance<UGroup>(groupManager, std::bind(&UApplication::Group_Show, this), index, undo);
			if (!undo)
			{
				data.Group = group;
			}
		}
	}
	if (Manager->GetDepartmentManager()->GetAllInstances().size() > 1)
	{
		bool editDepartment = GetBool(ApplicationMessages::Student::Question::MSG_Edit_Dep);
		if (editDepartment)
		{
			UInstanceManager<UDepartment>* departmentManager = Manager->GetDepartmentManager();
			UDepartment* dep = SelectInstance<UDepartment>(departmentManager, std::bind(&UApplication::Department_Show, this), index, undo);
			if (!undo)
			{
				data.Department = dep;
			}
		}
	}
	// message?
}

bool UApplication::Student_Check()
{
	return Manager->GetStudentsManager()->GetAllInstances().size() != 0;
}

