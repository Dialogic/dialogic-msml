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
// File Name: ACallflowManager.cpp
//
// Description: ACallflowManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "ACallflowManager.h"
#include "CTask.h"
#include "CTaskProcessor.h"
#include "AResourceGroup.h"
#include "ACallflow.h"

CCallflowManagerStoppedState ACallflowManager::m_stoppedState;;
CCallflowManagerStartingState ACallflowManager::m_startingState;
CCallflowManagerStartedState ACallflowManager::m_startedState;
CCallflowManagerStoppingState ACallflowManager::m_stoppingState;

///////////////////////////////////////////////////////////////////////////////
// Function: ACallflowManager::ACallflowManager( CTaskProcessorSptr& a_taskProcessor)
//
// Description: Initial;izing constructor
//
// Return:
//
// Parameters: CTaskProcessorSptr& a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
ACallflowManager::ACallflowManager( CTaskProcessorSptr& a_taskProcessor)
   : ATaskHandler( a_taskProcessor)
   , m_state( &m_stoppedState)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ACallflowManager::~ACallflowManager()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ACallflowManager::~ACallflowManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflowManager::IsStopped()
//
// Description: Test if the Callflow Manager is stopped
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflowManager::IsStopped()
{
   return m_state == &m_stoppedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflowManager::IsStarted()
//
// Description: Test if the Callflow Manager is started
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflowManager::IsStarted()
{
   return m_state == &m_startedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* ACallflowManager::StateDesc()
//
// Description: Access the state description
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* ACallflowManager::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum ACallflowManager::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum ACallflowManager::LogObjectType()
{
   return LogObject_CallflowManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::Start()
//
// Description: Queue a task to start the Callflow Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::Start()
{
   LogDebug( "Start");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflowManager::BasicStart, this),
                                              "ACallflowManager::BasicStart"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::Stop()
//
// Description: Queue a task to stop the Callflow Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::Stop()
{
   LogDebug( "Stop");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflowManager::BasicStop, this), 
                                              "ACallflowManager::BasicStop"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::OnStarted(int a_result)
//
// Description: Queue a task to handle the started event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::OnStarted( int a_result)
{
   LogDebugResult( "OnStarted", a_result);
   ATaskSptr l_task( new CTask1<int>( boost::bind( &ACallflowManager::BasicOnStarted, this, _1), 
                                                   a_result,
                                                   "ACallflowManager::BasicOnStarted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::GetCallflow(AResourceGroupSptr a_resourceGroup)
//
// Description: Queue a task to get a callflow object
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::GetCallflow( AResourceGroupSptr a_resourceGroup)
{
   LogDebug( "GetCallflow", a_resourceGroup->Name());
   ATaskSptr l_task( new CTask1< AResourceGroupSptr>(   boost::bind( &ACallflowManager::BasicGetCallflow, this, _1), 
                                                                     a_resourceGroup,
                                                                     "ACallflowManager::BasicGetCallflow"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::ResetCallflow(ACallflowSptr a_callflow)
//
// Description: Queue a task to reset a callflow object
//
// Return: void
//
// Parameters: ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::ResetCallflow( ACallflowSptr a_callflow)
{
   LogDebug( "ResetCallflow", a_callflow->Name());
   ATaskSptr l_task( new CTask1< ACallflowSptr>(   boost::bind( &ACallflowManager::BasicResetCallflow, this, _1), 
                                                                a_callflow,
                                                                "ACallflowManager::BasicResetCallflow"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::OnStopped(int a_result)
//
// Description: Queue a task to handle the stopped event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::OnStopped( int a_result)
{
   LogDebugResult( "OnStopped", a_result);
   ATaskSptr l_task( new CTask1<int>( boost::bind( &ACallflowManager::BasicOnStopped, this, _1),
                                                   a_result,
                                                   "ACallflowManager::BasicOnStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::BasicStart()
//
// Description: Delegate the Start command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::BasicStart()
{
   m_state->Start( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::BasicOnStarted(int a_result)
//
// Description: Delegate the OnStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::BasicOnStarted( int a_result)
{
   m_state->OnStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::BasicGetCallflow(AResourceGroupSptr a_resourceGroup)
//
// Description: Delegate the GetCallflow command to the state machine
//
// Return: void
//
// Parameters: AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::BasicGetCallflow( AResourceGroupSptr a_resourceGroup)
{
   m_state->GetCallflow( *this, a_resourceGroup);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::BasicResetCallflow(ACallflowSptr a_callflow)
//
// Description: Delegate the ResetCallflow command to the state machine
//
// Return: void
//
// Parameters: ACallflowSptr a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::BasicResetCallflow( ACallflowSptr a_callflow)
{
   m_state->ResetCallflow( *this, a_callflow);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::BasicStop()
//
// Description: Delegate the Stop command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::BasicStop()
{
   m_state->Stop( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowManager::BasicOnStopped(int a_result)
//
// Description: Delegate the OnStopped event command to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowManager::BasicOnStopped( int a_result)
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
void ACallflowManager::SetStateToStopped() { m_state = &m_stoppedState;}
void ACallflowManager::SetStateToStarting() { m_state = &m_startingState;}
void ACallflowManager::SetStateToStarted() { m_state = &m_startedState;}
void ACallflowManager::SetStateToStopping() { m_state = &m_stoppingState;}

