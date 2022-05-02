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
};

class UGroup : public UEntity
{
public:

	UGroup();
	UGroup(const FGroup& Data, int id);
	UGroup(UGroup* Other);
protected:
	FGroup Data;
public:
	FGroup& GetData();
	static UGroup* CreateGroup(const FGroup& InData, int id);
};