#include "Manager.h"
#include "Student.h"
#include "Group.h"
#include "Department.h"
UManager::UManager() 
{
	StudentsManager = new UInstanceManager<UStudent>();
	GroupManager = new UInstanceManager<UGroup>();
	DepartmentManager = new UInstanceManager<UDepartment>();
}
UManager::~UManager()
{
	if (StudentsManager)
		delete StudentsManager;
	if (GroupManager)
		delete GroupManager;
}

UInstanceManager<UStudent>* UManager::GetStudentsManager() const
{
	return StudentsManager;
}

UInstanceManager<UGroup>* UManager::GetGroupManager() const
{
	return GroupManager;
}
UInstanceManager<UDepartment>* UManager::GetDepartmentManager() const
{
	return DepartmentManager;
}

