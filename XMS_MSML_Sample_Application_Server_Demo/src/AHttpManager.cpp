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
// File Name: AHttpManager.cpp
//
// Description: AHttpManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "AHttpManager.h"
#include "CTask.h"
#include "CTaskProcessor.h"

CHttpManagerStoppedState AHttpManager::m_stoppedState;
CHttpManagerStartingState AHttpManager::m_startingState;
CHttpManagerStartedState AHttpManager::m_startedState;
CHttpManagerStoppingState AHttpManager::m_stoppingState;

///////////////////////////////////////////////////////////////////////////////
// Function: AHttpManager::AHttpManager()
//
// Description:   Default constructor - must never be called because a task 
//                processor is required
//
// Return: 
//
// Parameters: none
//
//
///////////////////////////////////////////////////////////////////////////////
AHttpManager::AHttpManager() 
{
   assert(0);
}

///////////////////////////////////////////////////////////////////////////////
// Function: AHttpManager::AHttpManager(CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
AHttpManager::AHttpManager( CTaskProcessorSptr a_taskProcessor) 
      : ATaskHandler( a_taskProcessor)
      , m_state( &m_stoppedState) 
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: AHttpManager::~AHttpManager()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
AHttpManager::~AHttpManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char * AHttpManager::StateDesc()
//
// Description: Return a description of the current state
//
// Return: const char *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const char* AHttpManager::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum AHttpManager::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum AHttpManager::LogObjectType()
{
   return LogObject_ResourceManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AHttpManager::Start()
//
// Description: Queue a task to Start the HTTP Manager
// state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManager::Start()
{
   LogDebug( "Start");
   ATaskSptr l_task( new CTask0( boost::bind( &AHttpManager::BasicStart, this),
                                              "AHttpManager::BasicStart"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AHttpManager::OnStarted()
//
// Description: Queue a task to handle an HTTP Manager Started event
// state machine
//
// Return: none
//
// Parameters: int - a_result
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManager::OnStarted(int a_result)
{
   LogDebug( "OnStarted");
   ATaskSptr l_task( new CTask1<int>(  boost::bind( &AHttpManager::BasicOnStarted, this, _1),
                                       a_result,
                                       "AHttpManager::OnStarted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AHttpManager::Stop()
//
// Description: Queue a task to Stop the HTTP Manager
// state machine
//
// Return: none
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManager::Stop()
{
   LogDebug( "Stop");
   ATaskSptr l_task( new CTask0( boost::bind( &AHttpManager::BasicStop, this),
                                              "AHttpManager::BasicStop"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AHttpManager::OnStopped()
//
// Description: Queue a task to handle an HTTP Manager Started event
// state machine
//
// Return: none
//
// Parameters: int - a_result
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManager::OnStopped(int a_result)
{
   LogDebug( "OnStopped");
   ATaskSptr l_task( new CTask1<int>(  boost::bind( &AHttpManager::BasicOnStopped, this, _1),
                                       a_result,
                                       "AHttpManager::BasicOnStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpManager::BasicStart()
//
// Description: Delegate the Start command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManager::BasicStart()
{
   m_state->Start( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpManager::BasicOnStarted(int a_result)
//
// Description: Delegate the OnStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManager::BasicOnStarted( int a_result)
{
   m_state->OnStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpManager::BasicStop()
//
// Description: Delegate the Stop command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManager::BasicStop()
{
   m_state->Stop( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpManager::BasicOnStopped(int a_result)
//
// Description: Delegate the OnStopped event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void AHttpManager::BasicOnStopped( int a_result)
{
   m_state->OnStopped( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool AHttpManager::IsStopping()
//
// Description: Test if the HTTP Manager is stopping
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool AHttpManager::IsStopping()
{
   return m_state == &m_stoppingState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool AHttpManager::IsStopped()
//
// Description: Test if the HTTP Manager is stopped
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool AHttpManager::IsStopped()
{
   return m_state == &m_stoppedState;
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
void AHttpManager::SetStateToStarting() { m_state = &m_startingState;}
void AHttpManager::SetStateToStarted() { m_state = &m_startedState;}
void AHttpManager::SetStateToStopping() { m_state = &m_stoppingState;}
void AHttpManager::SetStateToStopped() { m_state = &m_stoppedState;}

