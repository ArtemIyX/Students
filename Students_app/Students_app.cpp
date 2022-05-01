

#include <iostream>
#include "Application.h"
#include "Entity.h"
//class MyClass
//{
//public:
//	std::vector<int> gg;
//
//};
int main()
{
	UApplication* app = new UApplication();
	app->Run();

	delete app;
	//MyClass a;
	//a.gg = { 1, 2, 3, 4, 5, 6, 7 };
	//std::fstream fout;
	//fout.open("hello.bin", std::ios::out | std::ios::binary);
	//fout.read((char*)&a, sizeof(MyClass));
	////fout.write((char*)&a, sizeof(a));
	//std::cout << a.gg[3];
	//fout.close();
}

