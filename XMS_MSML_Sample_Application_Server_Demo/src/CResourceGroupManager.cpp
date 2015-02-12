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
// File Name: CResourceGroupManager.cpp
//
// Description: CResourceGroupManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "TypeDefs.h"
#include "CResourceGroupManager.h"
#include "CResourceGroup.h"
#include "CSipResourceManager.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CResourceGroupManager::CResourceGroupManager(CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
CResourceGroupManager::CResourceGroupManager( CTaskProcessorSptr a_taskProcessor) 
      : AResourceGroupManager( a_taskProcessor)
{
   Name( "Resource Group Manager");
}

///////////////////////////////////////////////////////////////////////////////
// Function: CResourceGroupManager::~CResourceGroupManager()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CResourceGroupManager::~CResourceGroupManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CResourceGroupManager:CResourceGroupManager::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CResourceGroupManager::ClassName()
{
   return "CResourceGroupManager";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipResourceManagerSptr CResourceGroupManager::SipResourceManager()
//
// Description: Access SIP Resource Manager
//
// Return: CSipResourceManagerSptr
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CSipResourceManagerSptr CResourceGroupManager::SipResourceManager()
{
   return CSipResourceManager::Instance();
}

///////////////////////////////////////////////////////////////////////////////
// Function: AResourceGroupSptr CResourceGroupManager::FindResourceGroup(ASipResourceSptr a_sipResource)
//
// Description: Find the Resource Group that uses a given SIP Resource
//
// Return: AResourceGroupSptr
//
// Parameters: ASipResourceSptr a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
AResourceGroupSptr CResourceGroupManager::FindResourceGroup( ASipResourceSptr a_sipResource)
{
   LogDebug( "FindResourceGroup", a_sipResource->Name());
   AResourceGroupSptr l_resourceGroup;
   std::list< AResourceGroupSptr >::iterator l_pos;
   for ( l_pos = m_resourceGroups.begin();
         l_pos != m_resourceGroups.end();
         ++l_pos)
   {
      if ((*l_pos)->HasSipResource( a_sipResource))
      {
         l_resourceGroup = *l_pos;
         break;
      }
   }
   return l_resourceGroup;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroupManager::PrimStart()
//
// Description: Start the Resource Group Manager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroupManager::PrimStart()
{
   LogDebug( "PrimStart");
   OnStarted( 0);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroupManager::PrimOnStarted(int a_result)
//
// Description: Handle the Resource Group Manager started completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroupManager::PrimOnStarted( int a_result)
{ 
   LogDebugResult( "PrimOnStarted", a_result);
   NotifyObservers( RESOURCEGROUP_MANAGER_STARTED, a_result);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroupManager::PrimStop()
//
// Description: Stop The Resource Group Manager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroupManager::PrimStop()
{ 
   LogDebug( "PrimStop");
   OnStopped( 0);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroupManager::PrimOnStopped(int a_result)
//
// Description: Handle the Resource Group Manager stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroupManager::PrimOnStopped( int a_result)
{ 
   LogDebugResult( "PrimOnStopped", a_result);
   NotifyObservers( RESOURCEGROUP_MANAGER_STOPPED, a_result);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroupManager::PrimGetResourceGroup(ASipResourceSptr a_inboundSipResource)
//
// Description: Get a Resource group and initialize it with SIP Resources
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ASipResourceSptr a_inboundSipResource
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroupManager::PrimGetResourceGroup( ASipResourceSptr a_inboundSipResource)
{
   LogDebug( "PrimGetResourceGroup");

   AResourceGroupSptr l_resourceGroup;
   ASipResourceSptr l_outboundSipResource;
   if ( SipResourceManager()->AllocateSipResource( a_inboundSipResource))
   {
      LogError( "PrimGetResourceGroup", a_inboundSipResource->Name() + ", could not allocate inbound SIP resource");
   }
   else
   {
      l_outboundSipResource = SipResourceManager()->AllocateSipResource();
      if (!l_outboundSipResource)
      {
         LogError( "PrimGetResourceGroup", a_inboundSipResource->Name() + ", could not allocate outbound SIP resource");
      }
      else
      {
         l_resourceGroup = AResourceGroupSptr ( new CResourceGroup( TaskProcessor(), a_inboundSipResource, l_outboundSipResource));
         if ( l_resourceGroup)
         {
            m_resourceGroups.insert( m_resourceGroups.begin(), l_resourceGroup);

            ATaskSptr l_availableTask( new CTask1< CResourceGroupSptr>(  
                                          boost::bind( &CResourceGroupManager::OnResourceGroupAvailable, this, _1),
                                                       "CResourceGroupManager::OnResourceGroupAvailable"));
            l_resourceGroup->RegisterForNotification( this, l_availableTask, RESOURCEGROUP_GROUP_AVAILABLE);

            ATaskSptr l_resetTask( new CTask1< CResourceGroupSptr>(  
                                          boost::bind( &CResourceGroupManager::OnResourceGroupReset, this, _1),
                                                       "CResourceGroupManager::OnResourceGroupReset"));
            l_resourceGroup->RegisterForNotification( this, l_resetTask, RESOURCEGROUP_GROUP_RESET);

            l_resourceGroup->MakeAvailable();

            return 0;
         }
         LogError( "PrimGetResourceGroup", a_inboundSipResource->Name() + ", could not allocate resource group");
      }
   }

   NotifyObservers( RESOURCEGROUP_MANAGER_GROUP_AVAILABLE, l_resourceGroup);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroupManager::PrimOnResourceGroupAvailable(AResourceGroupSptr a_resourceGroup)
//
// Description: Handle the Resource Group available completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroupManager::PrimOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup)
{
   LogDebug( "PrimOnResourceGroupAvailable");
   NotifyObservers( RESOURCEGROUP_MANAGER_GROUP_AVAILABLE, a_resourceGroup);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroupManager::PrimResetResourceGroup(AResourceGroupSptr a_resourceGroup)
//
// Description: Reset a Resource Group
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroupManager::PrimResetResourceGroup( AResourceGroupSptr a_resourceGroup)
{
   LogDebug( "PrimResetResourceGroup");
   a_resourceGroup->Reset();
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroupManager::PrimOnResourceGroupReset(AResourceGroupSptr a_resourceGroup)
//
// Description: Handle Resource Group reset completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroupManager::PrimOnResourceGroupReset( AResourceGroupSptr a_resourceGroup)
{
   LogDebug( "PrimOnResourceGroupReset");
   SipResourceManager()->DeallocateSipResource( a_resourceGroup->InboundSipResource());
   SipResourceManager()->DeallocateSipResource( a_resourceGroup->OutboundSipResource());
   a_resourceGroup->Unregister( this);
   m_resourceGroups.remove( a_resourceGroup);
   NotifyObservers( RESOURCEGROUP_MANAGER_GROUP_RESET, a_resourceGroup);
   return 0;
}

