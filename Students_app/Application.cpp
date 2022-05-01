#include "Application.h"
#include "Menu.h"
#include "Manager.h"
#include "MenuPosition.h"
UApplication::UApplication()
{
    Menu = new UMenu();
    Manager = new UManager();
}

UApplication::~UApplication()
{
    delete Menu;
    delete Manager;
    for (size_t i = 0; i < MenuPositions.size(); ++i) {
        delete MenuPositions[i];
    }
}

std::vector<UMenuPosition*> UApplication::GenerateMenuPositions()
{
    UMenuPosition* MainMenu = UMenuPosition::CreateMenuPosition(
        { FMenuFunction("Test function", std::bind(&UApplication::TestFunc, this)) }, 
        nullptr);
    return {
        MainMenu
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
    std::vector<UMenuPosition*> MenuFunctions = GenerateMenuPositions();
    Menu->Init(MenuFunctions);
    StartCycle();
}


void UApplication::StartCycle()
{
    do 
    {
        Menu->ClearScreen();
        int menuIndex = Menu->GetCurrentMenuPositionIndex();
        if (menuIndex == -1) {
            return; //never call this
        }
        
        uint16_t index = 0;
        bool undo = false;
        while (true) {
            Menu->ClearScreen();
            Menu->Draw(menuIndex);
            try {
                index = Menu->Select(menuIndex, undo);
                break;
            }
            catch (std::exception ex) {
                Menu->Warn("Try again");
            }
        }

        if (undo) {
            if (UMenuPosition* menuPos = Menu->GetCurrentMenuPosition()->GetOwner()) {
                Menu->SetCurrentMenuPosition(menuPos);
            }
            else {
                return; //exit
            }
        }
        else {
            Menu->GetCurrentMenuPosition()->GetFunctions()[index - 1].Func();
        }
    } while (true);
}

void UApplication::TestFunc()
{
    Menu->ClearScreen();
    Menu->Print("Hello dude");
    Menu->Wait();
}
