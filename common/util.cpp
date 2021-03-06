/*----------------------------------------------------------------
// Copyright (C) 2013 广州，爱游
//
// 模块名：util
// 创建者：Steven Yang
// 修改者列表：
// 创建日期：2013.1.5
// 模块描述：常用函数集合
//----------------------------------------------------------------*/

#include <stdarg.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/time.h>
#include <sys/stat.h>
#endif

#include "util.h"
#include <string>
using namespace std;


int my_isspace(int ch)
{
	return (unsigned int)(ch - 9) < 5u || ch == ' ';
}

std::string Ltrim(string& ss)
{
	std::string::iterator it = ss.begin();
	std::string::iterator end = ss.end();

	while (it != end && my_isspace(*it)) ++it;
	ss.erase(ss.begin(), it);
	return ss;
}


std::string Rtrim(string& ss)
{
	int pos = int(ss.size()) - 1;

	while (pos >= 0 && my_isspace(ss[pos])) --pos;
	ss.resize(pos + 1);

	return ss;
}


bool IsDigitStr(const char* pszStr)
{
	if (pszStr == NULL)
	{
		return false;
	}

	size_t nLen = strlen(pszStr);
	for (size_t i = 0; i < nLen; ++i)
	{
		if (!isdigit(pszStr[i]))
		{
			return false;
		}
	}

	return true;
}


bool IsFileExist(const string& strFileName)
{
	return IsFileExist(strFileName.c_str());
}

bool IsFileExist(const char* pszFileName)
{
	bool bExist = false;

	ifstream iFile(pszFileName, ios::in);
	if (iFile.is_open())
	{
		bExist = true;
		iFile.close();
	}

	return bExist;
}


//替换string中第一次出现的某个部分
string& xReplace(string& s1, const char* pszSrc, const char* pszRep)
{
	string::size_type nPos1 = s1.find(pszSrc);
	if (nPos1 == string::npos)
	{
		return s1;
	}

	s1.replace(nPos1, strlen(pszSrc), pszRep);
	return s1;
}


//判断一个配置文件读取的路径名最后是否带路径分隔符，如果没有则加上
string FormatPathName(const string& strPath)
{
	if (strPath[strPath.size() - 1] == g_cPathSplit[0])
	{
		return strPath;
	}

	string strPath1;
	strPath1.assign(strPath).append(g_cPathSplit);

	return strPath1;
}



//比较一个字符创的大写是否匹配一个大写的字符串
//也可以用strcasecmp
bool UpperStrCmp(const char* src, const char* dest)
{
	if (strlen(src) != strlen(dest))
	{
		return false;
	}
	if (src && dest)
	{
		for (;;)
		{
			char c1 = *src;
			char c2 = *dest;
			if (toupper(c1) == toupper(c2))
			{
				++src;
				++dest;
			}
			else
			{
				return false;
			}
		}
		return true;
	}

	//src和dest任一个为NULL,都认为false
	return false;
}

//按照分隔符nDelim拆分字符串
list<string> SplitString(const string& s1, int nDelim)
{
	list<string> l;

	size_t nSize = s1.size() + 1;
	char* pszTemp = new char[nSize];
	memset(pszTemp, 0, nSize);

	istringstream iss(s1);
	while (iss.getline(pszTemp, (std::streamsize)nSize, nDelim))
	{
		std::string strTemp = std::string(pszTemp);
		if (Rtrim(strTemp).length() > 0)
		{
			l.push_back(pszTemp);
		}
		memset(pszTemp, 0, nSize);
	}

	delete[] pszTemp;
	pszTemp = NULL;

	return l;
}


void SplitString(const string& s1, int nDelim, list<string>& ls)
{
	ls.clear();

	size_t nSize = s1.size() + 1;
	char* pszTemp = new char[nSize];
	memset(pszTemp, 0, nSize);

	istringstream iss(s1);
	while (iss.getline(pszTemp, (std::streamsize)nSize, nDelim))
	{
		std::string strTemp = std::string(pszTemp);
		if (Rtrim(strTemp).length() > 0)
		{
			ls.push_back(pszTemp);
		}
		memset(pszTemp, 0, nSize);
	}

	delete[] pszTemp;
	pszTemp = NULL;

	return;
}

void SplitStringToVector(const string& s1, int nDelim, vector<string>& ls)
{
	ls.clear();

	size_t nSize = s1.size() + 1;
	char* pszTemp = new char[nSize];
	memset(pszTemp, 0, nSize);

	istringstream iss(s1);
	while (iss.getline(pszTemp, (std::streamsize)nSize, nDelim))
	{
		std::string strTemp = std::string(pszTemp);
		if (Rtrim(strTemp).length() > 0)
		{
			ls.push_back(pszTemp);
		}
		memset(pszTemp, 0, nSize);
	}

	delete[] pszTemp;
	pszTemp = NULL;

	return;
}

void SplitStringToMap(const string& s1, int nDelim, char nDelim2, map<string, string>& dict)
{
	dict.clear();

	size_t nSize = s1.size() + 1;
	char* pszTemp = new char[nSize];
	memset(pszTemp, 0, nSize);

	istringstream iss(s1);
	while (iss.getline(pszTemp, (std::streamsize)nSize, nDelim))
	{
		std::string strTemp = std::string(pszTemp);
		if (Rtrim(strTemp).length() > 0)
		{
			string s2(pszTemp);
			string::size_type nn = s2.find(nDelim2);
			if (nn != string::npos)
			{
				dict.insert(make_pair(s2.substr(0, nn), s2.substr(nn + 1)));
			}
		}
		memset(pszTemp, 0, nSize);
	}

	delete[] pszTemp;

	return;
}


void CheckDir(const char* pszDirName, bool bLog /*= false*/)
{
	if (pszDirName == NULL || strlen(pszDirName) == 0)
	{
		cout << "输入目录名称为空!" << endl;
	}

#ifdef _WIN32
	if (_mkdir(pszDirName) == -1)
	{
		if (bLog)
		{
			cout << "检测到存在目录:" << pszDirName << endl;
		}
	}
	else
	{
		cout << "成功创建了目录:" << pszDirName << endl;
	}
#else


	DIR* pDir = opendir(pszDirName);
	if (pDir == NULL)
	{
		cout << "没有这个目录:" << pszDirName << endl;
		if (mkdir(pszDirName, 0777) == 0)
		{
			if (bLog)
			{
				cout << "成功创建了目录:" << pszDirName << endl;
			}
		}
		else
		{
			ThrowException(-1, "创建目录失败");
		}
	}
	else
	{
		closedir(pDir);
		if (bLog)
		{
			cout << "检测到存在目录:" << pszDirName << endl;
		}
	}
#endif
}


#ifdef _WIN32
const char g_cPathSplit[2] = "\\";      //路径分隔符
#else
const char g_cPathSplit[2] = "/";       //路径分隔符
#endif


bool DayDiff(const string& strDayTime, int nClock)
{
	time_t t2;
	{
		int nYear = atoi(strDayTime.substr(0, 4).c_str());
		int nMonth = atoi(strDayTime.substr(4, 2).c_str());
		int nDay = atoi(strDayTime.substr(6, 2).c_str());

		tm dtm;
		dtm.tm_year = nYear - 1900;
		dtm.tm_mon = nMonth - 1;
		dtm.tm_mday = nDay;
		dtm.tm_hour = nClock;
		dtm.tm_isdst = 0;
		dtm.tm_min = 0;
		dtm.tm_sec = 0;
		dtm.tm_wday = 0;
		dtm.tm_yday = 0;

		t2 = mktime(&dtm);
	}

	time_t t1 = time(NULL);

	//int nDayDiff = (int)difftime(t1, t2);
	int nDayDiff = (int)(t1 - t2 - 60 * 60 * 24);

	return nDayDiff >= 0;
}


string GetNextTime(const string& strLastTime)
{
	string strNextTime;

	if (strLastTime.size() != 8)
	{
		return strNextTime;
	}

	int nYear = atoi(strLastTime.substr(0, 4).c_str());
	int nMonth = atoi(strLastTime.substr(4, 2).c_str());
	int nDay = atoi(strLastTime.substr(6, 2).c_str());

	tm dtm;
	dtm.tm_year = nYear - 1900;
	dtm.tm_mon = nMonth - 1;
	dtm.tm_mday = nDay;
	dtm.tm_hour = 0;
	dtm.tm_isdst = 0;
	dtm.tm_min = 0;
	dtm.tm_sec = 0;
	dtm.tm_wday = 0;
	dtm.tm_yday = 0;

	time_t t2 = mktime(&dtm);
	if (t2 < 0)
	{
		return strNextTime;
	}

	t2 += 24 * 60 * 60;
	tm* dtm2 = localtime(&t2);

	char szTemp[9];
	snprintf(szTemp, sizeof(szTemp), "%04d%02d%02d", dtm2->tm_year + 1900, dtm2->tm_mon + 1, dtm2->tm_mday);
	szTemp[8] = '\0';
	strNextTime.assign(szTemp);

	return strNextTime;
}


void GetCurTime(string& strCurTime)
{
	time_t t2 = time(NULL);
	if (t2 < 0)
	{
		strCurTime.clear();
		return;
	}

	tm* dtm2 = localtime(&t2);
	char szTemp[9];
	snprintf(szTemp, sizeof(szTemp), "%04d%02d%02d", dtm2->tm_year + 1900, dtm2->tm_mon + 1, dtm2->tm_mday);
	szTemp[8] = '\0';
	strCurTime.assign(szTemp);

	return;
}


void GetDateTime(char* pszDT, size_t nLen)
{
	time_t t2 = time(NULL);
	if (t2 < 0)
	{
		pszDT[0] = '\0';
		return;
	}

	tm* dtm2 = localtime(&t2);
	memset(pszDT, 0, nLen);
	snprintf(pszDT, nLen, "%04d%02d%02d%02d%02d%02d",
		dtm2->tm_year + 1900, dtm2->tm_mon + 1, dtm2->tm_mday,
		dtm2->tm_hour, dtm2->tm_min, dtm2->tm_sec);

	return;
}


void GetYesterday(string& strYesterday)
{
	time_t t2 = time(NULL);
	if (t2 < 0)
	{
		strYesterday.clear();
		return;
	}

	enum { e_oneday = 24 * 60 * 60 };
	t2 -= e_oneday;
	tm* dtm2 = localtime(&t2);
	char szTemp[9];
	snprintf(szTemp, sizeof(szTemp), "%04d%02d%02d", dtm2->tm_year + 1900, dtm2->tm_mon + 1, dtm2->tm_mday);
	szTemp[8] = '\0';
	strYesterday.assign(szTemp);

	return;
}

uint32_t _GetTickCount()
{
#ifdef _WIN32
	win_time_val_t tv;
	if (win_gettimeofday(&tv) != 0) return 0;
	return tv.tv_sec * 1000 + (tv.tv_usec / 1000);
#else
	struct timeval tv;
	if (gettimeofday(&tv, NULL) != 0) return 0;
	return tv.tv_sec * 1000 + (tv.tv_usec / 1000);
#endif
}

uint64_t _GetTickCount64()
{
#ifndef _WIN32
	struct timeval tv;
	if (gettimeofday(&tv, NULL) != 0) return 0;
	return ((uint64_t)tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
#else
	win_time_val_t tv;
	if (win_gettimeofday(&tv) != 0) return 0;
	return ((uint64_t)tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
#endif
}

bool CheckSpeed(uint16_t speed, uint32_t timeDiff, float dis)
{
	if (dis > speed * timeDiff * 5)
	{
		return false;
	}
	else
	{
		return true;
	}
}

#ifdef _WIN32	
//windows 下实现 linux 的 timeval , 函数的实现
static void get_base_time(LARGE_INTEGER* base_time)
{
	SYSTEMTIME st;
	FILETIME ft;

	memset(&st, 0, sizeof(st));
	st.wYear = 1970;
	st.wMonth = 1;
	st.wDay = 1;
	SystemTimeToFileTime(&st, &ft);

	base_time->LowPart = ft.dwLowDateTime;
	base_time->HighPart = ft.dwHighDateTime;
	base_time->QuadPart /= SECS_TO_FT_MULT;
}

int win_gettimeofday(win_time_val_t* tv)
{
	SYSTEMTIME st;
	FILETIME ft;
	LARGE_INTEGER li;
	static char get_base_time_flag = 0;

	if (get_base_time_flag == 0)
	{
		get_base_time(&base_time);
	}

	/* Standard Win32 GetLocalTime */
	GetLocalTime(&st);
	SystemTimeToFileTime(&st, &ft);

	li.LowPart = ft.dwLowDateTime;
	li.HighPart = ft.dwHighDateTime;
	li.QuadPart /= SECS_TO_FT_MULT;
	li.QuadPart -= base_time.QuadPart;

	tv->tv_sec = li.LowPart;
	tv->tv_usec = st.wMilliseconds;

	return 0;
}

int win_time(const win_time_val_t* tv, win_time_t* time)
{
	LARGE_INTEGER li;
	FILETIME ft;
	SYSTEMTIME st;

	li.QuadPart = tv->tv_sec;
	li.QuadPart += base_time.QuadPart;
	li.QuadPart *= SECS_TO_FT_MULT;

	ft.dwLowDateTime = li.LowPart;
	ft.dwHighDateTime = li.HighPart;
	FileTimeToSystemTime(&ft, &st);

	time->year = st.wYear;
	time->mon = st.wMonth - 1;
	time->day = st.wDay;
	time->wday = st.wDayOfWeek;

	time->hour = st.wHour;
	time->min = st.wMinute;
	time->sec = st.wSecond;
	time->msec = tv->tv_usec;

	return 0;
}


// 下面两个 函数 需要重新实现
CGetTimeOfDay::CGetTimeOfDay()
{
	m_v = new win_time_val_t();
	win_gettimeofday(m_v);
}

CGetTimeOfDay::~CGetTimeOfDay()
{
	delete m_v;
}

void CGetTimeOfDay::SetNowTime()
{
	win_gettimeofday(m_v);
}

int CGetTimeOfDay::GetLapsedTime()
{
	win_time_val_t* v2 = new win_time_val_t;
	win_gettimeofday(v2);
	enum { e_micro_sec = 1000000, };
	int n = (int)((v2->tv_sec - m_v->tv_sec) * e_micro_sec + v2->tv_usec - m_v->tv_usec);

	if (m_v)
	{
		delete m_v;
	}

	m_v = v2;
	return n;
}

//linux下用gettimeofday来计算时间
#else
CGetTimeOfDay::CGetTimeOfDay()
{
	m_v = new struct timeval;
	this->GetTime(m_v);
}

CGetTimeOfDay::~CGetTimeOfDay()
{
	delete m_v;
}

void CGetTimeOfDay::GetTime(struct timeval* tv)
{
	gettimeofday(tv, NULL);
}

void CGetTimeOfDay::SetNowTime()
{
	gettimeofday(m_v, NULL);
}

//获取当前时间和上次的流逝时间
int CGetTimeOfDay::GetLapsedTime()
{
	struct timeval* v2 = new struct timeval;
	this->GetTime(v2);
	enum { e_micro_sec = 1000000, };
	int n = (int)((v2->tv_sec - m_v->tv_sec) * e_micro_sec + v2->tv_usec - m_v->tv_usec);

	if (m_v)
	{
		delete m_v;
	}

	m_v = v2;
	return n;
}
#endif
