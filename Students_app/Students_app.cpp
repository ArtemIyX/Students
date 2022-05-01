

#include <iostream>
#include "Application.h"

int main()
{
	UApplication* app = new UApplication();
	app->Run();

	delete app;
}

