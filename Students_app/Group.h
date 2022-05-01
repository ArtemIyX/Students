#pragma once
#include <string>
struct FGroup
{
private:

public:
	FGroup();
	FGroup(std::string Title);
public:
	std::string Title;
	//friend std::ostream& operator<<(std::ostream& os, const FGroup& group);
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
	FGroup& GetData();
	static UGroup* CreateGroup(const UGroup& InData);
};