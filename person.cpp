#include "person.h"

void person::setname(std::string name)
{
	this->name = name;
}

void person::setid(int id)
{
	this->id = id;
}

std::string person::getname()
{
	return this->name;
}

int person::getid()
{
	return this->id;
}
