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
// File Name: CCallflowManager.cpp
//
// Description: CCallflowManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "TypeDefs.h"
#include "CCallflowManager.h"
#include "CConfigOptions.h"
#include "CCallflow.h"
#include "AResourceGroup.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CCallflowManager::CCallflowManager(CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
CCallflowManager::CCallflowManager( CTaskProcessorSptr a_taskProcessor) 
      : ACallflowManager( a_taskProcessor)
{
   Name( "Callflow Manager");
}

///////////////////////////////////////////////////////////////////////////////
// Function: CCallflowManager::~CCallflowManager()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CCallflowManager::~CCallflowManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CCallflowManager::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CCallflowManager::ClassName()
{
   return "CCallflowManager";
}

///////////////////////////////////////////////////////////////////////////////
// Function: ACallflowSptr CCallflowManager::FindCallflow(AResourceGroupSptr a_resourceGroup)
//
// Description: Find a Callflow object that is using the given Resource Group
//
// Return: ACallflowSptr
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
ACallflowSptr CCallflowManager::FindCallflow( AResourceGroupSptr a_resourceGroup)
{
   ACallflowSptr l_callflow;
   std::list< ACallflowSptr >::iterator l_pos;
   for ( l_pos = m_callflows.begin();
         l_pos != m_callflows.end();
         ++l_pos)
   {
      if ((*l_pos)->HasResourceGroup( a_resourceGroup))
      {
         l_callflow = *l_pos;
         break;
      }
   }
   return l_callflow;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflowManager::PrimStart()
//
// Description: Start the Callflow Manager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflowManager::PrimStart()
{
   LogDebug("PrimStart");
   OnStarted( 0);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflowManager::PrimOnStarted(int a_result)
//
// Description: Handle the started completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CCallflowManager::PrimOnStarted( int a_result)
{ 
   LogDebugResult("PrimOnStarted", a_result);
   NotifyObservers( CALLFLOW_MANAGER_STARTED, a_result );
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflowManager::PrimGetCallflow(AResourceGroupSptr a_resourceGroup)
//
// Description: Get a Callflow object and initialize it with the given Resource 
// Group
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
int CCallflowManager::PrimGetCallflow( AResourceGroupSptr a_resourceGroup)
{ 
   LogDebug("PrimGetCallflow", a_resourceGroup->Name());
   ACallflowSptr l_callflow( new CCallflow( TaskProcessor(), a_resourceGroup));
   m_callflows.insert( m_callflows.begin(), l_callflow);
   NotifyObservers( CALLFLOW_MANAGER_CALLFLOW_AVAILABLE, l_callflow);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflowManager::PrimResetCallflow(ACallflowSptr a_callflow)
//
// Description: Reset the given Callflow object
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
int CCallflowManager::PrimResetCallflow( ACallflowSptr a_callflow)
{ 
   LogDebug("PrimResetCallflow", a_callflow->Name());
   a_callflow->Reset();
   m_callflows.remove( a_callflow);
   NotifyObservers( CALLFLOW_MANAGER_CALLFLOW_RESET, a_callflow);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflowManager::PrimStop()
//
// Description: Stop the Callflow Manager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflowManager::PrimStop()
{ 
   LogDebug("PrimStop");
   OnStopped( 0);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflowManager::PrimOnStopped(int a_result)
//
// Description: Handle the stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CCallflowManager::PrimOnStopped( int a_result)
{ 
   LogDebugResult("PrimOnStopped", a_result);
   NotifyObservers( CALLFLOW_MANAGER_STOPPED, a_result );
   return 0;
}
