#pragma once

#include <list>
#include <mutex>


class CMutexGuard
{
    public:
        CMutexGuard(std::mutex& m);
        ~CMutexGuard();

    private:
        std::mutex& mm;

};


