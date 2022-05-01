#pragma once
#include "InstanceManager.h"
class UStudent;
class UGroup;
class UDepartment;

class UManager
{
public:
	UManager();
	~UManager();

protected:
	UInstanceManager<UStudent>* StudentsManager;
	UInstanceManager<UGroup>* GroupManager;
	UInstanceManager<UDepartment>* DepartmentManager;
public:
	UInstanceManager<UStudent>* GetStudentsManager() const;
	UInstanceManager<UGroup>* GetGroupManager() const;
	UInstanceManager<UDepartment>* GetDepartmentManager() const;
};

