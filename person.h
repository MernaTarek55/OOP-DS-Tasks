#pragma once

#include <string>
class Teacher;
class person
{
private:
	std::string name;
	int id;
	//Association
	Teacher* t;
public:
	void setname(std::string name);
	void setid(int id );
	std::string getname();
	int getid();
};

