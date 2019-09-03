#ifndef __DB_TASK_HEAD__
#define __DB_TASK_HEAD__

#include <list>
#include<string>
#include "mutex.h"

#include <pthread.h>

#include "dboper.h"
using namespace std;


class CWorldOther;


extern CWorldOther& g_worldOther;
extern bool g_bShutdown;
extern int reqUrl(const char* url);
extern int runRul(string& url, char* key);
extern CPlutoList g_pluto_recvlist;
extern CPlutoList g_pluto_sendlist;



class CDbTask
{
public:
	CDbTask(CWorldOther& w, int seq);
	~CDbTask();

public:
	void Run();
	//连接数据库
	bool Init(const SDBCfg& cfg, string& strErr);
	bool UnInit();


private:
	CWorldOther& m_world;
	CDbOper m_db;

};

// class CHttp
// {
// public:
// 	CHttp(CWorldOther& w, int seq );
// 	~CHttp();
// 
// public:
// 	void Run();
// 
// 	bool Init(const SDBCfg& cfg, string& strErr);
// 	bool UnInit();
// 
// private:
// 	CWorldOther& m_world;
// 	CDbOper m_db;
// 
// };

#endif		// __DB_TASK_HEAD__

