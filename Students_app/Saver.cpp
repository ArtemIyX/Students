#include "Saver.h"
#include "Constants.h"
#include <fstream>
#include <iostream>

USaver::USaver(UManager* manager)
{
	managerRef = manager;
}

void USaver::Save(int id)
{
	FSaver saver;
	saver.Counter = id;

	std::vector<UDepartment*> departments = managerRef->GetDepartmentManager()->GetAllInstances();
	for (UDepartment* dep : departments) 
	{
		SDep d;
		d.f = dep->GetData();
		d.id = dep->ID;
		saver.Departments.push_back(d);
	}
	
	std::vector<UGroup*> groups = managerRef->GetGroupManager()->GetAllInstances();
	for (UGroup* group : groups)
	{
		SGroup g;
		g.group = group->GetData();
		g.id = group->ID;
		saver.Groups.push_back(g);
	}

	std::vector<UStudent*> students = managerRef->GetStudentsManager()->GetAllInstances();

	for (UStudent* student : students)
	{
		FStudent& data = student->GetData();
		UGroup* group = data.Group;
		UDepartment* dep = data.Department;

		int groupID = group->ID;
		int depID = dep->ID;

		data.Group = nullptr;
		data.Department = nullptr;

		SStudent save;
		save.f = data;
		save.dep = depID;
		save.group = groupID;
		save.id = student->ID;

		saver.Students.push_back(save);

		data.Group = group;
		data.Department = dep;
	}

	std::ofstream fout;
	fout.open(Constants::Misc::SavePath, std::ios::binary);
	fout.write((char*)&saver, sizeof(saver));
	fout.close();
}

int USaver::Load()
{
	FSaver saver;
	std::ifstream fin;
	fin.open(Constants::Misc::SavePath, std::ios::binary);
	fin.read((char*)&saver, sizeof(FSaver));
	fin.close();
	std::cout << saver.Groups[0].group.Title;
	system("Pause");
	return 1;
}
