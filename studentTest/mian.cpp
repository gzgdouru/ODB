#include "../../StandardLibrary/public/headfile.hpp"
//#include "database.hxx"
#include <odb/mysql/database.hxx>
#include <odb/transaction.hxx>
#include "student.hxx"
#include "student-odb.hxx"
using namespace odb::core;

void printStudent(student &stu)
{
	cout << stu.getId() << " " << stu.getName() << " " << stu.getAge() << endl;
}

// 保存数据
void saveData(shared_ptr<odb::database> db, student& data)
{
	transaction t(db->begin());
	db->persist(data);
	t.commit();
}

// 查询数据
void selectData(shared_ptr<odb::database> db, const string &szCondition, vector<student> &vtStudent)
{
	odb::result<student> r;
	transaction t(db->begin());
	if (szCondition.empty())
	{
		r = db->query<student>();
	}
	else
	{
		r = db->query<student>(szCondition);
	}

	for_each(r.begin(), r.end(), [&vtStudent](student &stu) {
		vtStudent.push_back(stu);
	});
	t.commit();
}

int main(int argc, char *argv[])
{
	try
	{
		// 连接数据库
		shared_ptr<odb::database> db(
			new odb::mysql::database(
				"root",
				"123456",
				"mysql",
				"localhost",
				3306
			)
		);

		student stu1(1, "ouru", 25);
		student stu2(2, "wancaiji", 30);
		student stu3(3, "laopan", 32);

		saveData(db, stu1);
		saveData(db, stu2);
		saveData(db, stu3);

		typedef odb::query<student> query;
		typedef odb::result<student> result;

		// 查询数据
		{
			vector<student> vtStudent;
			selectData(db, "age >= 30", vtStudent);
			for_each(vtStudent.begin(), vtStudent.end(), printStudent);
		}

		// 更新数据
		{
			vector<student> vtStudent;
			selectData(db, "name='laopan'", vtStudent);
			transaction t(db->begin());
			for_each(vtStudent.begin(), vtStudent.end(), [&db](student &stu) {
				stu.setAge(34);
				db->update(stu);
			});
			t.commit();
		}

		{
			transaction t(db->begin());
			student_stat ss(db->query_value<student_stat>());
			cout << ss.count << " " << ss.max_age << " " << ss.min_age << endl;
			t.commit();
		}
		
		// 删除数据
		{
			vector<student> vtStudent;
			selectData(db, "age >= 30", vtStudent);

			transaction t(db->begin());
			for_each(vtStudent.begin(), vtStudent.end(), [&db](student &stu) {
				db->erase<student>(stu.getId());
			});
			t.commit();
		}
	}
	catch (const odb::exception &e)
	{
		cout << e.what() << endl;
	}

	getchar();
	return 0;
}