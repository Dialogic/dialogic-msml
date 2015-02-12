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
// File Name: ASrlEventManager.cpp
//
// Description: ASrlEventManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "ASrlEventManager.h"
#include "CTask.h"
#include "CTaskProcessor.h"
#include "AResourceGroup.h"

CSrlEventManagerStoppedState ASrlEventManager::m_stoppedState;;
CSrlEventManagerStartingState ASrlEventManager::m_startingState;
CSrlEventManagerStartedState ASrlEventManager::m_startedState;
CSrlEventManagerStoppingState ASrlEventManager::m_stoppingState;

///////////////////////////////////////////////////////////////////////////////
// Function: ASrlEventManager::ASrlEventManager()
//
// Description: Default constructor - should never be called.  Always use the
// initializing constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ASrlEventManager::ASrlEventManager()
{
   assert(0);
}

///////////////////////////////////////////////////////////////////////////////
// Function: ASrlEventManager::ASrlEventManager( CTaskProcessorSptr& a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr& a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
ASrlEventManager::ASrlEventManager( CTaskProcessorSptr& a_taskProcessor)
      : ATaskHandler( a_taskProcessor)
      , m_state( &m_stoppedState)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ASrlEventManager::ASrlEventManager( CTaskProcessorSptr& a_taskProcessor)
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ASrlEventManager::~ASrlEventManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* ASrlEventManager::StateDesc()
//
// Description: Access a description of the current state
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* ASrlEventManager::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum ASrlEventManager::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum ASrlEventManager::LogObjectType()
{
   return LogObject_EventManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ASrlEventManager::IsStarted()
//
// Description: Test if the SRL Event Manager is started
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ASrlEventManager::IsStarted()
{
   return m_state == &m_startedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ASrlEventManager::IsStopping()
//
// Description: Test if the SRL Event Manager is stopping
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ASrlEventManager::IsStopping()
{
   return m_state == &m_stoppingState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ASrlEventManager::IsStopped()
//
// Description: Test if the SRL Event Manager is stopped
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ASrlEventManager::IsStopped()
{
   return m_state == &m_stoppedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManager::Start()
//
// Description: Queue a task to start the SRL Event Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManager::Start()
{
   LogDebug( "Start");
   ATaskSptr l_task( new CTask0( boost::bind( &ASrlEventManager::BasicStart, this),
                                              "ASrlEventManager::BasicStart"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManager::OnStarted(int a_result)
//
// Description: Queue a task to handle the SRL Event Manager started completion 
// event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManager::OnStarted( int a_result)
{
   LogDebugResult( "OnStarted", a_result);
   ATaskSptr l_task( new CTask1<int>( boost::bind( &ASrlEventManager::BasicOnStarted, this, _1), 
                                                   a_result,
                                                   "ASrlEventManager::BasicOnStarted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManager::Stop()
//
// Description: Queue a task to stop the SRL Event Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManager::Stop()
{
   LogDebug( "Stop");
   ATaskSptr l_task( new CTask0( boost::bind( &ASrlEventManager::BasicStop, this), 
                                              "ASrlEventManager::BasicStop"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManager::OnStopped(int a_result)
//
// Description: Queue a task to handle the SRL Event Manager stopped completion 
// event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManager::OnStopped( int a_result)
{
   LogDebugResult( "OnStopped", a_result);
   ATaskSptr l_task( new CTask1<int>( boost::bind( &ASrlEventManager::BasicOnStopped, this, _1),
                                                   a_result,
                                                   "ASrlEventManager::BasicOnStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManager::BasicStart()
//
// Description: Delegate the Start command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManager::BasicStart()
{
   m_state->Start( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManager::BasicOnStarted(int a_result)
//
// Description: Delegate the OnStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManager::BasicOnStarted( int a_result)
{
   m_state->OnStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManager::BasicStop()
//
// Description: Delegate the Stop command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManager::BasicStop()
{
   m_state->Stop( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASrlEventManager::BasicOnStopped(int a_result)
//
// Description: Delegate the OnStopped event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASrlEventManager::BasicOnStopped( int a_result)
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
void ASrlEventManager::SetStateToStopped() { m_state = &m_stoppedState;}
void ASrlEventManager::SetStateToStarting() { m_state = &m_startingState;}
void ASrlEventManager::SetStateToStarted() { m_state = &m_startedState;}
void ASrlEventManager::SetStateToStopping() { m_state = &m_stoppingState;}


