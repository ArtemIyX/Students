#pragma once
#include <vector>
template <typename T>
class UInstanceManager
{
public:
	UInstanceManager();
	~UInstanceManager();

protected:
	std::vector<T*> Instances;
private:
	void ClearData();
public:
	bool AddInstance(T* Instance);
	bool HasInstance(T* Target);
	
};
