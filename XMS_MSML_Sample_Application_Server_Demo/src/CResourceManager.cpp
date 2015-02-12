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
// File Name: CResourceManager.cpp
//
// Description: CResourceManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "TypeDefs.h"
#include "CResourceManager.h"
#include "CCallflowManager.h"
#include "CResourceGroupManager.h"
#include "CSipResourceManager.h"
#include "AResourceGroup.h"
#include "ACallflow.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CResourceManager::CResourceManager(CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
CResourceManager::CResourceManager( CTaskProcessorSptr a_taskProcessor) 
      : AResourceManager( a_taskProcessor)
      , m_callflowManager( CCallflowManager::Instance( TaskProcessor()))
      , m_sipResourceManager( CSipResourceManager::Instance( TaskProcessor()))
      , m_resourceGroupManager( CResourceGroupManager::Instance( TaskProcessor()))
{
   Name( "Resource Manager");
}

///////////////////////////////////////////////////////////////////////////////
// Function: CResourceManager::~CResourceManager()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CResourceManager::~CResourceManager()
{
   m_callflowManager.reset();
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CResourceManager::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CResourceManager::ClassName()
{
   return "CResourceManager";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CCallflowManagerSptr& CResourceManager::CallflowManager()
//
// Description: Access the Callflow Manager
//
// Return: CCallflowManagerSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CCallflowManagerSptr& CResourceManager::CallflowManager()
{
   return m_callflowManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CResourceGroupManagerSptr& CResourceManager::ResourceGroupManager()
//
// Description: Access the Resource Group Manager
//
// Return: CResourceGroupManagerSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CResourceGroupManagerSptr& CResourceManager::ResourceGroupManager()
{
   return m_resourceGroupManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipResourceManagerSptr& CResourceManager::SipResourceManager()
//
// Description: Access the SIP Resource Manager
//
// Return: CSipResourceManagerSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CSipResourceManagerSptr& CResourceManager::SipResourceManager()
{
   return m_sipResourceManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimStart()
//
// Description: Register for events from Resource Group, Callflow and SIP 
// Resource managers and start the managers
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimStart()
{
   LogDebug( "PrimStart");

   ATaskSptr l_callflowManagerStartedTask( new CTask1<int>(   
                                                boost::bind( &CResourceManager::OnCallflowManagerStarted, this, _1),
                                                "CResourceManager::OnCallflowManagerStarted"));
   CallflowManager()->RegisterForNotification(  this, l_callflowManagerStartedTask, CALLFLOW_MANAGER_STARTED);

   ATaskSptr l_callflowManagerGroupAvailableTask( new CTask1< ACallflowSptr>(   
                                                      boost::bind( &CResourceManager::OnCallflowAvailable, this, _1),
                                                      "CResourceManager::OnCallflowAvailable"));
   CallflowManager()->RegisterForNotification( this, l_callflowManagerGroupAvailableTask, CALLFLOW_MANAGER_CALLFLOW_AVAILABLE);

   ATaskSptr l_callflowManagerGroupResetTask( new CTask1< ACallflowSptr>( 
                                                   boost::bind( &CResourceManager::OnCallflowReset, this, _1),
                                                   "CResourceManager::OnCallflowReset"));
   CallflowManager()->RegisterForNotification( this, l_callflowManagerGroupResetTask, CALLFLOW_MANAGER_CALLFLOW_RESET);

   ATaskSptr l_callflowManagerStoppedTask( new CTask1<int>(
                                                boost::bind( &CResourceManager::OnCallflowManagerStopped, this, _1),
                                                "CResourceManager::OnCallflowManagerStopped"));
   CallflowManager()->RegisterForNotification(  this, l_callflowManagerStoppedTask, CALLFLOW_MANAGER_STOPPED);


   ATaskSptr l_resourceGroupManagerStartedTask( new CTask1<int>( 
                                                   boost::bind( &CResourceManager::OnResourceGroupManagerStarted, this, _1),
                                                   "CResourceManager::OnResourceGroupManagerStarted"));
   ResourceGroupManager()->RegisterForNotification( this, l_resourceGroupManagerStartedTask, RESOURCEGROUP_MANAGER_STARTED);

   ATaskSptr l_resourceGroupManagerGroupAvailableTask( new CTask1< AResourceGroupSptr>(  
                                                            boost::bind( &CResourceManager::OnResourceGroupAvailable, this, _1),
                                                            "CResourceManager::OnResourceGroupAvailable"));
   ResourceGroupManager()->RegisterForNotification( this, l_resourceGroupManagerGroupAvailableTask, RESOURCEGROUP_MANAGER_GROUP_AVAILABLE);

   ATaskSptr l_resourceGroupManagerGroupResetTask( new CTask1< AResourceGroupSptr>(   
                                                      boost::bind( &CResourceManager::OnResourceGroupReset, this, _1),
                                                      "CResourceManager::OnResourceGroupReset"));
   ResourceGroupManager()->RegisterForNotification( this, l_resourceGroupManagerGroupResetTask, RESOURCEGROUP_MANAGER_GROUP_RESET);

   ATaskSptr l_resourceGroupManagerStoppedTask( new CTask1<int>(
                                                   boost::bind( &CResourceManager::OnResourceGroupManagerStopped, this, _1),
                                                   "CResourceManager::OnResourceGroupManagerStopped"));
   ResourceGroupManager()->RegisterForNotification( this, l_resourceGroupManagerStoppedTask, RESOURCEGROUP_MANAGER_STOPPED);


   ATaskSptr l_sipResourceManagerStartedTask( new CTask1<int>(   
                                                   boost::bind( &CResourceManager::OnSipResourceManagerStarted, this, _1),
                                                   "CResourceManager::OnSipResourceManagerStarted"));
   SipResourceManager()->RegisterForNotification( this, l_sipResourceManagerStartedTask, SIPRESOURCE_MANAGER_STARTED);

   ATaskSptr l_sipResourceManagerCallOfferedTask( new CTask1<ASipResourceSptr>(  
                                                      boost::bind( &CResourceManager::OnCallOffered, this, _1),
                                                      "CResourceManager::OnCallOffered"));
   SipResourceManager()->RegisterForNotification( this, l_sipResourceManagerCallOfferedTask, SIPRESOURCE_MANAGER_CALL_OFFERED);

   ATaskSptr l_sipResourceManagerCallDisconnectedTask( new CTask1<ASipResourceSptr>(   
                                                         boost::bind( &CResourceManager::OnCallDisconnected, this, _1),
                                                         "CResourceManager::OnCallDisconnected"));
   SipResourceManager()->RegisterForNotification(  this, l_sipResourceManagerCallDisconnectedTask, SIPRESOURCE_MANAGER_CALL_DISCONNECTED);

   ATaskSptr l_sipResourceManagerStoppedTask( new CTask1<int>(
                                                   boost::bind( &CResourceManager::OnSipResourceManagerStopped, this, _1),
                                                   "CResourceManager::OnSipResourceManagerStopped"));
   SipResourceManager()->RegisterForNotification(  this, l_sipResourceManagerStoppedTask, SIPRESOURCE_MANAGER_STOPPED);

   ResourceGroupManager()->Start();
   CallflowManager()->Start();
   SipResourceManager()->Start();

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnCallflowManagerStarted(int a_result)
//
// Description: Handle Callflow Manager started event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnCallflowManagerStarted( int a_result)
{ 
   LogDebugResult( "PrimOnCallflowManagerStarted", a_result);
   m_startedResources.CallflowManager(true);
   if ( m_startedResources.AllResourcesStarted())
   {
      OnStarted( 0);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnResourceGroupManagerStarted(int a_result)
//
// Description: Handle Resource Group Manager started event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnResourceGroupManagerStarted( int a_result)
{ 
   LogDebugResult( "PrimOnResourceGroupManagerStarted", a_result);
   m_startedResources.ResourceGroupManager(true);
   if ( m_startedResources.AllResourcesStarted())
   {
      OnStarted( 0);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnSipResourceManagerStarted(int a_result)
//
// Description: Handle SIP Resource Manager started event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnSipResourceManagerStarted( int a_result)
{ 
   LogDebugResult( "PrimOnSipResourceManagerStarted", a_result);
   m_startedResources.SipResourceManager(true);
   if ( m_startedResources.AllResourcesStarted())
   {
      SipResourceManager()->EnableInboundCalls();
      OnStarted( 0);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnStarted(int a_result)
//
// Description: Handle started completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnStarted( int a_result)
{ 
   LogDebugResult( "PrimOnStarted", a_result);

   NotifyObservers( RESOURCE_MANAGER_STARTED, a_result );

   // test exception handliong
   //ATaskSptr task( new CTask0( boost::bind( &CResourceManager::ExceptionTest, this),
   //                   "CResourceManager::ExceptionTest()"));
   //TaskProcessor()->QueueTask( task);

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnCallOffered(const ASipResourceSptr &a_sipResource)
//
// Description: Handle SIP Resource call offered event - get a Resource Group
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnCallOffered( const ASipResourceSptr& a_sipResource)
{ 
   LogDebug( "PrimOnCallOffered", a_sipResource->Name());
   ResourceGroupManager()->GetResourceGroup( a_sipResource);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnResourceGroupAvailable(AResourceGroupSptr a_resourceGroup)
//
// Description: Handle Resource Group available event - get a Callflow
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup)
{ 
   LogDebug( "PrimOnResourceGroupAvailable", a_resourceGroup->Name());
   CallflowManager()->GetCallflow( a_resourceGroup);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnResourceGroupReset(AResourceGroupSptr a_resourceGroup)
//
// Description: Handle ResourceGroup reset complete event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnResourceGroupReset( AResourceGroupSptr a_resourceGroup)
{ 
   LogDebug( "PrimOnResourceGroupReset", a_resourceGroup->Name());
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnCallflowAvailable(ACallflowSptr a_callflow)
//
// Description: Handle Callflow available event - start the callflow
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnCallflowAvailable( ACallflowSptr a_callflow)
{ 
   LogDebug( "PrimOnCallflowAvailable", a_callflow->Name());
   a_callflow->Start();
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnCallflowReset(ACallflowSptr a_callflow)
//
// Description: Handle Callflow reset completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnCallflowReset( ACallflowSptr a_callflow)
{ 
   LogDebug( "PrimOnCallflowReset", a_callflow->Name());
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnCallDisconnected(const ASipResourceSptr &a_sipResource)
//
// Description: Handle SIP resource call disconnected event - reset the 
// Resource Group and Callflow
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnCallDisconnected( const ASipResourceSptr& a_sipResource)
{ 
   LogDebug( "PrimOnCallDisconnected", a_sipResource->Name());
   AResourceGroupSptr l_resourceGroup( ResourceGroupManager()->FindResourceGroup( a_sipResource));
   if ( l_resourceGroup)
   {
      ResourceGroupManager()->ResetResourceGroup( l_resourceGroup);

      ACallflowSptr l_callflow( CallflowManager()->FindCallflow( l_resourceGroup));
      if (l_callflow)
      {
         CallflowManager()->ResetCallflow( l_callflow);
      }
   }
   else
   {
      LogError( "PrimOnCallDisconnected", a_sipResource->Name());
      return -1;
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimStop()
//
// Description: Stop the Resource Manager - stop the Callflow, ResourceGroup 
// and SIP Resource managers
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimStop()
{ 
   LogDebug( "PrimStop");
   m_startedResources.CallflowManager( true);
   CallflowManager()->Stop();
   m_startedResources.ResourceGroupManager( true);
   ResourceGroupManager()->Stop();
   m_startedResources.SipResourceManager( true);
   SipResourceManager()->Stop();

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnCallflowManagerStopped(int a_result)
//
// Description: Handle Callflow manager stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnCallflowManagerStopped( int a_result)
{ 
   LogDebugResult( "PrimOnCallflowManagerStopped", a_result);
   m_startedResources.CallflowManager( false);
   if ( m_startedResources.AllResourcesStopped())
   {
      OnStopped( 0);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnResourceGroupManagerStopped(int a_result)
//
// Description: Handle Resource Group Manager stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnResourceGroupManagerStopped( int a_result)
{ 
   LogDebugResult( "PrimOnResourceGroupManagerStopped", a_result);
   m_startedResources.ResourceGroupManager( false);
   if ( m_startedResources.AllResourcesStopped())
   {
      OnStopped( 0);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnSipResourceManagerStopped(int a_result)
//
// Description: Handle SIP Resource Manager stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnSipResourceManagerStopped( int a_result)
{ 
   LogDebugResult( "PrimOnSipResourceManagerStopped", a_result);
   m_startedResources.SipResourceManager( false);
   if ( m_startedResources.AllResourcesStopped())
   {
      OnStopped( 0);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceManager::PrimOnStopped(int a_result)
//
// Description: Handle stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceManager::PrimOnStopped( int a_result)
{ 
   LogDebugResult( "PrimOnStopped", a_result);
   NotifyObservers( RESOURCE_MANAGER_STOPPED, a_result);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceManager::ExceptionTest()
//
// Description: used as a development test for handling exceptions
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void CResourceManager::ExceptionTest()
{
   int a = 1;
   int b = 0;
   int c = a / b;
}
