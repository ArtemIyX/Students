#include "Department.h"
#include "Constants.h"
FDepartment::FDepartment()
{
	Title = Constants::Misc::NAME_None;
}

FDepartment::FDepartment(std::string Title)
{
	this->Title = Title;
}

FDepartment::FDepartment(const FDepartment& Other) : FDepartment(Other.Title)
{

}

UDepartment::UDepartment()
{
	Data = FDepartment();
}

UDepartment::UDepartment(const FDepartment& Data, int id)
{
	this->Data = Data;
	this->ID = id;
}

UDepartment::UDepartment(UDepartment* Other) : UDepartment(Data, Other->ID)
{
}

FDepartment& UDepartment::GetData() 
{
	return Data;
}

UDepartment* UDepartment::CreateDepartment(const FDepartment& InData)
{
	UDepartment* object = new UDepartment(InData, UEntity::GetNextID());
	return object;
}
