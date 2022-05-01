#include "StudentsManager.h"
#include "Student.h"
#include <algorithm>
UStudentsManager::UStudentsManager()
{
}

bool UStudentsManager::AddNewStudent(UStudent* StudentInstance)
{
	if (!StudentInstance) {
		return false;
	}
	if (HasStudentInstance(StudentInstance)) {
		return false;
	}
	Students.push_back(StudentInstance);
	return true;
}

UStudent* UStudentsManager::CreateAndAddNewStudent(const FStudent& StudentData)
{
	UStudent* object = UStudent::CreateStudent(StudentData);
	bool add = AddNewStudent(object);
	if (!add) {
		delete object;
	}
}

bool UStudentsManager::HasStudentInstance(UStudent* student)
{
	//return std::find(std::begin(Students), std::end(Students), Students) != std::end(Students);
	for (UStudent* st : Students) {
		if (st) {
			if (st == student) {
				return true;
			}
		}
	}
	return false;
}
