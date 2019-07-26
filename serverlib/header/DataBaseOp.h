/*
	author: Macro Gu
	email: macrogu@qq.com
	QQ: 877188891
	des: mysql ²Ù×÷Àà·â×°
*/

#pragma once

#include <sstream>
#include <queue>
#include <mutex>
#include <thread>
#include <string>

#ifdef _WIN32
#include<winsock2.h>
#endif
#include <mysql.h>
#include "ServerConf.h"
#include "singleton.h"



struct stStoreMachineData
{
	uint16_t DataType;
	std::string clientKey;
	unsigned int memoryLimit;   // percentage
	unsigned int cpuLimit;      // percentage
	unsigned int processesLimit;

	stStoreMachineData()
	{
		DataType = TEST_DATA_TYPE;
		clientKey = "";
		memoryLimit = 0;
		cpuLimit = 0;
		processesLimit = 0;
	}
};



class DataBaseOp : public ISingleton<DataBaseOp>
{
public:
	~DataBaseOp();

	// push need store data to DB queue
	void PushBackToDbQueue(const stStoreMachineData& needStoreData);

protected:
	//insert data to DB
	bool InserDataToDB(const std::string& clientKey, const unsigned int& memory,
		const unsigned int& cpu, const unsigned int& processes);

	void DisConnect();

	void threadStoreDatabase();


public:
	bool ConnectMysql();

	bool Init();


private:
	friend ISingleton<DataBaseOp>;
	friend class std::unique_ptr<DataBaseOp>;
	DataBaseOp();



private:
	MYSQL* MysqlHandle;
	std::shared_ptr<stMysqlInfo> MysqlInfo;
	bool bConnectingStatus;

	std::thread* StoreMachineData;

	std::queue<stStoreMachineData> qAllNeedStoreData;
	std::mutex databaseMutex;

};


