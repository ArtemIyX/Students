#pragma once
#include <vector>
class UMenu;
class UManager;

class UApplication
{
public:
	UApplication();
	~UApplication();
private:
	UMenu* Menu;
	UManager* Manager;
protected:
	std::vector<struct FMenuFunction> GetMenuFunctions();
	void StartCycle();
	void TestFunc();
public:
	UMenu* GetMenu() const;
	UManager* GetManager() const;
	void Run();
};

