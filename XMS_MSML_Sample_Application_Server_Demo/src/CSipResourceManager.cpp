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
// File Name: CSipResourceManager.cpp
//
// Description: CSipResourceManager calss implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "CSipResourceManager.h"
#include "CSrlEventManager.h"
#include "CConfigOptions.h"
#include "CSipBoardResource.h"
#include "CSipResource.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CSipResourceManager::CSipResourceManager()
//
// Description: Default constructor - should never be called
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CSipResourceManager::CSipResourceManager()
{
   assert(0);
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipResourceManager::CSipResourceManager(CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
CSipResourceManager::CSipResourceManager( CTaskProcessorSptr a_taskProcessor) 
      : ASipResourceManager( a_taskProcessor)
      , m_srlEventManager( CSrlEventManager::Instance( TaskProcessor()))
      , m_sipBoardResource( CSipBoardResourceSptr (new CSipBoardResource( TaskProcessor(), "iptB1"))) 
{
   Name( "Sip Resource Manager");
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipResourceManager::~CSipResourceManager()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CSipResourceManager::~CSipResourceManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CSipResourceManager::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CSipResourceManager::ClassName()
{
   return "CSipResourceManager";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSrlEventManagerSptr CSipResourceManager::SrlEventManager()
//
// Description: Access the SRL Event Manager
//
// Return: CSrlEventManagerSptr 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CSrlEventManagerSptr CSipResourceManager::SrlEventManager()
{
   return m_srlEventManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CSipResourceManager::SipResourcesPending()
//
// Description: Test if any SIP Resources are pending open or close completion
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool CSipResourceManager::SipResourcesPending()
{
   return ! m_pendingSipResources.empty();
}

///////////////////////////////////////////////////////////////////////////////
// Function: ASipResourceSptr CSipResourceManager::AllocateSipResource()
//
// Description: Allocate an available SIP Resource
//
// Return: ASipResourceSptr
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ASipResourceSptr CSipResourceManager::AllocateSipResource()
{
   ASipResourceSptr l_sipResource = *m_unallocatedSipResources.begin();
   m_unallocatedSipResources.erase( l_sipResource);
   m_allocatedSipResources.insert( l_sipResource);
   return l_sipResource;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::AllocateSipResource(ASipResourceSptr a_sipResource)
//
// Description: Allocate a specific SIP Resource
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ASipResourceSptr a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::AllocateSipResource( ASipResourceSptr a_sipResource)
{
   m_unallocatedSipResources.erase( a_sipResource);
   m_allocatedSipResources.insert( a_sipResource);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::DeallocateSipResource(ASipResourceSptr a_sipResource)
//
// Description: Return an allocated SIP Resource to the pool on available SIP 
// Resources
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ASipResourceSptr a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::DeallocateSipResource( ASipResourceSptr a_sipResource)
{
   m_allocatedSipResources.erase( a_sipResource);
   m_unallocatedSipResources.insert( a_sipResource);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimStartSrlEventManager()
//
// Description: Register for events from the SRL Event Manager and start it
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimStartSrlEventManager()
{
   LogDebug("PrimStartSrlEventManager");

   ATaskSptr l_sipStackManagerStartedTask( new CTask1<int>(
                                                boost::bind( &CSipResourceManager::OnSrlEventManagerStarted, this, _1),
                                                             "CSipResourceManager::OnSrlEventManagerStarted"));
   SrlEventManager()->RegisterForNotification( this, l_sipStackManagerStartedTask, SRLEVENT_MANAGER_STARTED);

   ATaskSptr l_sipStackManagerStoppedTask( new CTask1<int>(
                                                boost::bind( &CSipResourceManager::OnSrlEventManagerStopped, this, _1),
                                                             "CSipResourceManager::OnSrlEventManagerStopped"));
   SrlEventManager()->RegisterForNotification( this, l_sipStackManagerStoppedTask, SRLEVENT_MANAGER_STOPPED);

   SrlEventManager()->Start();

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnSrlEventManagerStarted(int a_result)
//
// Description: Handle SRL Event Manager start completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnSrlEventManagerStarted( int a_result)
{ 
   LogDebugResult("PrimOnSrlEventManagerStarted", a_result);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOpenSipBoardResource()
//
// Description: Register for events from the SIP Board Resource and open it
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOpenSipBoardResource()
{
   LogDebug("PrimOpenSipBoardResource");

   ATaskSptr l_sipBoardResourceOpenedTask( new CTask1<const CSipBoardResourceSptr>( 
                                                boost::bind( &CSipResourceManager::OnSipBoardResourceOpened, this, _1),
                                                             m_sipBoardResource,
                                                             "CSipResourceManager::OnSipBoardResourceOpened"));
   m_sipBoardResource->RegisterForNotification( this, l_sipBoardResourceOpenedTask, SIP_BOARD_RESOURCE_OPENED);

   ATaskSptr l_sipBoardResourceClosedTask( new CTask1<const CSipBoardResourceSptr>( 
                                                boost::bind( &CSipResourceManager::OnSipBoardResourceClosed, this, _1),
                                                             m_sipBoardResource,
                                                             "CSipResourceManager::OnCallOffered"));
   m_sipBoardResource->RegisterForNotification( this, l_sipBoardResourceClosedTask, SIP_BOARD_RESOURCE_CLOSED);

   m_sipBoardResource->Open();

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOpenSipResources()
//
// Description: Create, register for events from, and open the configured 
// number of SIP Resources
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOpenSipResources()
{
   LogDebug("PrimOpenSipResources");
   m_pendingSipResources.clear();
   for ( int i = 1; i <= CConfigOptions::Instance()->MaxChannels(); i++)
   {
      CSipResourceSptr l_resource( new CSipResource( TaskProcessor(), "iptB1T" + AsString(i)));
      m_sipResources[ (long) l_resource.get()] = l_resource;
      AllocateSipResource( l_resource);
      m_pendingSipResources.insert( l_resource);

      ATaskSptr l_resourceUnblockedTask( new CTask1<CSipResourceSptr>( 
                                                boost::bind( &CSipResourceManager::OnSipResourceOpened, this, _1),
                                                             l_resource,
                                                             "CSipResourceManager::OnSipResourceOpened"));
      l_resource->RegisterForNotification( this, l_resourceUnblockedTask, SIP_RESOURCE_UNBLOCKED);

      ATaskSptr l_onCallOfferedTask( new CTask1<CSipResourceSptr>( 
                                          boost::bind( &CSipResourceManager::OnCallOffered, this, _1),
                                                       l_resource,
                                                       "CSipResourceManager::OnCallOffered"));
      l_resource->RegisterForNotification( this, l_onCallOfferedTask, SIP_RESOURCE_OFFERED_RESOURCE);

      ATaskSptr l_onCallDisconnectedTask( new CTask1<CSipResourceSptr>(
                                                boost::bind( &CSipResourceManager::OnCallDisconnected, this, _1),
                                                             l_resource,
                                                             "CSipResourceManager::OnCallDisconnected"));
      l_resource->RegisterForNotification( this, l_onCallDisconnectedTask, SIP_RESOURCE_DISCONNECTED_RESOURCE);

      ATaskSptr l_resourceClosedTask( new CTask1<CSipResourceSptr>(
                                             boost::bind( &CSipResourceManager::OnSipResourceClosed, this, _1),
                                                          l_resource,
                                                          "CSipResourceManager::OnSipResourceClosed"));
      l_resource->RegisterForNotification( this, l_resourceClosedTask, SIP_RESOURCE_CLOSED);

      l_resource->Open( SrlEventManager());
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnSipBoardResourceOpened(const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: Handle SIP Board Resource open completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnSipBoardResourceOpened( const ASipBoardResourceSptr& a_sipBoardResource)
{ 
   LogDebug("PrimOnSipBoardResourceOpened", a_sipBoardResource->Name());
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnSipResourceOpened(const ASipResourceSptr &a_sipResource)
//
// Description: Handle SIP Resource open completion event - ass the SIP 
// Resource to the pool of available SIP Resoirces
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnSipResourceOpened( const ASipResourceSptr& a_sipResource)
{ 
   LogDebug("PrimOnSipResourceOpened", a_sipResource->Name());

   std::set< ASipResourceSptr >::iterator l_pos;
   for ( l_pos = m_pendingSipResources.begin();
         l_pos != m_pendingSipResources.end();
         ++l_pos)
   {
      if ( (*l_pos) == a_sipResource)
      {
         break;
      }
   }

   if ( l_pos == m_pendingSipResources.end())
   {
      LogError( "PrimOnSipResourceOpened", "unknown a_sipResource: " + a_sipResource->Name());
   }
   else
   {
      m_pendingSipResources.erase( l_pos);
      DeallocateSipResource( a_sipResource);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnStarted(int a_result)
//
// Description: Handle SIP Resource Manager started completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnStarted( int a_result)
{ 
   LogDebugResult("PrimOnStarted", a_result);
   NotifyObservers( SIPRESOURCE_MANAGER_STARTED, a_result);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimEnableInboundCalls()
//
// Description: Enable inbound calls on all SIP Resources
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimEnableInboundCalls()
{ 
   LogDebug("PrimEnableInboundCalls");

   std::set< ASipResourceSptr >::iterator l_sipResource;
   for ( l_sipResource = m_unallocatedSipResources.begin();
         l_sipResource != m_unallocatedSipResources.end();
         ++l_sipResource)
   {
      (*l_sipResource)->EnableInboundCalls();
   }

   NotifyObservers( SIPRESOURCE_MANAGER_INBOUNDCALLS_ENABLED);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnCallOffered(const ASipResourceSptr &a_sipResource)
//
// Description: Handle SIP Resource inbound call offered event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnCallOffered( const ASipResourceSptr& a_sipResource)
{ 
   LogDebug("PrimOnCallOffered", a_sipResource->Name());
   NotifyObservers( SIPRESOURCE_MANAGER_CALL_OFFERED, const_cast<ASipResourceSptr&>(a_sipResource));
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnCallDisconnected(const ASipResourceSptr &a_sipResource)
//
// Description: Handle SIP Resource call disconnected event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnCallDisconnected( const ASipResourceSptr& a_sipResource)
{ 
   LogDebug("PrimOnCallDisconnected", a_sipResource->Name());
   NotifyObservers( SIPRESOURCE_MANAGER_CALL_DISCONNECTED, const_cast<ASipResourceSptr&>(a_sipResource));
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimCloseSipResources()
//
// Description: Close all SIP Resources
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimCloseSipResources()
{ 
   LogDebug("PrimCloseSipResources");

   std::map< long, ASipResourceSptr >:: iterator l_pos;

   m_pendingSipResources.clear();
   for ( l_pos = m_sipResources.begin();
         l_pos != m_sipResources.end();
         ++l_pos)
   {
      ASipResourceSptr l_sipResource = l_pos->second;
      m_unallocatedSipResources.erase( l_sipResource);
      m_allocatedSipResources.erase( l_sipResource);
      m_pendingSipResources.insert( l_sipResource);
      l_sipResource->Close();
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnSipResourceClosed(const ASipResourceSptr &a_sipResource)
//
// Description: Handle SIP Resource closed completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnSipResourceClosed( const ASipResourceSptr& a_sipResource)
{ 
   LogDebug("PrimOnSipResourceClosed", a_sipResource->Name());

   std::set< ASipResourceSptr >::iterator l_pos;
   l_pos = m_pendingSipResources.find( a_sipResource);
   if (l_pos != m_pendingSipResources.end())
   {
      m_pendingSipResources.erase(l_pos);
      a_sipResource->Unregister( this);
   }
   else
   {
      LogError( "PrimOnSipResourceClosed", "unknown a_sipResource: " + a_sipResource->Name());
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimCloseSipBoardResource()
//
// Description: Close the SIP Board Resource
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimCloseSipBoardResource()
{ 
   LogDebug("PrimCloseSipBoardResource");
   m_sipBoardResource->Close();
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnSipBoardResourceClosed(const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: Handle the SIP Board Resource closed completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnSipBoardResourceClosed( const ASipBoardResourceSptr& a_sipBoardResource)
{ 
   LogDebug("PrimOnSipBoardResourceClosed", a_sipBoardResource->Name());

   m_sipBoardResource->Unregister( this);

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimStopSrlEventManager()
//
// Description: Stop the SRL Event Manager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimStopSrlEventManager()
{ 
   LogDebug("PrimStopSrlEventManager");
   SrlEventManager()->Stop();
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnSrlEventManagerStopped(int a_result)
//
// Description: Handle SRL Event Manager closed completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnSrlEventManagerStopped( int a_result)
{ 
   LogDebugResult("PrimOnSrlEventManagerStopped", a_result);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResourceManager::PrimOnStopped(int a_result)
//
// Description: Handle the SIP Resource Manager stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CSipResourceManager::PrimOnStopped( int a_result)
{ 
   LogDebugResult("PrimOnStopped", a_result);

   m_sipResources.clear();

   NotifyObservers( SIPRESOURCE_MANAGER_STOPPED, a_result);

   return 0;
}
