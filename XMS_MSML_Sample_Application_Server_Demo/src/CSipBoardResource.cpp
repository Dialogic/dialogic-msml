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
// File Name: CSipBoardResource.cpp
//
// Description: CSipBoardResource class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "TypeDefs.h"
#include "CSipBoardResource.h"
#include "CConfigOptions.h"
#include "CSrlEventManager.h"
#include "CMetaEvent.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CSipBoardResource::CSipBoardResource(CTaskProcessorSptr a_taskProcessor, const std::string &a_deviceName)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//             const std::string &a_deviceName
//
///////////////////////////////////////////////////////////////////////////////
CSipBoardResource::CSipBoardResource( CTaskProcessorSptr a_taskProcessor, const std::string& a_deviceName) 
   : ASipBoardResource( a_taskProcessor)
   , m_deviceName( a_deviceName)
   , m_srlDeviceHandle( -1)
{
   Name( a_deviceName);
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipBoardResource::~CSipBoardResource()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CSipBoardResource::~CSipBoardResource()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CSipBoardResource::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CSipBoardResource::ClassName()
{
   return "CSipBoardResource";
}

///////////////////////////////////////////////////////////////////////////////
// Function: const CSipBoardResourceSptr CSipBoardResource::SharedPtr()
//
// Description: Obtain a shared pointer to this object
//
// Return: const CSipBoardResourceSptr 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const CSipBoardResourceSptr CSipBoardResource::SharedPtr()
{
   return shared_from_this();
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSrlEventManagerSptr CSipBoardResource::SrlEventManager()
//
// Description: Access the SIP Board Resource
//
// Return: CSrlEventManagerSptr
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CSrlEventManagerSptr CSipBoardResource::SrlEventManager()
{
   return CSrlEventManager::Instance();
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipBoardResource::PrimOpen()
//
// Description: Open the SIP Board Resource - register for events from the SRL 
// Event Manager and open the device
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipBoardResource::PrimOpen()
{
   LogDebug("PrimOpen");

   ATaskSptr l_onOpenedTask( new CTask1<CMetaEventSptr>(  
                                 boost::bind( &CSipBoardResource::OnOpened, this, _1),
                                 "CSipBoardResource::OnOpened"));
   SrlEventManager()->RegisterForEventDispatch( this, l_onOpenedTask, GCEV_OPENEX);

   std::string l_gcDeviceName = ":P_IP:N_" + Name();

   if (  gc_OpenEx(  &m_srlDeviceHandle, 
                     const_cast<char*> (l_gcDeviceName.c_str()), 
                     EV_ASYNC, 
                     (void *) this) != GC_SUCCESS)
   {
      LogGcError( "gc_OpenEx", m_srlDeviceHandle);
      return -1;
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipBoardResource::PrimOnOpened(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle the opened event - set device configuration data
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipBoardResource::PrimOnOpened( const CMetaEventSptr& a_metaEvent)
{ 
   LogDebug("PrimOnOpened");

	GC_PARM_BLKP l_parmblk = 0;
	GC_PARM_BLKP l_retblk = 0;

	gc_util_insert_parm_ref( &l_parmblk,
							IPSET_CONFIG,
							IPPARM_REGISTER_SIP_HEADER,
							(unsigned char)strlen("Call-ID") + 1,
							(void*)"Call-ID");
	gc_util_insert_parm_ref( &l_parmblk,
							IPSET_CONFIG,
							IPPARM_REGISTER_SIP_HEADER,
							(unsigned char)strlen("To") + 1,
							(void*)"To");
	gc_util_insert_parm_ref( &l_parmblk,
							IPSET_CONFIG,
							IPPARM_REGISTER_SIP_HEADER,
							(unsigned char)strlen("From") + 1,
							(void*)"From");

	long l_requestId = 0;
	if (gc_SetConfigData(	GCTGT_CCLIB_NETIF, 
							m_srlDeviceHandle, 
							l_parmblk, 
							0, 
							GCUPDATE_IMMEDIATE, 
							&l_requestId, 
							EV_ASYNC) != GC_SUCCESS)
	{
      LogGcError( "gc_SetConfigData", m_srlDeviceHandle);
	}
	gc_util_delete_parm_blk( l_parmblk);

   NotifyObservers( SIP_BOARD_RESOURCE_OPENED, SharedPtr());

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipBoardResource::PrimClose()
//
// Description: Close the device
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipBoardResource::PrimClose()
{ 
   LogDebug("PrimClose");

   if ( gc_Close( m_srlDeviceHandle) != GC_SUCCESS)
   {
      LogGcError( "gc_Close", m_srlDeviceHandle);
      return -1;
   }

   OnClosed();

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipBoardResource::PrimOnClosed()
//
// Description: Handle devices closed event - unregister for events from the 
// SRL event Manager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipBoardResource::PrimOnClosed()
{ 
   LogDebug("PrimOnClosed");
   SrlEventManager()->Unregister(this);
   NotifyObservers( SIP_BOARD_RESOURCE_CLOSED, SharedPtr());
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipBoardResource::LogGcError(const char *a_method, int a_deviceHandle)
//
// Description: Log a GlobalCall error
//
// Return: void
//
// Parameters: const char *a_method
//             int a_deviceHandle
//
///////////////////////////////////////////////////////////////////////////////
void CSipBoardResource::LogGcError( const char* a_method, int a_deviceHandle)
{
   GC_INFO l_gcErrorInfo;
   if ( gc_ErrorInfo( &l_gcErrorInfo) != GC_SUCCESS)
   {
      Logger()->Log( LOG_LEVEL_ERROR, *this, a_method, " gc_ErrorInfo() failed, unable to retrieve error info");
   }
   else
   {
      std::ostringstream l_stream;
      l_stream <<    ATDV_NAMEP( a_deviceHandle)
         << "\n\tGC error="
         << "\n\tgcValue  : 0x" << std::hex << l_gcErrorInfo.gcValue
         << "\n\tgcMsg    : " << l_gcErrorInfo.gcMsg
         << "\n\tccLibId  : " << std::dec << l_gcErrorInfo.ccLibId
         << "\n\tccLibName: " << l_gcErrorInfo.ccLibName
         << "\n\tccValue  : 0x" << std::hex << l_gcErrorInfo.ccValue
         << "\n\tccMsg    : " << l_gcErrorInfo.ccMsg
         << "\n\tinfo     : " << l_gcErrorInfo.additionalInfo;
      const std::string& l_msg = l_stream.str();
      Logger()->Log( LOG_LEVEL_ERROR, *this, a_method, l_msg);
   }
}
