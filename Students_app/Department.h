#pragma once
#include <string>
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

class UDepartment
{
public:

	UDepartment();
	UDepartment(const FDepartment& Data);
	UDepartment(UDepartment* Other);
protected:
	FDepartment Data;
public:
	const FDepartment& GetData() const;
	static UDepartment* CreateDepartment(const FDepartment& InData);
};

