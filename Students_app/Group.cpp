#include "Group.h"
#include "Constants.h"
FGroup::FGroup()
{
	Title = Constants::Misc::NAME_None;
}

FGroup::FGroup(const FGroup& Other)
{
	this->Title = Other.Title;
}

UGroup::UGroup()
{
	Data = FGroup();
}

UGroup::UGroup(const FGroup& Data)
{
	this->Data = Data;
}

UGroup::UGroup(UGroup* Other) : UGroup(Other->GetData())
{
}

const FGroup& UGroup::GetData() const
{
	return Data;
}

UGroup* UGroup::CreateGroup(const UGroup& InData)
{
	UGroup* object = new UGroup(InData);
	return object;
}