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
void from_json(const nlohmann::json& j, SStudent& s)
{
	j.at("dep").get_to(s.dep);
	j.at("group").get_to(s.group);
	j.at("id").get_to(s.id);
	j.at("f").at("FullName").get_to(s.f.FullName);
	j.at("f").at("Age").get_to(s.f.Age);
}
void to_json(nlohmann::json& j, const SGroup& s)
{
	/*j = {
			{"group",
				{
					{"title", s.group.Title}
				},
			{"id", s.id}
		}
	};*/
	j = {
		{"groupTitle", s.group.Title},
		{"id", s.id}
	};
}
void from_json(const nlohmann::json& j, SGroup& s)
{
	j.at("id").get_to(s.id);
	j.at("groupTitle").get_to(s.group.Title);
}
void to_json(nlohmann::json& j, const SDep& s)
{
	/*j = {
		{"department",
			{
				{"title", s.department.Title}
			}
		},
		{"id", s.id}
	};*/
	j = {
		{"departmentTitle", s.department.Title},
		{"id", s.id}
	};
}
void from_json(const nlohmann::json& j, SDep& s)
{
	j.at("id").get_to(s.id);
	j.at("departmentTitle").get_to(s.department.Title);
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

UGroup* USaver::FindGroupById(int id)
{
	auto groups = managerRef->GetGroupManager()->GetAllInstances();
	for (auto group : groups)
	{
		if (group->ID == id)
		{
			return group;
		}
	}
	return nullptr;
}

UDepartment* USaver::FindDepartmentById(int id)
{
	auto departments = managerRef->GetDepartmentManager()->GetAllInstances();
	for (auto dep : departments)
	{
		if (dep->ID == id)
		{
			return dep;
		}
	}
	return nullptr;
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
		j[FieldNames::F_Departments].push_back(d);
	}

	std::vector<UGroup*> groups = managerRef->GetGroupManager()->GetAllInstances();
	for (UGroup* group : groups)
	{
		SGroup g;
		g.group = group->GetData();
		g.id = group->ID;
		j[FieldNames::F_Groups].push_back(g);
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

		j[FieldNames::F_Students].push_back(s);

		data.Group = group;
		data.Department = dep;
	}
	j[FieldNames::F_Counter] = id;
	//std::cout << j;
	std::string content = j.dump();
	WriteFile(Constants::Misc::SavePath, content);
	//system("pause");
	//TODO: Message
}

int USaver::Load()
{
	std::string content;
	ReadFile(Constants::Misc::SavePath, content);
	nlohmann::json j1 = nlohmann::json::parse(content);

	auto departments = j1[FieldNames::F_Departments].get<std::vector<SDep>>();
	auto groups = j1[FieldNames::F_Groups].get<std::vector<SGroup>>();
	auto students = j1[FieldNames::F_Students].get<std::vector<SStudent>>();
	int counter = j1[FieldNames::F_Counter].get<int>();

	for (auto& dep : departments)
	{
		managerRef->GetDepartmentManager()->AddInstance(UDepartment::CreateDepartment(dep.department, dep.id));
	}
	for (auto& group : groups)
	{
		managerRef->GetGroupManager()->AddInstance(UGroup::CreateGroup(group.group, group.id));
	}
	for (auto& student : students)
	{
		FStudent data;
		data.FullName = student.f.FullName;
		data.Age = student.f.Age;
		data.Group = FindGroupById(student.group);
		data.Department = FindDepartmentById(student.dep);
		managerRef->GetStudentsManager()->AddInstance(UStudent::CreateStudent(data, student.id));
	}
	return counter;
}
