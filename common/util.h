#ifndef __UTIL__HEAD__
#define __UTIL__HEAD__


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <list>
#include <mutex>
#include "exception.h"

#ifdef _WIN32
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#define strcasecmp(a,b) strcmp(a,b)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <time.h>
#else
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/time.h>
#endif

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::ios;
using std::list;


using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::ios;
using std::list;


extern string& Ltrim(string& s);
extern string& Rtrim(string& s);

inline string& Trim(string& s)
{
	return Rtrim(Ltrim(s));
}

//删除字符串左边的空格
extern char* Ltrim(char* p);

//删除字符串右边的空格
extern char* Rtrim(char* p);

//删除字符串两边的空格
inline char* Trim(char* s)
{
	return Rtrim(Ltrim(s));
}

//比较一个字符串的大写是否匹配一个大写的字符串
extern bool UpperStrCmp(const char* src, const char* desc);

//按照分隔符nDelim拆分字符串
extern list<string> SplitString(const string& s1, int nDelim);
extern void SplitString(const string& s1, int nDelim, list<string>& ls);
extern void SplitStringToVector(const string& s1, int nDelim, vector<string>& ls);
extern void SplitStringToMap(const string& s1, int nDelim1, char nDelim2, map<string, string>& dict);

//替换string中第一次出现的某个部分
extern string& xReplace(string& s1, const char* pszSrc, const char* pszRep);

//判断一个字符串是否全部由数字字符组成
extern bool IsDigitStr(const char* pszStr);

//测试文件strFileName是否存在
extern bool IsFileExist(const char* pszFileName);
extern bool IsFileExist(const string& strFileName);

//检查一个目录是否存在，如果不存在则创建
extern void CheckDir(const char* pszDirName, bool bLog = false);

//判断一个配置文件读取的路径名最后是否带路径分隔符，如果没有则加上
extern string FormatPathName(const string& strPath);

#define FORMATPATHNAME(x) { x = formatPathName(x);}


//用于清理一个指针容器
template <typename TP,
	template <typename ELEM,
	typename ALLOC = std::allocator<ELEM>
	> class TC
>
void ClearContainer(TC<TP, std::allocator<TP> > & c1)
{
	while (!c1.empty())
	{
		typename TC<TP>::iterator iter = c1.begin();
		delete* iter;
		*iter = NULL;
		c1.erase(iter);
	}
}

//用于清理一个map,第二个类型为指针
template<typename T1, typename T2,
	template <class _Kty,
	class _Ty,
	class _Pr = std::less<_Kty>,
	class _Alloc = std::allocator<std::pair<const _Kty, _Ty> >
	> class M
>
void ClearMap(M<T1, T2, std::less<T1>, std::allocator<std::pair<const T1, T2> > >& c1)
{
	typename M<T1, T2>::iterator iter = c1.begin();
	for (; iter != c1.end(); ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}
	c1.clear();
}

//template<typename T1, typename T2>
//void clearMap(unordered_multimap<T1, T2>& c1)
//{
//  typename unordered_multimap<T1, T2>::iterator iter = c1.begin();
//  for(; iter!=c1.end(); ++iter)
//  {
//      delete iter->second;
//      iter->second = NULL;
//  }
//  c1.clear();
//}


extern const char g_cPathSplit[2];  //路径分隔符

//传入指定的速度、时间段、移动距离，校验玩家移动是否被允许
#ifndef _WIN32
bool CheckSpeed(uint16_t speed, uint32_t timeDiff, float dis);
#endif

extern void GetCurTime(string& strCurTime);
extern string GetNextTime(const string& strLastTime);
extern void GetYesterday(string& strYesterday);
extern bool DayDiff(const string& strDayTime, int nClock);
extern void GetDateTime(char* pszDT, size_t nLen);
#ifndef _WIN32
extern uint32_t _GetTickCount();
extern uint64_t _GetTickCount64();
#else	
inline long _GetTickCount64()
{
	return 0;
}
#endif



#ifndef _WIN32	
//linux下用gettimeofday来计算时间
class CGetTimeOfDay
{
public:
	CGetTimeOfDay();
	~CGetTimeOfDay();

private:
	void GetTime(struct timeval* tv);

public:
	//获取当前时间和上次的流逝时间
	int GetLapsedTime();
	void SetNowTime();

private:
	struct timeval* m_v;

};
#else
//windows 下实现 linux 的 timeval
#define SECS_TO_FT_MULT 10000000
static LARGE_INTEGER base_time;
typedef struct win_time_val
{
	/** The seconds part of the time. */
	long    tv_sec;			//long    sec;

	/** The miliseconds fraction of the time. */
	long    tv_usec;			//long    msec;

} win_time_val_t;

typedef struct win_time
{
	/** This represents day of week where value zero means Sunday */
	int wday;

	/** This represents day of month: 1-31 */
	int day;

	/** This represents month, with the value is 0 - 11 (zero is January) */
	int mon;

	/** This represent the actual year (unlike in ANSI libc where
	*  the value must be added by 1900).
	*/
	int year;

	/** This represents the second part, with the value is 0-59 */
	int sec;

	/** This represents the minute part, with the value is: 0-59 */
	int min;

	/** This represents the hour part, with the value is 0-23 */
	int hour;

	/** This represents the milisecond part, with the value is 0-999 */
	int msec;

}win_time_t;

// Find 1st Jan 1970 as a FILETIME 
static void get_base_time(LARGE_INTEGER* base_time);

int win_gettimeofday(win_time_val_t* tv);

int win_time(const win_time_val_t* tv, win_time_t* time);

// windows 下实现 gettimeofday
class CGetTimeOfDay
{
public:
	CGetTimeOfDay();
	~CGetTimeOfDay();

public:
	//获取当前时间和上次的流逝时间
	int GetLapsedTime();
	void SetNowTime();
	win_time_val_t* m_v;
};

#endif

class MyLock
{
	std::mutex m_Mutex;
public:
	MyLock() {  };
	~MyLock() {  };
	void Lock() { m_Mutex.lock(); };
	void Unlock() { m_Mutex.unlock(); };
};
#endif		//__UTIL__HEAD__
