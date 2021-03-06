#pragma once
#include <vector>

template <typename T>
class UInstanceManager
{
public:
	UInstanceManager() {}
	~UInstanceManager()
	{
		ClearData();
	}

protected:
	std::vector<T*> Instances;
private:
	void ClearData()
	{
		const size_t size = Instances.size();
		for (size_t i = 0; i < size; ++i)
		{
			if (Instances[i])
			{
				delete Instances[i];
				Instances[i] = nullptr;
			}
		}
		Instances.clear();
	}
public:
	bool AddInstance(T* Instance)
	{
		if (!Instance) {
			return false;
		}
		if (HasInstance(Instance))
		{
			return false;
		}
		Instances.push_back(Instance);
		return true;
	}

	bool HasInstance(T* Target)
	{
		for (T* instance : Instances)
		{
			if (instance)
			{
				if (instance == Target)
				{
					return true;
				}
			}
		}
		return false;
	}
	
	void RemoveInstance(T* target)
	{
		size_t index = 0;
		for (size_t i = 0; i < Instances.size(); ++i) 
		{
			if (Instances[i] == target) {
				RemoveInstanceAt(i);
				return;
			}
		}
	}

	void RemoveInstanceAt(size_t index) 
	{
		delete Instances[index];
		Instances[index] = nullptr;
		Instances.erase(std::begin(Instances) + index);
	}

	const std::vector<T*>& GetAllInstances() const
	{
		return Instances;
	}

	T* GetInstance(size_t index) const
	{
		return Instances[index];
	}
	void Clear()
	{
		for (size_t i = 0; i < Instances.size(); ++i)
		{
			delete Instances[i];
			Instances[i] = nullptr;
		}
		Instances.clear();
	}
};
