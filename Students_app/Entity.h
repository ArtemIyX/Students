#pragma once

class UEntity
{
private:

public:
	int ID;
	static int ID_Counter;
	static int GetNextID();
};

