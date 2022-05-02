#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include "InstanceManager.h"
#include "Menu.h"
class UManager;
class UMenuPosition;

namespace ApplicationMessages
{
	namespace Group
	{
		const std::string MSG_Name = "Groups: \n";
		const std::string MSG_Rem = "Group successfully removed\n";
		const std::string MSG_Edit = "Group successfully edited\n";
		const std::string MSG_Enter = "Enter group name: ";
		const std::string MSG_No = "There are no groups\n";
		const std::string MSG_Con = "Group is connected with student\n";
	}

	namespace Departments
	{
		const std::string MSG_Name = "Departments: \n";
		const std::string MSG_Rem = "Department successfully removed\n";
		const std::string MSG_Edit = "Department successfully edited\n";
		const std::string MSG_Enter = "Enter Department name: ";
		const std::string MSG_No = "There are no Departments\n";
		const std::string MSG_Con = "Department is connected with student\n";
	}
	namespace Student
	{
		const std::string MSG_Name = "Students: \n";
		const std::string MSG_Rem = "Student successfully removed\n";
		const std::string MSG_Edit = "Student successfully edited\n";
		const std::string MSG_Enter_Name = "Enter Student name: ";
		const std::string MSG_Enter_Age = "Enter Student age: ";
		const std::string MSG_Enter_Group = "Select group for student:\n";
		const std::string MSG_Enter_Department = "Enter department for student:\n";
		const std::string MSG_No = "There are no Students\n";


		namespace Question
		{
			const std::string MSG_Edit_Name = "Edit name? ";
			const std::string MSG_Edit_Age = "Edit age? ";
			const std::string MSG_Edit_Group = "Edit group? ";
			const std::string MSG_Edit_Dep = "Edit department? ";
		}
	}
	
}

class UApplication
{
public:
	UApplication();
	~UApplication();
private:
	UMenu* Menu;
	UManager* Manager;
	int Counter_ID;
private:
	int GetInt(const std::string& Prompt, int min, int max);
	std::string GetString(const std::string& Prompt);
	bool GetBool(const std::string& Prompt);

protected:
	
protected:

	int GetID();
	std::vector<UMenuPosition*> GenerateMenuPositions();

	void StartCycle();
	void Select(uint16_t& index, bool& undo);
	void Group_Section();
	void Group_Add();
	void Group_Show();
	void Group_Remove();
	void Group_Edit();
	bool Group_Check();

	void Department_Section();
	void Department_Add();
	void Department_Show();
	void Department_Remove();
	void Department_Edit();
	bool Department_Check();

	void Student_Section();
	void Student_Add();
	void Student_Show();
	void Student_Remove();
	void Student_Edit();
	bool Student_Check();

	bool IsGroupConnected(class UGroup* group);
	bool IsDepartmentConnected(class UDepartment* deparment);

	void FastDebug();

	template<typename T>
	T* SelectInstance(UInstanceManager<T>* instanceManager, std::function<void()> DrawFunc, uint16_t& Position, bool& undo)
	{
		undo = false;
		int index = 0;
		while (true)
		{
			Menu->ClearScreen();
			DrawFunc();

			index = GetInt(MenuMessages::MSG_Select, 1, instanceManager->GetAllInstances().size());
			if (index == -1) {
				undo = true;
				Position = 0;
				return nullptr;
			}
			std::vector<T*> instances = instanceManager->GetAllInstances();
			if (!(index < 1 || static_cast<size_t>(index) > instances.size())) {
				Position = index;
				return instances[index - 1];
			}
			else {
				Menu->Warn("Try again");
			}
		}


	}
public:
	UMenu* GetMenu() const;
	UManager* GetManager() const;
	void Run();
	void Save();
	void Load();
};

