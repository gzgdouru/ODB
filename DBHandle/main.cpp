#include "DBHandle.hpp"

#include <odb/transaction.hxx>
#include "student.hxx"
#include "student-odb.hxx"
using namespace odb::core;

int main(int argc, char *argv[])
{
	SDBConnectParam params;
	params.szUser = "root";
	params.szPasswd = "123456";
	params.szDBName = "mysql";
	params.szIp = "localhost";
	params.iPort = 3306;
	params.iConnectNum = 20;
	CDBHandle::getInstance()->setDBParams(params);

	shared_ptr<odb::database> db = CDBHandle::getInstance()->getDB();
	{
		vector<string> vtStr;
		/*vtStr.push_back("aiji");
		vtStr.push_back("ouru");*/
		try
		{
			transaction t(db->begin());
			odb::result<student> r = db->query<student>(query<student>::name.in_range(vtStr.begin(), vtStr.end()));
			for_each(r.begin(), r.end(), [](student &stu) {
				cout << stu.getId() << " " << stu.getName() << " " << stu.getAge() << endl;
			});
			t.commit();
		}
		catch (odb::exception &e)
		{
			cout << e.what() << endl;
		}
	}

	return 0;
}