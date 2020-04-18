#include <signal.h>
#include "dbmgr.h"
#include "world_dbmgr.h"
#include "db_task.h"
#include "world_select.h"
#include "debug.h"

///////////////////////////////////////////////////////////////////////////

world* g_pTheWorld = new CWorldDbmgr;
CWorldDbmgr& g_worldDbmgr = (CWorldDbmgr&)(*g_pTheWorld);

void* RunDbTask(void* arg)
{
    int nSeq = *(int*)arg;      //每个线程编一个流水号
    //printf("runDbTask,seq=%d\n", nSeq);

    mysql_thread_init();
    CDbTask t(g_worldDbmgr, nSeq);

    string strErr;
    if(!t.ConnectDB(GetWorld()->GetDefParser().GetDbCfg(), GetWorld()->GetDefParser().GetRedisCfg(), strErr))
    {
        LogDebug("CWorldDbmgr::init().error", "connect db:%s", strErr.c_str());
        mysql_thread_end();
        return NULL;
    }

    t.Run();
    mysql_thread_end();
    return NULL;
}

int main(int argc, char* argv[])
{
    if(argc < 4)
    {
        printf("Usage:%s etc_fn server_id log_fn\n", argv[0]);
        return -1;
    }

    //命令行参数,依次为: 配置文件路径,server_id,日志文件路径名
    const char* pszEtcFn = argv[1];
    uint16_t nServerId = (uint16_t)atoi(argv[2]);
    const char* pszLogPath = argv[3];
#ifndef _WIN32
	signal(SIGPIPE, SIG_IGN);
#endif
    CDebug::Init();

    //printf("%d\n", mysql_thread_safe() );
    {
        MYSQL* dummy = mysql_init(NULL);
        mysql_close(dummy);
    }

    g_logger_mutex = new std::mutex;

    if(!g_pluto_recvlist.InitMutex() || !g_pluto_sendlist.InitMutex() || !g_worldDbmgr.InitMutex() )
    {
        printf("pthead_mutext_t init error:%d,%s\n", errno, strerror(errno));
        return -1;
    }

    g_logger.SetLogPath(pszLogPath);
    CWorldDbmgr& world = g_worldDbmgr;
    int nRet = world.init(pszEtcFn);
    if(nRet != 0)
    {
        printf("CWorldDbmgr init error:%d\n", nRet);
        return nRet;
    }

    CDbMgrServer s;
    s.SetMailboxId(nServerId);
    s.SetWorld(&world);
    world.SetServer(&s);

    vector<std::thread> pid_list;
    {
        for(int i=0; i<4; ++i)
        {
            int* ii = new int(i);
            pid_list.push_back(std::thread(RunDbTask, ii));
            //delete ii;
        }
    }

    uint16_t unPort = world.GetServerPort(nServerId);
    s.Service("", unPort);

    for(size_t i = 0; i < pid_list.size(); ++i)
    {
        pid_list[i].join();
    }

}
