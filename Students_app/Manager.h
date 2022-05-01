#pragma once
#include "InstanceManager.h"
class UStudent;
class UGroup;

class UManager
{
public:
	UManager();
	~UManager();

protected:
	UInstanceManager<class UStudent>* StudentsManager;
	UInstanceManager<class UGroup>* GroupManager;
public:
	UInstanceManager<class UStudent>* GetStudentsManager() const;
	UInstanceManager<class UGroup>* GetGroupManager() const;
};

