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
//	File Name:		CTask.cpp
//
//	Description:	Implementation of Task classes
//
///////////////////////////////////////////////////////////////////////////////
#include "CTask.h"

///////////////////////////////////////////////////////////////////////////////
// Function: ATask::ATask(const char *a_debugInfo)
//
// Description: Initializing constructor
//
// Return:  
//
// Parameters: const char *a_debugInfo 
//
///////////////////////////////////////////////////////////////////////////////
ATask::ATask( const char* a_debugInfo) : m_debugInfo( a_debugInfo)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ATask::~ATask()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ATask::~ATask()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ATask::()()
//
// Description: Function call operator
//
// Return: void 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
void ATask::operator () ()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* ATask::DebugInfo()
//
// Description: Access the task debug info
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* ATask::DebugInfo()
{
   return m_debugInfo ? m_debugInfo : "none";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CTask0::CTask0(boost::function0<void> a_taskFunc, const char *a_debugInfo)
//
// Description: Initializing constructor
//
// Return:  
//
// Parameters: boost::function0<void> a_taskFunc 
//             const char *a_debugInfo 
//
///////////////////////////////////////////////////////////////////////////////
CTask0::CTask0( boost::function0< void> a_taskFunc, const char* a_debugInfo)
   : ATask( a_debugInfo)
   , m_taskFunc( a_taskFunc)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CTask0::CTask0(const CTask0 &a_task)
//
// Description: Initializing constructor
//
// Return:  
//
// Parameters: const CTask0 &a_task 
//
///////////////////////////////////////////////////////////////////////////////
CTask0::CTask0( const CTask0& a_task)
   : m_taskFunc( a_task.m_taskFunc)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CTask0::~CTask0()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CTask0::~CTask0()
{
   m_taskFunc.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CTask0::()()
//
// Description: Function call operator
//
// Return: void 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
void CTask0::operator () ()
{
   m_taskFunc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: CTask0& CTask0::=(const CTask0 &a_task)
//
// Description: Assignment operator
//
// Return: CTask0& 
//
// Parameters: const CTask0 &a_task 
//
///////////////////////////////////////////////////////////////////////////////
CTask0& CTask0::operator=( const CTask0& a_task)
{
   if ( this != &a_task)
   {
      m_taskFunc = a_task.m_taskFunc;
   }
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Function: boost::function0<void> CTask0::TaskFunc()
//
// Description: Access the task function
//
// Return: boost::function0<void> 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
boost::function0< void> CTask0::TaskFunc()
{
   return m_taskFunc;
}


