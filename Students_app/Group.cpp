#include "Group.h"
#include "Constants.h"
FGroup::FGroup()
{
	Title = Constants::Misc::NAME_None;
}
FGroup::FGroup(std::string Title)
{
	this->Title = Title;
}


UGroup::UGroup()
{
	Data = FGroup();
}

UGroup::UGroup(const FGroup& Data, int id)
{
	this->Data = Data;
	this->ID = id;
}

UGroup::UGroup(UGroup* Other) : UGroup(Other->GetData(), Other->ID)
{
}

FGroup& UGroup::GetData()
{
	return Data;
}

UGroup* UGroup::CreateGroup(const FGroup& InData, int id)
{
	UGroup* object = new UGroup(InData, id);
	return object;
}

