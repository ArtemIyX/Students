#pragma once
#include <string>
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

class UStudent
{
public:

	UStudent();
	UStudent(const FStudent& Data);
	UStudent(UStudent* Other);
protected:
	FStudent Data;
public:
	const FStudent& GetData() const;
	static UStudent* CreateStudent(const FStudent& InData);
};

