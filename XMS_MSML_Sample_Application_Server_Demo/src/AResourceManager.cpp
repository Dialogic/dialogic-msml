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
// File Name: AResourceManager.cpp
//
// Description: AResourceManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "TypeDefs.h"
#include "AResourceManager.h"
#include "CTask.h"
#include "CTaskProcessor.h"
#include "AResourceGroup.h"

CResourceManagerStoppedState AResourceManager::m_stoppedState;;
CResourceManagerStartingState AResourceManager::m_startingState;
CResourceManagerStartedState AResourceManager::m_startedState;
CResourceManagerStoppingState AResourceManager::m_stoppingState;

///////////////////////////////////////////////////////////////////////////////
// Function: AResourceManager::AResourceManager( CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
AResourceManager::AResourceManager( CTaskProcessorSptr a_taskProcessor)
   : ATaskHandler( a_taskProcessor)
   , m_state( &m_stoppedState) 
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: AResourceManager::~AResourceManager()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
AResourceManager::~AResourceManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool AResourceManager::IsStopped()
//
// Description: Test if the Resource Manager is stopped
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool AResourceManager::IsStopped()
{
   return m_state == &m_stoppedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool AResourceManager::IsStarted()
//
// Description: Test if the Resource Manager is started
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool AResourceManager::IsStarted()
{
   return m_state == &m_startedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* AResourceManager::StateDesc()
//
// Description: Access a description of the current state
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* AResourceManager::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum AResourceManager::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum AResourceManager::LogObjectType()
{
   return LogObject_ResourceManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::Start()
//
// Description: Queue a task to Start the Resource Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::Start()
{
   LogDebug( "Start");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceManager::BasicStart, this),
                                              "AResourceManager::BasicStart"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::Stop()
//
// Description: Queue a task to Stop the Resource Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::Stop()
{
   LogDebug( "Stop");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceManager::BasicStop, this),
                                              "AResourceManager::BasicStop"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnCallflowManagerStarted(int a_result)
//
// Description: Queue a task to handle a Callflow Manager Started event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnCallflowManagerStarted( int a_result)
{
   LogDebug( "OnCallflowManagerStarted");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceManager::BasicOnCallflowManagerStarted, this, _1),
                                                   a_result,
                                                   "AResourceManager::BasicOnCallflowManagerStarted"));
   TaskProcessor()->QueueTask( l_task);
}  

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnResourceGroupManagerStarted(int a_result)
//
// Description: Queue a task to handle a Resource Group Manager started event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnResourceGroupManagerStarted( int a_result)
{
   LogDebug( "OnResourceGroupManagerStarted");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceManager::BasicOnResourceGroupManagerStarted, this, _1),
                                                   a_result,
                                                   "AResourceManager::BasicOnResourceGroupManagerStarted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnSipResourceManagerStarted(int a_result)
//
// Description: Queue a task to handle a SIP Resource Manager started event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnSipResourceManagerStarted( int a_result)
{
   LogDebug( "OnSipResourceManagerStarted");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceManager::BasicOnSipResourceManagerStarted, this, _1),
                                                   a_result,
                                                   "AResourceManager::BasicOnSipResourceManagerStarted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnStarted(int a_result)
//
// Description: Queue a task to handle a Resource Manager started completion 
// event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnStarted( int a_result)
{
   LogDebug( "OnStarted");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceManager::BasicOnStarted, this, _1),
                                                   a_result,
                                                   "AResourceManager::BasicOnStarted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnCallOffered(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle a SIP Resource Call Offered event
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnCallOffered( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnCallOffered");
   ATaskSptr l_task( new CTask1<ASipResourceSptr>( 
                           boost::bind( &AResourceManager::BasicOnCallOffered, this, _1),
                                        a_sipResource,
                                        "AResourceManager::BasicOnCallOffered"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnResourceGroupAvailable(AResourceGroupSptr a_resourceGroup)
//
// Description: Queue a task to handle a Resource Group available event
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup)
{
   LogDebug( "OnResourceGroupAvailable", a_resourceGroup->Name());
   ATaskSptr l_task( new CTask1<AResourceGroupSptr>(  
                           boost::bind( &AResourceManager::BasicOnResourceGroupAvailable, this, _1),
                                        a_resourceGroup,
                                        "AResourceManager::BasicOnResourceGroupAvailable"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnResourceGroupReset(AResourceGroupSptr a_resourceGroup)
//
// Description: Queue a task to handle a Resource Group reset event
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnResourceGroupReset( AResourceGroupSptr a_resourceGroup)
{
   LogDebug( "OnResourceGroupReset");
   ATaskSptr l_task( new CTask1<AResourceGroupSptr>(  
                           boost::bind( &AResourceManager::BasicOnResourceGroupReset, this, _1),
                                        a_resourceGroup,
                                        "AResourceManager::BasicOnResourceGroupReset"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnCallflowAvailable(ACallflowSptr a_callflow)
//
// Description: Queue a task to handle a Callflow Available event
//
// Return: void
//
// Parameters: ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnCallflowAvailable( ACallflowSptr a_callflow)
{
   LogDebug( "OnCallflowAvailable");
   ATaskSptr l_task( new CTask1<ACallflowSptr>( 
                           boost::bind( &AResourceManager::BasicOnCallflowAvailable, this, _1),
                                        a_callflow,
                                       "AResourceManager::BasicOnCallflowAvailable"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnCallflowReset(ACallflowSptr a_callflow)
//
// Description: Queue a task to handle a Callflow reset event
//
// Return: void
//
// Parameters: ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnCallflowReset( ACallflowSptr a_callflow)
{
   LogDebug( "OnCallflowReset");
   ATaskSptr l_task( new CTask1<ACallflowSptr>( 
                           boost::bind( &AResourceManager::BasicOnCallflowReset, this, _1),
                                        a_callflow,
                                        "AResourceManager::BasicOnCallflowReset"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnCallDisconnected(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle a SIP Resource call disconnected event
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnCallDisconnected( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnCallDisconnected");
   ATaskSptr l_task( new CTask1<ASipResourceSptr>( 
                           boost::bind( &AResourceManager::BasicOnCallDisconnected, this, _1),
                                        a_sipResource,
                                        "AResourceManager::BasicOnCallDisconnected"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnCallflowManagerStopped(int a_result)
//
// Description: Queue a task to handle a Callflow Manager stopped event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnCallflowManagerStopped( int a_result)
{
   LogDebug( "OnCallflowManagerStopped");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceManager::BasicOnCallflowManagerStopped, this, _1),
                                                   a_result,
                                                   "AResourceManager::BasicOnCallflowManagerStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnResourceGroupManagerStopped(int a_result)
//
// Description: Queue a task to handle a Resource Group Manager stopped event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnResourceGroupManagerStopped( int a_result)
{
   LogDebug( "OnResourceGroupManagerStopped");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceManager::BasicOnResourceGroupManagerStopped, this, _1),
                                                   a_result,
                                                   "AResourceManager::BasicOnResourceGroupManagerStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnSipResourceManagerStopped(int a_result)
//
// Description: Queue a task to handle a SIP Resource Manager stopped event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnSipResourceManagerStopped( int a_result)
{
   LogDebug( "OnSipResourceManagerStopped");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceManager::BasicOnSipResourceManagerStopped, this, _1),
                                                   a_result,
                                                   "AResourceManager::BasicOnSipResourceManagerStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::OnStopped(int a_result)
//
// Description: Queue a task to handle a Resource Manager stopped completion event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::OnStopped( int a_result)
{
   LogDebug( "OnStopped");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &AResourceManager::BasicOnStopped, this, _1),
                                                   a_result,
                                                   "AResourceManager::BasicOnStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicStart()
//
// Description: Delegate the Start command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicStart()
{
   m_state->Start( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnCallflowManagerStarted(int a_result)
//
// Description: Delegate the OnCallflowManagerStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnCallflowManagerStarted( int a_result)
{
   m_state->OnCallflowManagerStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnResourceGroupManagerStarted(int a_result)
//
// Description: Delegate the OnResourceGroupManagerStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnResourceGroupManagerStarted( int a_result)
{
   m_state->OnResourceGroupManagerStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnSipResourceManagerStarted(int a_result)
//
// Description: Delegate the OnSipResourceManagerStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnSipResourceManagerStarted( int a_result)
{
   m_state->OnSipResourceManagerStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnStarted(int a_result)
//
// Description: Delegate the OnStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnStarted( int a_result)
{
   m_state->OnStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnCallOffered(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnCallOffered event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnCallOffered( const ASipResourceSptr& a_sipResource)
{
   m_state->OnCallOffered( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnResourceGroupAvailable(AResourceGroupSptr a_resourceGroup)
//
// Description: Delegate the OnResourceGroupAvailable event to the state machine
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup)
{
   m_state->OnResourceGroupAvailable( *this, a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnResourceGroupReset(AResourceGroupSptr a_resourceGroup)
//
// Description: Delegate the OnResourceGroupReset event to the state machine
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnResourceGroupReset( AResourceGroupSptr a_resourceGroup)
{
   m_state->OnResourceGroupReset( *this, a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnCallflowAvailable(ACallflowSptr a_callflow)
//
// Description: Delegate the OnCallflowAvailable event to the state machine
//
// Return: void
//
// Parameters: ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnCallflowAvailable( ACallflowSptr a_callflow)
{
   m_state->OnCallflowAvailable( *this, a_callflow);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnCallflowReset(ACallflowSptr a_callflow)
//
// Description: Delegate the OnCallflowReset event to the state machine
//
// Return: void
//
// Parameters: ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnCallflowReset( ACallflowSptr a_callflow)
{
   m_state->OnCallflowReset( *this, a_callflow);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnCallDisconnected(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnCallDisconnected event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnCallDisconnected( const ASipResourceSptr& a_sipResource)
{
   m_state->OnCallDisconnected( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicStop()
//
// Description: Delegate the Stop command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicStop()
{
   m_state->Stop( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnCallflowManagerStopped(int a_result)
//
// Description: Delegate the OnCallflowManagerStopped event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnCallflowManagerStopped( int a_result)
{
   m_state->OnCallflowManagerStopped( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnResourceGroupManagerStopped(int a_result)
//
// Description: Delegate the OnResourceGroupManagerStopped event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnResourceGroupManagerStopped( int a_result)
{
   m_state->OnResourceGroupManagerStopped( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnSipResourceManagerStopped(int a_result)
//
// Description: Delegate the OnSipResourceManagerStopped event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnSipResourceManagerStopped( int a_result)
{
   m_state->OnSipResourceManagerStopped( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceManager::BasicOnStopped(int a_result)
//
// Description: Delegate the OnStopped event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AResourceManager::BasicOnStopped( int a_result)
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
void AResourceManager::SetStateToStopped() { m_state = &m_stoppedState;}
void AResourceManager::SetStateToStarting() { m_state = &m_startingState;}
void AResourceManager::SetStateToStarted() { m_state = &m_startedState;}
void AResourceManager::SetStateToStopping() { m_state = &m_stoppingState;}


