#include "MenuPosition.h"
#include "Menu.h"
UMenuPosition::UMenuPosition(const std::vector<struct FMenuFunction>& Functions, UMenuPosition* Owner)
{
	this->Functions = Functions;
}

const std::vector<FMenuFunction>& UMenuPosition::GetFunctions() const
{
	return Functions;
}

UMenuPosition* UMenuPosition::GetOwner() const
{
	return Owner;
}

UMenuPosition* UMenuPosition::CreateMenuPosition(const std::vector<FMenuFunction>& Functions, UMenuPosition* Owner)
{
	UMenuPosition* object = new UMenuPosition(Functions, Owner);
	return object;
}
