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

#ifndef IXPELOGGER_H
#define IXPELOGGER_H

/// We need this line to link dynamically the boost log libraries
#define BOOST_LOG_DYN_LINK 1

#include <ostream>
#include <string>
#include <vector>

#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/severity_feature.hpp>


/// We define our own severity levels
enum severity_level
{
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

/// The operator << puts a human-friendly representation of the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream<CharT, TraitsT>& operator<< (
    std::basic_ostream<CharT, TraitsT>& strm, severity_level level)
{
    static const std::vector<std::string> strings =
    {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR",
        "CRITICAL"
    };
    if (static_cast<std::size_t>(level) < strings.size())
        strm << strings.at(level);
    else
        strm << static_cast<int>(level);
    return strm;
}

/// Our logger type is a thread-safe logger with custom severity level
typedef boost::log::sources::severity_logger_mt<severity_level> logger_t;

/// Declares our global logger
BOOST_LOG_GLOBAL_LOGGER(ixpeLogger, logger_t);

/// Logger targets (console, file(s)) initialization
void loggerInit(std::string filePath, severity_level minSeverityLevel =INFO);

/// Convenience macros (these are the ones we will actually use in the code)
#define LOG_DEBUG     BOOST_LOG_SEV(ixpeLogger::get(), DEBUG)
#define LOG_INFO      BOOST_LOG_SEV(ixpeLogger::get(), INFO)
#define LOG_WARN      BOOST_LOG_SEV(ixpeLogger::get(), WARNING)
#define LOG_ERROR     BOOST_LOG_SEV(ixpeLogger::get(), ERROR)
#define LOG_CRITICAL  BOOST_LOG_SEV(ixpeLogger::get(), CRITICAL)

#endif //IXPELOGGER_H
