#pragma once
#include <string>
#include "Entity.h"
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

class UGroup : UEntity
{
public:

	UGroup();
	UGroup(const FGroup& Data, int id);
	UGroup(UGroup* Other);
protected:
	FGroup Data;
public:
	FGroup& GetData();
	static UGroup* CreateGroup(const FGroup& InData);
};