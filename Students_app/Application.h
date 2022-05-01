#pragma once
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include "InstanceManager.h"
#include "Menu.h"
#include "Group.h"

class UManager;
class UMenuPosition;

namespace ApplicationMessages
{
	const std::string MSG_Groups = "Groups: \n";
	const std::string MSG_Rem_Group = "Group successfully removed\n";
	const std::string MSG_Enter_GroupName = "Enter group name: ";
	const std::string MSG_No_Groups = "There are no groups\n";
	
}

class UApplication
{
public:
	UApplication();
	~UApplication();
private:
	UMenu* Menu;
	UManager* Manager;
protected:
	std::vector<UMenuPosition*> GenerateMenuPositions();
	void StartCycle();
	void TestFunc();
	void GroupSection();
	void Group_Add();
	void Group_Show();
	void Group_Remove();
	void Select(uint16_t& index, bool& undo);


	template<typename T>
	T* SelectInstance(UInstanceManager<T>* instanceManager, std::function<void()> DrawFunc, uint16_t& Position, bool& undo)
	{
		int index = 0;
		while (true)
		{
			Menu->ClearScreen();
			DrawFunc();

			undo = false;

			while (true) {
				Menu->Print(MenuMessages::MSG_Select);
				std::string input;
				std::cin >> input;
				try {
					index = std::stoi(input);
					break;
				}
				catch (std::exception ex) {
					Menu->Warn("Try again");
				}
			}

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
};

