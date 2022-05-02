#include "Student.h"
#include "Constants.h"
#include "Group.h"

FStudent::FStudent()
{
	FullName = Constants::Misc::NAME_None;
	Age = 17;
}

FStudent::FStudent(const std::string& FullName, uint16_t Age, UGroup* Group, UDepartment* Department)
{
	this->FullName = FullName;
	this->Age = Age;
	this->Group = Group;
	this->Department = Department;
}

FStudent::FStudent(const FStudent& Other) : FStudent(Other.FullName, Other.Age, Other.Group, Other.Department) {	}

UStudent::UStudent()
{
	Data = FStudent();
}

UStudent::UStudent(const FStudent& Data, int id)
{
	this->Data = Data;
	this->ID = id;
}

UStudent::UStudent(UStudent* Other)
{
	this->Data = Other->Data;
}


FStudent& UStudent::GetData()
{
	return Data;
}

UStudent* UStudent::CreateStudent(const FStudent& InData, int id)
{
	UStudent* object = new UStudent(InData, id);
	return object;
}


