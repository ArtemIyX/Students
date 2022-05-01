#pragma once
#include <vector>

class UStudent;
struct FStudent;
class UStudentsManager
{
public:
	UStudentsManager();
protected:
	std::vector<UStudent*> Students;
public:
	bool AddNewStudent(UStudent* student);
	UStudent* CreateAndAddNewStudent(const FStudent& student);
	bool HasStudentInstance(UStudent* student);
};

