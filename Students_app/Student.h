#pragma once
#include <string>
#include "Entity.h"
struct FStudent 
{
private:

public:
	FStudent();
	FStudent(const std::string& FullName, uint16_t Age, class UGroup* Group, class UDepartment* Department);
	FStudent(const FStudent& Other);
public:
	std::string FullName;
	uint16_t Age;
	class UGroup* Group;
	class UDepartment* Department;
};

class UStudent : UEntity
{
public:

	UStudent();
	UStudent(const FStudent& Data, int id);
	UStudent(UStudent* Other);
protected:
	FStudent Data;
public:
	FStudent& GetData();
	static UStudent* CreateStudent(const FStudent& InData);
};

