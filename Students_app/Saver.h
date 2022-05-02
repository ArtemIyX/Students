#pragma once
#include "Manager.h"
#include "Student.h"
#include "Group.h"
#include "Department.h"
#include "Entity.h"
#include "Menu.h"
#include "InstanceManager.h"
#include <vector>

namespace FieldNames
{
	const std::string F_Departments = "departments";
	const std::string F_Students = "students";
	const std::string F_Groups = "groups";
	const std::string F_Counter = "counter";
}

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
	FDepartment department;
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
	void ReadFile(const std::string& filepath, std::string& buffer);
	void WriteFile(const std::string& filepath, std::string& content);
	UGroup* FindGroupById(int id);
	UDepartment* FindDepartmentById(int id);
public:
	void Save(int id);
	int Load();
};

