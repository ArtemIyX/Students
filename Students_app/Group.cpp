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

UGroup* UGroup::CreateGroup(const FGroup& InData)
{
	UGroup* object = new UGroup(InData, UEntity::GetNextID());
	return object;
}

//std::ostream& operator<<(std::ostream& os, const FGroup& group)
//{
//	os << group.Title;
//	return os;
//}
