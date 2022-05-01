#pragma once
#include <string>
struct FGroup
{
private:

public:
	FGroup();
	FGroup(const FGroup& Other);
	FGroup(std::string Title);
public:
	std::string Title;
};

class UGroup
{
public:

	UGroup();
	UGroup(const FGroup& Data);
	UGroup(UGroup* Other);
protected:
	FGroup Data;
public:
	const FGroup& GetData() const;
	static UGroup* CreateGroup(const UGroup& InData);
};