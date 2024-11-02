#pragma once
#include <string>
#include "Teacher.h"
#include <vector>
class Department
{
public:
	std::string name;
	//Aggregation
	std::vector <Teacher> Teachers;
	
};

