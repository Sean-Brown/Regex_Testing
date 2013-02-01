#include "StdAfx.h"
#include "Logger.h"
#include <boost/logging/format.hpp>
#include <boost/logging/writer/ts_write.hpp>

using namespace bl; // boost::logging, as declared in Aliases.h

// Step 6: [Define] the loggers and filters
BOOST_DEFINE_LOG(g_l, log_type)
BOOST_DEFINE_LOG_FILTER(g_l_filter, level::holder)

void Init_Log_File(void)
{
    // Add formatters and destinations
    // That is, how the message is to be formatted...
    g_l()->writer().add_formatter( formatter::time(_T("[$hh:$mm:$ss] ")) );
    g_l()->writer().add_formatter( formatter::append_newline() );

    // Specify output destinations (i.e. where logs should be written to)
    //g_l()->writer().add_destination( destination::cout() );
    //g_l()->writer().add_destination( destination::dbg_window() );
	g_l()->writer().add_destination( destination::file(MakeLog().GetBuffer()) );
    g_l()->turn_cache_off();
}
