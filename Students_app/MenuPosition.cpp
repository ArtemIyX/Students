#include "MenuPosition.h"
#include "Menu.h"
UMenuPosition::UMenuPosition(const std::vector<struct FMenuFunction>& Functions)
{
	this->Functions = Functions;
}

const std::vector<FMenuFunction>& UMenuPosition::GetFunctions() const
{
	return Functions;
}
