#pragma once

#include "epoll_server.h"


class CDbMgrServer : public CEpollServer
{
    public:
        CDbMgrServer();
        ~CDbMgrServer();

    protected:
        inline int HandlePluto()
        {
            return 0;
        }

        int HandleSendPluto();

    protected:
        void AddRecvMsg(CPluto* u);

};



