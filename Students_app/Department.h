#pragma once
#include <string>
#include "Entity.h"
struct FDepartment
{
private:

public:
	FDepartment();
	FDepartment(const FDepartment& Other);
	FDepartment(std::string Title);
public:
	std::string Title;
};

class UDepartment : public UEntity
{
public:

	UDepartment();
	UDepartment(const FDepartment& Data, int id);
	UDepartment(UDepartment* Other);
protected:
	FDepartment Data;
public:
	FDepartment& GetData();
	static UDepartment* CreateDepartment(const FDepartment& InData, int id);
};

