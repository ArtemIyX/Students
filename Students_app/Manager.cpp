#include "Manager.h"
#include "Student.h"
#include "Group.h"

UManager::UManager() 
{
	StudentsManager = new UInstanceManager<UStudent>();
	GroupManager = new UInstanceManager<UGroup>();
}
UManager::~UManager()
{
	if (StudentsManager)
		delete StudentsManager;
	if (GroupManager)
		delete GroupManager;
}

UInstanceManager<class UStudent>* UManager::GetStudentsManager() const
{
	return StudentsManager;
}

UInstanceManager<class UGroup>* UManager::GetGroupManager() const
{
	return GroupManager;
}


