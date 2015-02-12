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
// File Name: CSrlEventManager.cpp
//
// Description: CSrlEventManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "TypeDefs.h"
#include "CSrlEventManager.h"
#include "CConfigOptions.h"
#include "AResourceGroup.h"
#include "CMetaEvent.h"

#include <sstream>
#include <iomanip>

///////////////////////////////////////////////////////////////////////////////
// Function: CSrlEventManager::CSrlEventManager()
//
// Description: Default constructor - should never be called
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CSrlEventManager::CSrlEventManager()
{
   assert(0);
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSrlEventManager::CSrlEventManager(CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
CSrlEventManager::CSrlEventManager( CTaskProcessorSptr a_taskProcessor) 
      : ASrlEventManager( a_taskProcessor)
{
   Name( "SrlEvent Manager");
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSrlEventManager::~CSrlEventManager()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CSrlEventManager::~CSrlEventManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CSrlEventManager::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CSrlEventManager::ClassName()
{
   return "CSrlEventManager";
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSrlEventManager::PrimStart()
//
// Description: Start the event polling thread
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSrlEventManager::PrimStart()
{
   LogDebug("PrimStart");
   m_thread = boost::shared_ptr<boost::thread> ( new boost::thread( boost::bind( &CSrlEventManager::ProcessEvents, this)));
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSrlEventManager::PrimOnStarted(int a_result)
//
// Description: Handle SRL Event Manager started completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CSrlEventManager::PrimOnStarted( int a_result)
{ 
   LogDebugResult("PrimOnStarted", a_result);
   NotifyObservers( SRLEVENT_MANAGER_STARTED, a_result );
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSrlEventManager::PrimStop()
//
// Description: Stop the SRL Event Manager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSrlEventManager::PrimStop()
{ 
   LogDebug("PrimStop");
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSrlEventManager::PrimOnStopped(int a_result)
//
// Description: Handle the SRL Event Manager stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CSrlEventManager::PrimOnStopped( int a_result)
{ 
   LogDebugResult("PrimOnStopped", a_result);
   NotifyObservers( SRLEVENT_MANAGER_STOPPED, a_result );
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSrlEventManager::ProcessEvents()
//
// Description: Wait for events from the SRL and dispatch them as they arrive
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void CSrlEventManager::ProcessEvents()
{
   Logger()->Log( LOG_LEVEL_DEBUG, *this, "ProcessEvents");
   OnStarted( 0);
   while ( !IsStopping())
   {
	   int l_result = sr_waitevt( 100);
	   if ( l_result != -1) 
	   {
	      METAEVENT l_metaEvent;

	      if ( gc_GetMetaEvent( &l_metaEvent) != GC_SUCCESS)
	      {
		      LogGcError( "DispatchEvent", 0);
		      return;
	      }

         long l_eventType = l_metaEvent.evttype;
         void* l_userAttribute = l_metaEvent.usrattr;

         ATaskHandler* l_eventHandler = static_cast<ATaskHandler*>(l_userAttribute);
         assert( l_eventHandler);

         CMetaEventSptr l_metaEventData( new CMetaEvent( &l_metaEvent));
         Logger()->Log( LOG_LEVEL_DEBUG, *this, "DispatchEvent", gcev_msg[l_eventType - DT_GC]);
         ADispatcher::DispatchEvent( l_eventType, l_eventHandler, l_metaEventData);

         if ( l_eventType == GCEV_TASKFAIL)
         {
            LogGcError( "GCEV_TASKFAIL", l_metaEvent.evtdev);
         }
	   }
   }
   OnStopped( 0);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSrlEventManager::LogGcError(const char *a_method, int a_deviceHandle)
//
// Description: Log a GlobalCall error
//
// Return: void
//
// Parameters: const char *a_method
//             int a_deviceHandle
//
///////////////////////////////////////////////////////////////////////////////
void CSrlEventManager::LogGcError( const char* a_method, int a_deviceHandle)
{
   GC_INFO l_gcErrorInfo;
   if ( gc_ErrorInfo( &l_gcErrorInfo) != GC_SUCCESS)
   {
      Logger()->Log( LOG_LEVEL_ERROR, *this, a_method, " gc_ErrorInfo() failed, unable to retrieve error info");
   }
   else
   {
      std::ostringstream l_stream;
	   l_stream << 	ATDV_NAMEP( a_deviceHandle)
         << ", GC error="
         << "\n\tgcValue  : 0x" << std::hex << l_gcErrorInfo.gcValue
         << "\n\tgcMsg    : " << l_gcErrorInfo.gcMsg
         << "\tccLibId  : " << std::dec << l_gcErrorInfo.ccLibId
         << "\n\tccLibName: " << l_gcErrorInfo.ccLibName
         << "\n\tccValue  : 0x" << std::hex << l_gcErrorInfo.ccValue
         << "\n\tccMsg    : " << l_gcErrorInfo.ccMsg
         << "\tinfo     : " << l_gcErrorInfo.additionalInfo;
      const std::string& l_msg = l_stream.str();
      Logger()->Log( LOG_LEVEL_ERROR, *this, a_method, l_msg);
   }
}
