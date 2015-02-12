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
// File Name: ATaskHandler.h
//
// Description: ATaskHandler class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ATaskHandler_h
#define ATaskHandler_h

#include <string>

#include <boost/utility.hpp>

#include "TypeDefs.h"
#include "CLogger.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::ATaskHandler
//
// Description: The abstract Task Handler class is responsible for interfaces 
// and variables required for a concrete class to be a task handler.
//
///////////////////////////////////////////////////////////////////////////////
class ATaskHandler : public boost::noncopyable
{
public:
   ATaskHandler( CTaskProcessorSptr a_taskProcessor);
   virtual ~ATaskHandler();

   int QueueTask( ATaskSptr a_task);

   void LogDebug( const char* a_method);
   void LogDebug( const char* a_method, const std::string& a_msg);
   void LogDebugResult( const char* a_method, const int& a_result);
   void LogError( const char* a_method, const std::string& a_msg);

   CTaskProcessorSptr TaskProcessor();
   void TaskProcessor( CTaskProcessorSptr a_taskProcessor);

   CLoggerSptr Logger();
   void Logger( CLoggerSptr a_logger);
   
   const std::string& Name();
   void Name( const std::string& a_name);

   virtual const char* StateDesc() = 0;
   virtual const char* ClassName() = 0;
   virtual LogObjectTypeEnum LogObjectType();

protected:
   ATaskHandler();

private:
   CLoggerSptr m_logger;
   CTaskProcessorSptr m_taskProcessor;
   std::string m_name;
};

#endif
