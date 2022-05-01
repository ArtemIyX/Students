#pragma once
#include <vector>
struct FMenuFunction;
class UMenuPosition
{
public:
	UMenuPosition(const std::vector<FMenuFunction>& Functions);
protected:
	std::vector<FMenuFunction> Functions;
public:
	const std::vector<FMenuFunction>& GetFunctions() const;
};

