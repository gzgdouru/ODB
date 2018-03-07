#ifndef _STUDENT_HXX
#define _STUDENT_HXX

#include <odb/core.hxx>
#include <string>
using namespace std;

#pragma db object
class student
{
public:
	student(int iId, const string &szName, int iAge) :
		id(iId), name(szName), age(iAge)
	{

	}

	int getId()
	{
		return id;
	}

	string getName()
	{
		return name;
	}

	int getAge()
	{
		return age;
	}

	void setAge(int iAge)
	{
		age = iAge;
	}

private:
	friend class odb::access;
	student() {}
#pragma db id auto
	int	id;
	string name;
	int age;
};

#pragma db view object(student)
struct student_stat
{
#pragma db column("count(" + student::id + ")")
	size_t count;
#pragma db column("max(" + student::age + ")")
	int max_age;
#pragma db column("min(" + student::age + ")")
	int min_age;
};

#endif
