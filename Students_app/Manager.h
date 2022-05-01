#pragma once
#include "InstanceManager.h"

class UManager
{
public:
	UManager();
	~UManager();

protected:
	UInstanceManager<class UStudent>* StudentsManager;
	UInstanceManager<class UGroup>* GroupManager;
protected:
};

