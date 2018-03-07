#include "DBHandle.hpp"

CDBHandle* CDBHandle::m_instance = nullptr;

CDBHandle::CDBHandle()
{

}

CDBHandle::~CDBHandle()
{

}

CDBHandle* CDBHandle::getInstance()
{
	if (m_instance)
	{
		return m_instance;
	}

	m_instance = new CDBHandle();
	return m_instance;
}

void CDBHandle::setDBParams(const SDBConnectParam &params)
{
	m_factory = auto_ptr<odb::mysql::connection_factory>(new odb::mysql::connection_pool_factory(params.iConnectNum, 1));
	m_db.reset(new odb::mysql::database(params.szUser.c_str(), params.szPasswd.c_str(), params.szDBName.c_str(), params.szIp.c_str(), params.iPort, 
		0, "", 0, m_factory));
}
