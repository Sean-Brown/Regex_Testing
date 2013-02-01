// Based partially on the example provided by John Torjo
#pragma once

#include <boost/logging/format_fwd.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "Aliases.h"

#ifndef LOG_H_header
#define LOG_H_header

// Optimize : use a cache string, to make formatting the message faster
BOOST_LOG_FORMAT_MSG( bl::optimize::cache_string_one_str<> ) 

#ifndef BOOST_LOG_COMPILE_FAST
#include <boost/logging/format.hpp>
#include <boost/logging/writer/ts_write.hpp>
#endif

// Specify logging class(es)
typedef bl::logger_format_write< > log_type;

// [Declare] which loggers and filters to use
BOOST_DECLARE_LOG(g_l, log_type) // Declare the logger as "g_l", which will be "global_logger"
BOOST_DECLARE_LOG_FILTER(g_l_filter, bl::level::holder)

// Define the macros through which to log
#define LDBG_ BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_filter(), debug) << _T("[Debug] ")
#define LERR_ BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_filter(), error) << _T("[Error] ")
#define LINF_ BOOST_LOG_USE_LOG_IF_LEVEL(g_l(), g_l_filter(), info) << _T("[Info] ")


// TODO: Flesh out the logging class. Include convenience macros for decreasing code verbosity
//#define LOG_INFO(_msg) LINF_ << _msg

void Init_Log_File(void);

static CString MakeLog(void)
{
	SYSTEMTIME tNow;
	GetSystemTime(&tNow);
	CString strDate;
	strDate.Format(_T("%.2d-%.2d-%.4d_at_[%.2d-%.2dm-%.2ds]"), tNow.wMonth, tNow.wDay, tNow.wYear, tNow.wHour, tNow.wMinute, tNow.wSecond);
	strDate.Append(_T("_log.txt"));
	return strDate;
}

#endif


