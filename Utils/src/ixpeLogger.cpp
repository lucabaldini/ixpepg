/***********************************************************************
Copyright (C) 2017 the Imaging X-ray Polarimetry Explorer (IXPE) team.

For the license terms see the file LICENSE, distributed along with this
software.

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
***********************************************************************/

#include "ixpeLogger.h"

#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/formatter_parser.hpp>


/// Aliases for a few useful namespaces
namespace expr    = boost::log::expressions;
namespace sinks   = boost::log::sinks;
namespace logging = boost::log;


/// Default logger construction
BOOST_LOG_GLOBAL_LOGGER_DEFAULT(ixpeLogger, logger_t);

/// Initialization of the logger targets (console, file(s))
void loggerInit(std::string filePath, severity_level minSeverityLevel)
{
  /// Register our custom severity attribute
  boost::log::register_simple_formatter_factory<
                                           severity_level, char>("Severity");

  
  /// Out-of-the box convenience function provided by boost to register two
  /// common used attributes ("LineID" and "TimeStamp") so that they are
  /// available for every logger
  logging::add_common_attributes();

  /// Define the format of our log messages
  logging::formatter formatter = expr::stream
    << expr::attr<unsigned int>("LineID") << ": "
    << expr::format_date_time<boost::posix_time::ptime>
       ("TimeStamp", "%Y-%m-%d %H:%M:%S")
    << " *"
    << expr::attr<severity_level>("Severity")
    << "* "
    << expr::message;
  
  /// Define an handy alias for the console sink
  typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink_t;
  /// Initialize logging console
  boost::shared_ptr<text_sink_t> consoleSink = logging::add_console_log();
  /// Set the format for the console log
  consoleSink->set_formatter(formatter);
  /// Set the minimum severity level for console messages
  consoleSink->set_filter(expr::attr<severity_level>("Severity") >=
                                                           minSeverityLevel);
  /// Activate the auto-flush (we want stuff printed in the console as quickly
  /// as possible)
  consoleSink->locked_backend()->auto_flush(true);
  
  /// Define an handy alias for the file sink
  typedef sinks::synchronous_sink<sinks::text_file_backend> file_sink_t;
  /// Initialize logging to file with the same format
  boost::shared_ptr<file_sink_t> fileSink = logging::add_file_log(filePath);
  /// Set file log format
  fileSink->set_formatter(formatter);
  /// Set the minimum severity level for console messages
  fileSink->set_filter(expr::attr<severity_level>("Severity") >=
                                                            minSeverityLevel);
}
