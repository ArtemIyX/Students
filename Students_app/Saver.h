#pragma once
#include "Manager.h"
#include "Student.h"
#include "Group.h"
#include "Department.h"
#include "Entity.h"
#include "Menu.h"
#include "InstanceManager.h"
#include <vector>

class Sid
{
public:

	int id;
};

class SStudent : public Sid
{
public:
	FStudent f;
	int dep;
	int group;
};
class SGroup : public Sid
{
public:
	FGroup group;
};
class SDep : public Sid
{
public:
	FDepartment f;
};

class FSaver
{
public:
	int Counter;
	std::vector<SGroup> Groups;
	std::vector<SDep> Departments;
	std::vector<SStudent> Students;
};

class USaver
{
public:
	USaver(UManager* manager);
protected:
	UManager* managerRef;
public:
	void Save(int id);
	int Load();
};
