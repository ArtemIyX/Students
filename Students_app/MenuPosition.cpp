#include "MenuPosition.h"
#include "Menu.h"

UMenuPosition::UMenuPosition(const std::vector<struct FMenuFunction>& Functions, const std::string& Title, UMenuPosition* Owner)
{
	this->Functions = Functions;
	this->Title = Title;
	this->Owner = Owner;
}

const std::vector<FMenuFunction>& UMenuPosition::GetFunctions() const
{
	return Functions;
}

UMenuPosition* UMenuPosition::GetOwner() const
{
	return Owner;
}

std::string UMenuPosition::GetTitle() const
{
	return Title;
}

UMenuPosition* UMenuPosition::CreateMenuPosition(const std::vector<FMenuFunction>& Functions, const std::string& Title, UMenuPosition* Owner)
{
	UMenuPosition* object = new UMenuPosition(Functions, Title, Owner);
	return object;
}
