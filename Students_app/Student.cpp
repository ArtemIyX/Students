#include "Student.h"
#include "Constants.h"
#include "Group.h"

FStudent::FStudent()
{
	FullName = Constants::Misc::NAME_None;
	Age = 17;
}

FStudent::FStudent(const std::string& FullName, uint16_t Age, UGroup* Group)
{
	this->FullName = FullName;
	this->Age = Age;
	this->Group = Group;
}

FStudent::FStudent(const FStudent& Other) : FStudent(Other.FullName, Other.Age, Other.Group) {	}

UStudent::UStudent()
{
	Data = FStudent();
}

UStudent::UStudent(const FStudent& Data)
{
	this->Data = Data;
}

UStudent::UStudent(UStudent* Other)
{
	this->Data = Other->Data;
}

const FStudent& UStudent::GetData() const
{
	return Data;
}

UStudent* UStudent::CreateStudent(const FStudent& InData)
{
	UStudent* object = new UStudent(InData);
	return object;
}


