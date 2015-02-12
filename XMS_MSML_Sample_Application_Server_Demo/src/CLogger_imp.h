///////////////////////////////////////////////////////////////////////////////
//
// Copyright © 2006-2012 Dialogic Inc. All Rights Reserved.
//
// The source code contained or described herein and all documents related to
// the source code (collectively "Material") are owned by Dialogic Inc.,
// its subsidiaries, affiliates, suppliers, licensors and/or assigns 
// ("Dialogic"). Title to the Material remains with Dialogic. The Material 
// contains proprietary information and material of Dialogic. The Material is 
// protected by worldwide copyright, trade secret laws, treaty provisions 
// and/or other applicable intellectual property rights, laws and/or treaties.
// No part of the Material may be used, copied, reproduced, modified, 
// published, uploaded, posted, transmitted, distributed, or disclosed in any 
// way without Dialogic's prior express written permission.
//
// No license under any patent, copyright, trade secret or other intellectual
// property right is granted to or conferred upon you by disclosure or delivery
// of the Material, either expressly, by implication, inducement, estoppels
// or otherwise. Any license under such intellectual property rights must be
// express and approved by Dialogic in writing.
//
///////////////////////////////////////////////////////////////////////////////
// File Name: CLogger_imp.h
//
// Description: Implementation of CLogger template functions
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CLogger_imp_h
#define CLogger_imp_h

#include "Utility.h"

#include <boost/format.hpp>

///////////////////////////////////////////////////////////////////////////////
// Function: void CLogger::Log(LogLevelEnum a_logLevel, const TMsg &a_msg)
//
// Description: Log a message with content formatting based on function 
// template parameter type.
//
// Return: void
//
// Parameters: LogLevelEnum a_logLevel
//             const TMsg &a_msg
//
///////////////////////////////////////////////////////////////////////////////
template< typename TMsg>
void CLogger::Log( LogLevelEnum a_logLevel, const TMsg& a_msg )
{
   if ( ( a_logLevel <= m_logLevel ) && ( m_state == LOGGER_RUNNING ) )
   {
      LogItemSptr l_logItem = BlankMessageHeader( a_logLevel);
      *l_logItem << a_msg;
      QueueLogItem( l_logItem);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CLogger::Log(LogLevelEnum a_logLevel, TSource &a_source, const TMethodName &a_methodName)
//
// Description: Log a message with content formatting based on function 
// template parameter types for the source and method name.
//
// Return: void
//
// Parameters: LogLevelEnum a_logLevel
//             TSource &a_source
//             const TMethodName &a_methodName
//
///////////////////////////////////////////////////////////////////////////////
template< typename TSource, typename TMethodName>
void CLogger::Log( LogLevelEnum a_logLevel, TSource& a_source, const TMethodName& a_methodName)
{
   if ( ( a_logLevel <= m_logLevelByType[a_source.LogObjectType()] ) && ( m_state == LOGGER_RUNNING ) )
   {
      LogItemSptr l_logItem = SourceInfoMessageHeader( a_logLevel, a_source, a_methodName);
      QueueLogItem( l_logItem);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CLogger::Log(LogLevelEnum a_logLevel, TSource &a_source, const TMethodName &a_methodName, TMsg &a_msg)
//
// Description: Log a message with content formatting based on function 
// template parameter types for the source, method name and message.
//
// Return: void
//
// Parameters: LogLevelEnum a_logLevel
//             TSource &a_source
//             const TMethodName &a_methodName
//             TMsg &a_msg
//
///////////////////////////////////////////////////////////////////////////////
template< typename TSource, typename TMethodName, typename TMsg>
void CLogger::Log( LogLevelEnum a_logLevel, TSource& a_source, const TMethodName& a_methodName, TMsg& a_msg)
{
   if ( ( a_logLevel <= m_logLevelByType[a_source.LogObjectType()] ) && ( m_state == LOGGER_RUNNING ) )
   {
      LogItemSptr l_logItem = SourceInfoMessageHeader( a_logLevel, a_source, a_methodName);
      *l_logItem << a_msg;
      QueueLogItem( l_logItem);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogItemSptr CLogger::SourceInfoMessageHeader(LogLevelEnum a_logLevel, TSource &a_source, const TMethodName &a_methodName)
//
// Description: Format a log message header based on function template 
// parmaeter types for message source and method name.
//
// Return: LogItemSptr
//
// Parameters: LogLevelEnum a_logLevel
//             TSource &a_source
//             const TMethodName &a_methodName
//
///////////////////////////////////////////////////////////////////////////////
template< typename TSource, typename TMethodName>
LogItemSptr CLogger::SourceInfoMessageHeader( LogLevelEnum a_logLevel, TSource& a_source, const TMethodName& a_methodName)
{
   LogItemSptr l_logItem = BasicMessageHeader( a_logLevel);
   boost::format l_sourceInfoFormat("%20.20s ! %20.20s ! %s::%s: ");
   *l_logItem << l_sourceInfoFormat  
      % a_source.Name()
      % a_source.StateDesc()
      % a_source.ClassName()
      % a_methodName;
   return l_logItem;
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogItemSptr CLogger::FormatedLogItem(LogLevelEnum a_logLevel, TSource &a_source, const TMethodName &a_methodName, TMsg &a_msg)
//
// Description: Format a log message based on function template parmaeter types
// for message source and method name.
//
// Return: LogItemSptr
//
// Parameters: LogLevelEnum a_logLevel
//             TSource &a_source
//             const TMethodName &a_methodName
//             TMsg &a_msg
//
///////////////////////////////////////////////////////////////////////////////
template< typename TSource, typename TMethodName, typename TMsg>
LogItemSptr CLogger::FormatedLogItem( LogLevelEnum a_logLevel, TSource& a_source, const TMethodName& a_methodName, TMsg& a_msg)
{
   LogItemSptr l_logItem = SourceInfoMessageHeader( a_logLevel, a_source, a_methodName);
   *l_logItem << a_msg;
   return l_logItem;
}

#endif
