#pragma once
#include <vector>
#include <string>
class UMenu;
class UManager;
class UMenuPosition;

namespace ApplicationMessages 
{
	const std::string MSG_Enter_GroupName = "Enter group name: ";
	const std::string MSG_No_Groups = "There are no groups\n";
	const std::string MSG_Groups = "Groups: \n";
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
public:
	UMenu* GetMenu() const;
	UManager* GetManager() const;
	void Run();
};

