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
// File Name: ATaskHandler.cpp
//
// Description: ATaskHandler class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "ATaskHandler.h"
#include "CTaskProcessor.h"

///////////////////////////////////////////////////////////////////////////////
// Function: ATaskHandler::ATaskHandler()
//
// Description: Default constructor - should never be called.  Always use the
// initializing constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ATaskHandler::ATaskHandler()
{
   assert(0);
}

///////////////////////////////////////////////////////////////////////////////
// Function: ATaskHandler::ATaskHandler( CTaskProcessorSptr a_taskProcessor) 
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
ATaskHandler::ATaskHandler( CTaskProcessorSptr a_taskProcessor) 
      : m_logger( CLogger::Instance())
      , m_taskProcessor( a_taskProcessor)
      , m_name( "ATaskHandler")
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ATaskHandler::~ATaskHandler()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ATaskHandler::~ATaskHandler() 
{ 
   m_taskProcessor.reset(); 
   m_logger.reset();
}

///////////////////////////////////////////////////////////////////////////////
// Function: CTaskProcessorSptr ATaskHandler::TaskProcessor()
//
// Description: Access the Task Processor
//
// Return: CTaskProcessorSptr 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CTaskProcessorSptr ATaskHandler::TaskProcessor()
{
   return m_taskProcessor;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ATaskHandler::TaskProcessor(CTaskProcessorSptr a_taskProcessor)
//
// Description: Set the Task Processor
//
// Return: void 
//
// Parameters: CTaskProcessorSptr a_taskProcessor 
//
///////////////////////////////////////////////////////////////////////////////
void ATaskHandler::TaskProcessor( CTaskProcessorSptr a_taskProcessor)
{
   m_taskProcessor = a_taskProcessor;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CLoggerSptr ATaskHandler::Logger()
//
// Description: Access the Logger
//
// Return: CLoggerSptr 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CLoggerSptr ATaskHandler::Logger()
{
   return m_logger;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ATaskHandler::Logger(CLoggerSptr a_logger)
//
// Description: Set the Logger
//
// Return: void 
//
// Parameters: CLoggerSptr a_logger 
//
///////////////////////////////////////////////////////////////////////////////
void ATaskHandler::Logger( CLoggerSptr a_logger)
{
   m_logger = a_logger;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string& ATaskHandler::Name()
//
// Description: Access the object Name
//
// Return: const std::string& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const std::string& ATaskHandler::Name()
{
   return m_name;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ATaskHandler::Name(const std::string &a_name)
//
// Description: Set the object Name
//
// Return: void 
//
// Parameters: const std::string &a_name 
//
///////////////////////////////////////////////////////////////////////////////
void ATaskHandler::Name( const std::string& a_name)
{
   m_name = a_name;
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum ATaskHandler::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum ATaskHandler::LogObjectType()
{
   return LogObject_System;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ATaskHandler::QueueTask(ATaskSptr a_task)
//
// Description: Queue a task to the task processor if it exists
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ATaskSptr a_task
//
///////////////////////////////////////////////////////////////////////////////
int ATaskHandler::QueueTask( ATaskSptr a_task) 
{ 
   return ! m_taskProcessor ? -1 : m_taskProcessor->QueueTask( a_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ATaskHandler::LogDebug(const char *a_method)
//
// Description: Log a debug message containing only the method name
//
// Return: void
//
// Parameters: const char *a_method
//
///////////////////////////////////////////////////////////////////////////////
void ATaskHandler::LogDebug( const char* a_method)
{ 
   Logger()->Log( LOG_LEVEL_DEBUG, *this, a_method);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ATaskHandler::LogDebug(const char *a_method, const std::string &a_msg)
//
// Description: Log a debug message containing a method name and a message
//
// Return: void
//
// Parameters: const char *a_method
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void ATaskHandler::LogDebug( const char* a_method, const std::string& a_msg)
{
   Logger()->Log( LOG_LEVEL_DEBUG, *this, a_method, a_msg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ATaskHandler::LogDebugResult(const char *a_method, const int &a_result)
//
// Description: Log a debug message containing a method name and integer result
// data
//
// Return: void
//
// Parameters: const char *a_method
//             const int &a_result
//
///////////////////////////////////////////////////////////////////////////////
void ATaskHandler::LogDebugResult( const char* a_method, const int& a_result)
{
   std::string tempMsg( "a_result: " + AsString( a_result));
   Logger()->Log( LOG_LEVEL_DEBUG, *this, a_method, tempMsg);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ATaskHandler::LogError(const char *a_method, const std::string &a_msg)
//
// Description: Log an error message containing a method name and a message
//
// Return: void
//
// Parameters: const char *a_method
//             const std::string &a_msg
//
///////////////////////////////////////////////////////////////////////////////
void ATaskHandler::LogError( const char* a_method, const std::string& a_msg)
{
   Logger()->Log( LOG_LEVEL_ERROR, *this, a_method, a_msg);
}
