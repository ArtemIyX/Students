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

UDepartment::UDepartment(const FDepartment& Data)
{
	this->Data = Data;
}

UDepartment::UDepartment(UDepartment* Other) : UDepartment(Data)
{
}

FDepartment& UDepartment::GetData() 
{
	return Data;
}

UDepartment* UDepartment::CreateDepartment(const FDepartment& InData)
{
	UDepartment* object = new UDepartment(InData);
	return object;
}
