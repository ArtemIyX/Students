#pragma once
#include <vector>
class UMenu;
class UManager;
class UMenuPosition;
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
public:
	UMenu* GetMenu() const;
	UManager* GetManager() const;
	void Run();
};

