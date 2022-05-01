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

UGroup::UGroup(const FGroup& Data)
{
	this->Data = Data;
}

UGroup::UGroup(UGroup* Other) : UGroup(Other->GetData())
{
}

FGroup& UGroup::GetData()
{
	return Data;
}

UGroup* UGroup::CreateGroup(const UGroup& InData)
{
	UGroup* object = new UGroup(InData);
	return object;
}

//std::ostream& operator<<(std::ostream& os, const FGroup& group)
//{
//	os << group.Title;
//	return os;
//}
