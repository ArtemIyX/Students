#include "InstanceManager.h"

template<typename T>
UInstanceManager<T>::UInstanceManager() {

}
template<typename T>
UInstanceManager<T>::~UInstanceManager() {
	ClearData();
}

template<typename T>
bool UInstanceManager<T>::AddInstance(T* Instance) {
	if (!Instance) {
		return false;
	}
	if (HasInstance(Instance)) {
		return false;
	}
	Instances.push_back(Instance);
}

template<typename T>
bool UInstanceManager<T>::HasInstance(T* Target) {
	for (T* instance : Instances) {
		if (instance) {
			if (instance == Target) {
				return true;
			}
		}
	}
	return false;
}

template<typename T>
void UInstanceManager<T>::ClearData() {
	const size_t size = Instances.size();
	for (size_t i = 0; i < size; ++i) {
		if (Instances[i]) {
			delete Instances[i];
			Instances[i] = nullptr;
		}
	}
	Instances.clear();
}