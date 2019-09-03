#ifndef __MYREDIS_HEAD__
#define __MYREDIS_HEAD__

#include <hiredis/hiredis.h>

#include "pluto.h"
#include "logger.h"

    class CRedisUtil
    {
        public:
            CRedisUtil();
            ~CRedisUtil();

        public:
            bool Connect(const char* pszAddr, int nPort, int nDbId);
            void DisConnect();
            void DisConnectAndBgSave();

        public:
            int UpdateEntity(const string& strEntity, const map<string, VOBJECT*>& props, TDBID dbid);

        public:
            void RedisHashLoad(const string& strKey, string& strValue);
            void RedisHashSet(const string& strKey, int32_t nSeq, const string& strValue);
            void RedisHashDel(const string& strKey, int32_t nSeq);

        private:
            struct redisContext* m_redis;

    };

#endif		// __MYREDIS_HEAD__

