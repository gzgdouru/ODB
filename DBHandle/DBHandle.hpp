#ifndef _DBHANDLE_HPP
#define _DBHANDLE_HPP

#include <odb/mysql/database.hxx>
#include "../../StandardLibrary/public/headfile.hpp"

struct SDBConnectParam 
{
	string szIp;
	string szDBName;
	string szUser;
	string szPasswd;
	int iPort;
	int iConnectNum = 3;
};

class CDBHandle
{
public:
	static CDBHandle* getInstance();
	void setDBParams(const SDBConnectParam &params);
	shared_ptr<odb::database>  getDB()
	{
		return m_db;
	}
	~CDBHandle();
private:
	CDBHandle();
	static CDBHandle *m_instance;
	shared_ptr<odb::database> m_db;
	auto_ptr<odb::mysql::connection_factory> m_factory;
};

#endif