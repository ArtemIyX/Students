#include "Application.h"
#include "Menu.h"
#include "Manager.h"

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

std::vector<FMenuFunction> UApplication::GetMenuFunctions()
{
    return
    {
        FMenuFunction(std::string("Test function"), 
        std::bind(&UApplication::TestFunc, this))
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
    std::vector<FMenuFunction> MenuFunctions = GetMenuFunctions();
    Menu->Init(MenuFunctions);
    StartCycle();
}

void UApplication::StartCycle()
{
    do 
    {
        system("cls");
        Menu->Draw();
        getchar();
    } while (true);
}

void UApplication::TestFunc()
{
    Menu->Print("Hello dude");
}
