#include <iostream>
#include "DataBaseOp.h"





DataBaseOp::DataBaseOp()
{
	bConnectingStatus = false;
	MysqlHandle = mysql_init(NULL);

}

DataBaseOp::~DataBaseOp()
{
	DisConnect();
	StoreMachineData->join();
	delete StoreMachineData;

}

void DataBaseOp::PushBackToDbQueue(const stStoreMachineData& needStoreData)
{
	databaseMutex.lock();
	qAllNeedStoreData.push(needStoreData);
	databaseMutex.unlock();
}

bool DataBaseOp::InserDataToDB(const std::string& clientKey, const unsigned int& memory, const unsigned int& cpu, const unsigned int& processes)
{
	std::ostringstream inserSql;
	inserSql << "INSERT INTO `guhong_test`.`collections` (`clientkey`, `memory`, `cpu`,`processes`) VALUES (\""
		<< clientKey << "\"" << ',' << memory << ',' << cpu << ',' << processes << ")";


	std::string cInsertSql;
	cInsertSql.assign(inserSql.str());
	int nRet = mysql_real_query(MysqlHandle, cInsertSql.c_str(), (unsigned long)cInsertSql.size());
	if (nRet != 0)
	{
		LOG_ERROR("execuse insert sql error , reason: {}", mysql_error(MysqlHandle));
		return false;
	}

	return true;

}

void DataBaseOp::DisConnect()
{
	if (!MysqlHandle)
	{
		mysql_close(MysqlHandle);
	}
}

void DataBaseOp::threadStoreDatabase()
{

}

bool DataBaseOp::ConnectMysql()
{
	int ml_outtime = 10;
	mysql_options(MysqlHandle, MYSQL_OPT_CONNECT_TIMEOUT, &ml_outtime);
	std::string errorStr;

	do 
	{
		if (0 != mysql_options(MysqlHandle, MYSQL_SET_CHARSET_NAME, "utf8"))//ÉèÖÃ×Ö·û¼¯utf8
		{
			bConnectingStatus = false;
			break;
		}

		if (mysql_real_connect(MysqlHandle, MysqlInfo->IpHost.c_str(), MysqlInfo->UserName.c_str(), 
			MysqlInfo->Password.c_str(), MysqlInfo->DBName.c_str(), MysqlInfo->port, NULL, 0) == NULL)
		{
			bConnectingStatus = false;
			break;
		}

		std::string strSql = "set interactive_timeout=24*3600";
		if (0 != mysql_real_query(MysqlHandle, strSql.c_str(), (unsigned long)strSql.size()))
		{
			bConnectingStatus = false;
		}

		bConnectingStatus = true;
	} while (false);

	if (!bConnectingStatus)
	{
		std::cout << "connect to mysql failed!, reason: " << mysql_error(MysqlHandle) << std::endl;
		return false;
	}

	return true;
}

bool DataBaseOp::Init()
{
	MysqlInfo = ServerConf::GetInstance().GetMysqlInfo();

	if (!MysqlInfo)
	{
		std::cout << __FUNCTION__ << " : " << __LINE__ << "  get Mysql info failed!" << std::endl;
		return false;
	}

	if (!ConnectMysql())
	{
		std::cout << __FUNCTION__ << " : " << __LINE__ << "  connect to Mysql failed!" << std::endl;
		return false;
	}


	return true;
}

