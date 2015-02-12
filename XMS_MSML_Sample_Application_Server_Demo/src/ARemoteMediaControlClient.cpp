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
// File Name: ARemoteMediaControlClient.cpp
//
// Description: ARemoteMediaControlClient class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "ARemoteMediaControlClient.h"

#include "CResourceManager.h"

CRmcClientStoppedState ARemoteMediaControlClient::m_stoppedState;
CRmcClientStartingState ARemoteMediaControlClient::m_startingState;
CRmcClientStartedState ARemoteMediaControlClient::m_startedState;
CRmcClientStoppingState ARemoteMediaControlClient::m_stoppingState;

///////////////////////////////////////////////////////////////////////////////
// Function: ARemoteMediaControlClient:ARemoteMediaControlClient::ARemoteMediaControlClient()
//
// Description: Initializing constructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ARemoteMediaControlClient::ARemoteMediaControlClient()
   : ATaskHandler( CTaskProcessorSptr (new CTaskProcessor()))
   , m_state( &m_stoppedState)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ARemoteMediaControlClient::~ARemoteMediaControlClient()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ARemoteMediaControlClient::~ARemoteMediaControlClient()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ARemoteMediaControlClient::Start()
//
// Description: Start the Remote Media Control Client by delegating the 
// command to the state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int ARemoteMediaControlClient::Start()
{
   return m_state->Start( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ARemoteMediaControlClient::IsStarted()
//
// Description: Test if the Remote Media Control Client is started
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ARemoteMediaControlClient::IsStarted()
{
   return m_state == &m_startedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ARemoteMediaControlClient::IsStopped()
//
// Description: Test if the Remote Media Control Client is stopped
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ARemoteMediaControlClient::IsStopped()
{
   return m_state == &m_stoppedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* ARemoteMediaControlClient::StateDesc()
//
// Description: Access a description of the current state
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* ARemoteMediaControlClient::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum ARemoteMediaControlClient::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum ARemoteMediaControlClient::LogObjectType()
{
   return LogObject_RmcClient;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ARemoteMediaControlClient::OnResourceManagerStarted(int a_result)
//
// Description: Handle the OnResourceManagerStarted event by delegating it to 
// the state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int ARemoteMediaControlClient::OnResourceManagerStarted( int a_result)
{
   return m_state->OnResourceManagerStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ARemoteMediaControlClient::OnHttpManagerStarted(int a_result)
//
// Description: Handle the OnHttpManagerStarted event by delegating it to 
// the state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int ARemoteMediaControlClient::OnHttpManagerStarted( int a_result)
{
   return m_state->OnHttpManagerStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ARemoteMediaControlClient::OnStartup(int a_result)
//
// Description: Handle the OnStartup event by delegating it to the state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int ARemoteMediaControlClient::OnStartup( int a_result)
{
   return m_state->OnStartup( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ARemoteMediaControlClient::Stop()
//
// Description: Stop the Remote Media Control Client by delegating the command 
// to the state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int ARemoteMediaControlClient::Stop()
{
   return m_state->Stop( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ARemoteMediaControlClient::OnResourceManagerStopped(int a_result)
//
// Description: Handle the OnResourceManagerStopped event by delegating it to 
// the state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int ARemoteMediaControlClient::OnResourceManagerStopped( int a_result)
{
   return m_state->OnResourceManagerStopped( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int ARemoteMediaControlClient::OnHttpManagerStopped(int a_result)
//
// Description: Handle the OnHttpManagerStopped event by delegating it to 
// the state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int ARemoteMediaControlClient::OnHttpManagerStopped( int a_result)
{
   return m_state->OnHttpManagerStopped( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
//	Function: State setting functions
//
//	Description: These functions set the current state
//
//	Return: see below
//
//	Parameters: see below
//
///////////////////////////////////////////////////////////////////////////////
void ARemoteMediaControlClient::SetStateToStopped() { m_state = &m_stoppedState;}
void ARemoteMediaControlClient::SetStateToStarting() { m_state =  &m_startingState;}
void ARemoteMediaControlClient::SetStateToStarted() { m_state = &m_startedState;}
void ARemoteMediaControlClient::SetStateToStopping() { m_state = &m_stoppingState;}
int ARemoteMediaControlClient::SubStateStatus() { return m_subStateStatus;}
void ARemoteMediaControlClient::SubStateStatus( int a_subStateStatus) { m_subStateStatus = a_subStateStatus;}

