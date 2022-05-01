#include "UStudent.h"
#include "Constants.h"
FStudent::FStudent()
{
	FullName = Constants::Misc::NAME_None;
	Age = 17;
}

FStudent::FStudent(const std::string& FullName, uint16_t Age)
{
	this->FullName = FullName;
	this->Age = Age;
}

FStudent::FStudent(const FStudent& Other) : FStudent(Other.FullName, Other.Age) {	}

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


