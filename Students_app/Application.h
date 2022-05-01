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
	std::vector<UMenuPosition*> MenuPositions;
protected:
	std::vector<UMenuPosition*> GenerateMenuPositions();
	void StartCycle();
	void TestFunc();
public:
	UMenu* GetMenu() const;
	UManager* GetManager() const;
	void Run();
};

