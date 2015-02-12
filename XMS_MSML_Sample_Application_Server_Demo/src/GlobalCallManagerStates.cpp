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
// File Name: GlobalCallManagerStates.cpp
//
// Description: Implementation of the GlobalCallManager state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "GlobalCallManagerStates.h"
#include "AGlobalCallManager.h"

///////////////////////////////////////////////////////////////////////////////
// Function: int AGlobalCallManagerState::Start(AGlobalCallManager &a_globalCallManager)
//
// Description:  Start command is invalid in this state
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AGlobalCallManager &a_globalCallManager
//
///////////////////////////////////////////////////////////////////////////////
int AGlobalCallManagerState::Start( AGlobalCallManager& a_globalCallManager)
{
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AGlobalCallManagerState::Stop(AGlobalCallManager &a_globalCallManager)
//
// Description:  Stop command is invalid in this state
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AGlobalCallManager &a_globalCallManager
//
///////////////////////////////////////////////////////////////////////////////
int AGlobalCallManagerState::Stop( AGlobalCallManager& a_globalCallManager)
{
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char * CGlobalCallManagerStoppedState::StateDesc()
//
// Description: Return a description of the state
//
// Return: const char *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const char* CGlobalCallManagerStoppedState::StateDesc()
{
   return "Stopped";
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CGlobalCallManagerStoppedState::Start(AGlobalCallManager &a_globalCallManager)
//
// Description: Start the GlobalCall Manager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AGlobalCallManager &a_globalCallManager
//
///////////////////////////////////////////////////////////////////////////////
int CGlobalCallManagerStoppedState::Start( AGlobalCallManager& a_globalCallManager)
{
   int l_result = a_globalCallManager.PrimStart();
   if ( l_result == 0)
   {
      a_globalCallManager.SetStateToStarted();
   }
   return l_result;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char * CGlobalCallManagerStartedState::StateDesc()
//
// Description: Return a description of the state
//
// Return: const char *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const char* CGlobalCallManagerStartedState::StateDesc()
{
   return "Started";
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CGlobalCallManagerStartedState::Stop(AGlobalCallManager &a_globalCallManager)
//
// Description: Stop the GlobalCall Manager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: AGlobalCallManager &a_globalCallManager
//
///////////////////////////////////////////////////////////////////////////////
int CGlobalCallManagerStartedState::Stop( AGlobalCallManager& a_globalCallManager)
{
   int l_result = a_globalCallManager.PrimStop();
   if ( l_result == 0)
   {
      a_globalCallManager.SetStateToStopped();
   }
   return l_result;
}
