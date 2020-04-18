#include "mutex.h"


CMutexGuard::CMutexGuard(std::mutex& m):mm(m)
{
	mm.lock();
}

CMutexGuard::~CMutexGuard()
{
	mm.unlock();
}
