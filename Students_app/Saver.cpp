#include "Saver.h"
#include "Constants.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
void to_json(nlohmann::json& j, const SStudent& s)
{
	j = {
		{"f",
			{
				{"FullName", s.f.FullName},
				{"Age", s.f.Age}
			}},
		{"dep", s.dep},
		{"group", s.group},
		{"id", s.id}
	};
}
void to_json(nlohmann::json& j, const SGroup& s)
{
	j = {
		{"group",
			{
				{"title", s.group.Title}
			}
		},
		{"id", s.id}
	};
}
void to_json(nlohmann::json& j, const SDep& s)
{
	j = {
		{"department",
			{
				{"title", s.department.Title}
			}
		},
		{"id", s.id}
	};
}
USaver::USaver(UManager* manager)
{
	managerRef = manager;
}

void USaver::ReadFile(const std::string& filepath, std::string& buffer)
{
	std::ifstream fin(filepath.c_str());
	getline(fin, buffer, char(-1));
	fin.close();
}

void USaver::WriteFile(const std::string& filepath, std::string& content)
{
	std::ofstream out(filepath);
	out << content;
	out.close();
}

void USaver::Save(int id)
{
	FSaver saver;
	nlohmann::json j;

	std::vector<UDepartment*> departments = managerRef->GetDepartmentManager()->GetAllInstances();
	for (UDepartment* dep : departments) 
	{
		SDep d;
		d.department = dep->GetData();
		d.id = dep->ID;
		saver.Departments.push_back(d);
		j["departments"].push_back(d);
	}
	
	std::vector<UGroup*> groups = managerRef->GetGroupManager()->GetAllInstances();
	for (UGroup* group : groups)
	{
		SGroup g;
		g.group = group->GetData();
		g.id = group->ID;
		j["groups"].push_back(g);
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

		SStudent s;
		s.f = data;
		s.dep = depID;
		s.group = groupID;
		s.id = student->ID;

		j["students"].push_back(s);

		data.Group = group;
		data.Department = dep;
	}

	//std::cout << j;
	std::string content = j.dump();
	WriteFile(Constants::Misc::SavePath, content);
	system("pause");
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
