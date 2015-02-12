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
// File Name: AGlobalCallManager.cpp
//
// Description: AGlobalCallManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "AGlobalCallManager.h"

CGlobalCallManagerStoppedState AGlobalCallManager::m_stoppedState;
CGlobalCallManagerStartedState AGlobalCallManager::m_startedState;

///////////////////////////////////////////////////////////////////////////////
// Function: AGlobalCallManager::AGlobalCallManager()
//
// Description: Default constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
AGlobalCallManager::AGlobalCallManager() : m_state( &m_stoppedState) 
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: AGlobalCallManager::~AGlobalCallManager()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
AGlobalCallManager::~AGlobalCallManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char * AGlobalCallManager::StateDesc()
//
// Description: Return a description of the current state
//
// Return: const char *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const char* AGlobalCallManager::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum AGlobalCallManager::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum AGlobalCallManager::LogObjectType()
{
   return LogObject_ResourceManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AGlobalCallManager::Start()
//
// Description: Start the GlobalCall Manager by delegating the command to the 
// state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int AGlobalCallManager::Start()
{
   return m_state->Start( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AGlobalCallManager::Stop()
//
// Description: Stop the GlobalCall Manager by delegating the command to the 
// state machine
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int AGlobalCallManager::Stop()
{
   return m_state->Stop( *this);
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
void AGlobalCallManager::SetStateToStarted() { m_state = &m_startedState;}
void AGlobalCallManager::SetStateToStopped() { m_state = &m_stoppedState;}

