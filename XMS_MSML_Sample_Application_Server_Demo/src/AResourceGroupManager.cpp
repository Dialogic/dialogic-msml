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
// File Name: AResourceGroupManager.cpp
//
// Description: AResourceGroupManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "AResourceGroupManager.h"
#include "CTask.h"
#include "CTaskProcessor.h"

CResourceGroupManagerStoppedState AResourceGroupManager::m_stoppedState;;
CResourceGroupManagerStartingState AResourceGroupManager::m_startingState;
CResourceGroupManagerStartedState AResourceGroupManager::m_startedState;
CResourceGroupManagerStoppingState AResourceGroupManager::m_stoppingState;

///////////////////////////////////////////////////////////////////////////////
// Function: AResourceGroupManager::AResourceGroupManager( CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return:
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
AResourceGroupManager::AResourceGroupManager( CTaskProcessorSptr a_taskProcessor)
   : ATaskHandler( a_taskProcessor)
   , m_state( &m_stoppedState)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: AResourceGroupManager::~AResourceGroupManager()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
AResourceGroupManager::~AResourceGroupManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool AResourceGroupManager::IsStopped()
//
// Description: Test if the Resource Group Manager is stopped
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool AResourceGroupManager::IsStopped()
{
   return m_state == &m_stoppedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool AResourceGroupManager::IsStarted()
//
// Description: Test if the Resource Group Manager is started
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool AResourceGroupManager::IsStarted()
{
   return m_state == &m_startedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* AResourceGroupManager::StateDesc()
//
// Description: Access a description of the current state
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* AResourceGroupManager::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum AResourceGroupManager::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum AResourceGroupManager::LogObjectType()
{
   return LogObject_ResourceGroupManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::Start()
//
// Description: Queue a task to start the Resource Group Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::Start()
{
   LogDebug( "Start");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroupManager::BasicStart, this),
                                              "AResourceGroupManager::BasicStart"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::OnStarted(int a_result)
//
// Description: Queue a task to handle the Resource Group Manager started 
// completion event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::OnStarted( int a_result)
{
   LogDebugResult( "OnStarted", a_result);
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceGroupManager::BasicOnStarted, this, _1),
                                                   a_result,
                                                   "AResourceGroupManager::BasicOnStarted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::GetResourceGroup(ASipResourceSptr a_inboundSipResource)
//
// Description: Queue a task to get a resource group
//
// Return: void
//
// Parameters: ASipResourceSptr a_inboundSipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::GetResourceGroup( ASipResourceSptr a_inboundSipResource)
{
   LogDebug( "GetResourceGroup");
   ATaskSptr l_task( new CTask1<ASipResourceSptr>( boost::bind( &AResourceGroupManager::BasicGetResourceGroup, this, _1),
                                                                a_inboundSipResource,
                                                                "AResourceGroupManager::BasicGetResourceGroup"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::OnResourceGroupAvailable(AResourceGroupSptr a_resourceGroup)
//
// Description: Queue a task to handle a Resource Group available event
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::OnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup)
{
   LogDebug( "OnResourceGroupAvailable");
   ATaskSptr l_task( new CTask1<AResourceGroupSptr>( boost::bind( &AResourceGroupManager::BasicOnResourceGroupAvailable, this, _1),
                                                                a_resourceGroup,
                                                                "AResourceGroupManager::BasicOnResourceGroupAvailable"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::ResetResourceGroup(AResourceGroupSptr a_resourceGroup)
//
// Description: Queue a task to reset a Resource Group
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::ResetResourceGroup( AResourceGroupSptr a_resourceGroup)
{
   LogDebug( "ResetResourceGroup");
   ATaskSptr l_task( new CTask1<AResourceGroupSptr>( boost::bind( &AResourceGroupManager::BasicResetResourceGroup, this, _1),
                                                                  a_resourceGroup,
                                                                  "AResourceGroupManager::BasicResetResourceGroup"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::OnResourceGroupReset(AResourceGroupSptr a_resourceGroup)
//
// Description: Queue a task to handle a Resource Group reset completion event
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::OnResourceGroupReset( AResourceGroupSptr a_resourceGroup)
{
   LogDebug( "OnResourceGroupReset");
   ATaskSptr l_task( new CTask1<AResourceGroupSptr>( boost::bind( &AResourceGroupManager::BasicOnResourceGroupReset, this, _1),
                                                                a_resourceGroup,
                                                                "AResourceGroupManager::BasicOnResourceGroupReset"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::Stop()
//
// Description: Queue a task to stop the Resource Group Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::Stop()
{
   LogDebug( "Stop");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroupManager::BasicStop, this),
                                              "AResourceGroupManager::BasicStop"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::OnStopped(int a_result)
//
// Description: Queue a task to handlea Resource Group Manager stopped 
// completion event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::OnStopped( int a_result)
{
   LogDebugResult( "OnStopped", a_result);
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceGroupManager::BasicOnStopped, this, _1),
                                                   a_result,
                                                   "AResourceGroupManager::BasicOnStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::BasicStart()
//
// Description: Delegate the Start command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::BasicStart()
{
   m_state->Start( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::BasicOnStarted(int a_result)
//
// Description: Delegate the OnStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::BasicOnStarted( int a_result)
{
   m_state->OnStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::BasicGetResourceGroup(ASipResourceSptr a_inboundSipResource)
//
// Description: Delegate the GetResourceGroup command to the state machine
//
// Return: void
//
// Parameters: ASipResourceSptr a_inboundSipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::BasicGetResourceGroup( ASipResourceSptr a_inboundSipResource)
{
   m_state->GetResourceGroup( *this, a_inboundSipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::BasicOnResourceGroupAvailable(AResourceGroupSptr a_resourceGroup)
//
// Description: Delegate the OnResourceGroupAvailable event to the state machine
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::BasicOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup)
{
   m_state->OnResourceGroupAvailable( *this, a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::BasicResetResourceGroup(AResourceGroupSptr a_resourceGroup)
//
// Description: Delegate the ResetResourceGroup command to the state machine
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::BasicResetResourceGroup( AResourceGroupSptr a_resourceGroup)
{
   m_state->ResetResourceGroup( *this, a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::BasicOnResourceGroupReset(AResourceGroupSptr a_resourceGroup)
//
// Description: Delegate the OnResourceGroupReset event to the state machine
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::BasicOnResourceGroupReset( AResourceGroupSptr a_resourceGroup)
{
   m_state->OnResourceGroupReset( *this, a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::BasicStop()
//
// Description: Delegate the Stop command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::BasicStop()
{
   m_state->Stop( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupManager::BasicOnStopped(int a_result)
//
// Description: Delegate the OnStopped event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::BasicOnStopped( int a_result)
{
   m_state->OnStopped( *this, a_result);
}


///////////////////////////////////////////////////////////////////////////////
//	Function: State setting functions
//
//	Description: These functions set the current state
//
//	Return: void
//
//	Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupManager::SetStateToStopped() { m_state = &m_stoppedState;}
void AResourceGroupManager::SetStateToStarting() { m_state = &m_startingState;}
void AResourceGroupManager::SetStateToStarted() { m_state = &m_startedState;}
void AResourceGroupManager::SetStateToStopping() { m_state = &m_stoppingState;}


