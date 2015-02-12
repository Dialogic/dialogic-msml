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
// File Name: RemoteMediaControlClientStates.cpp
//
// Description: Implementation of the RemoteMediaControlClient state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "RemoteMediaControlClientStates.h"
#include "ARemoteMediaControlClient.h"

   const int ARmcClientState::NO_MANAGERS = 0x00;
   const int ARmcClientState::RESOURCE_MANAGER = 0x01;
   const int ARmcClientState::HTTP_MANAGER = 0x02;
   const int ARmcClientState::ALL_MANAGERS = 0x03;

///////////////////////////////////////////////////////////////////////////////
// Function: int CRmcClientStoppedState::Start(ARemoteMediaControlClient &a_client)
//
// Description: Start the Remote Media Control Client
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ARemoteMediaControlClient &a_client
//
///////////////////////////////////////////////////////////////////////////////
int CRmcClientStoppedState::Start( ARemoteMediaControlClient& a_client)
{
   a_client.SubStateStatus(NO_MANAGERS);
   a_client.SetStateToStarting();
   int l_res = a_client.PrimStart();
   if ( l_res == 0)
   {
      a_client.SetStateToStarting();
   }
   return l_res;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRmcClientStartingState::OnResourceManagerStarted(ARemoteMediaControlClient &a_client, int a_result)
//
// Description: Handle a Resource Manager Started event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ARemoteMediaControlClient &a_client
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRmcClientStartingState::OnResourceManagerStarted( ARemoteMediaControlClient& a_client, int a_result)
{
   a_client.SubStateStatus( a_client.SubStateStatus() | RESOURCE_MANAGER);
   return OnManagerStarted( a_client, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRmcClientStartingState::OnHttpManagerStarted(ARemoteMediaControlClient &a_client, int a_result)
//
// Description: Handle an HTTP Manager Started event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ARemoteMediaControlClient &a_client
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRmcClientStartingState::OnHttpManagerStarted( ARemoteMediaControlClient& a_client, int a_result)
{
   a_client.SubStateStatus(a_client.SubStateStatus() | HTTP_MANAGER);
   return OnManagerStarted( a_client, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRmcClientStartingState::OnManagerStarted(ARemoteMediaControlClient &a_client, int a_result)
//
// Description: Handle a Manager Started event and check if all managers have started
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ARemoteMediaControlClient &a_client
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRmcClientStartingState::OnManagerStarted( ARemoteMediaControlClient& a_client, int a_result)
{
   int l_res(0);
   if (a_client.SubStateStatus() == ALL_MANAGERS)
   {
      l_res = a_client.PrimOnManagersStarted( a_result);
      if (l_res == 0)
      {
         a_client.SetStateToStarted();
      }
   }
   return l_res;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRmcClientStartedState::OnStartup(ARemoteMediaControlClient &a_client, int a_result)
//
// Description: Handle the Remote Media Control Client Startup completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ARemoteMediaControlClient &a_client
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRmcClientStartedState::OnStartup( ARemoteMediaControlClient& a_client, int a_result)
{
   return a_client.PrimOnStartup( a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRmcClientStartedState::Stop(ARemoteMediaControlClient &a_client)
//
// Description: Stop the Remote Media Control Client
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ARemoteMediaControlClient &a_client
//
///////////////////////////////////////////////////////////////////////////////
int CRmcClientStartedState::Stop( ARemoteMediaControlClient& a_client)
{
   a_client.SubStateStatus(NO_MANAGERS);
   a_client.SetStateToStopping();
   int l_res = a_client.PrimStop();
   if ( l_res == 0)
   {
      a_client.SetStateToStopped();
   }
   return l_res;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRmcClientStoppingState::OnResourceManagerStopped(ARemoteMediaControlClient &a_client, int a_result)
//
// Description: Handle a Resource Manager stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ARemoteMediaControlClient &a_client
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRmcClientStoppingState::OnResourceManagerStopped( ARemoteMediaControlClient& a_client, int a_result)
{
   a_client.SubStateStatus(a_client.SubStateStatus() | RESOURCE_MANAGER);
   return OnManagerStopped( a_client, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRmcClientStoppingState::OnHttpManagerStopped(ARemoteMediaControlClient &a_client, int a_result)
//
// Description: Handle an HTTP Manager stopped completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ARemoteMediaControlClient &a_client
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRmcClientStoppingState::OnHttpManagerStopped( ARemoteMediaControlClient& a_client, int a_result)
{
   a_client.SubStateStatus(a_client.SubStateStatus() | HTTP_MANAGER);
   return OnManagerStopped( a_client, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRmcClientStoppingState::OnManagerStopped(ARemoteMediaControlClient &a_client, int a_result)
//
// Description: Handle a Manager Stopped event and check if all managers have stopped
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: ARemoteMediaControlClient &a_client
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRmcClientStoppingState::OnManagerStopped( ARemoteMediaControlClient& a_client, int a_result)
{
   int l_res(0);
   if (a_client.SubStateStatus() == ALL_MANAGERS)
   {
      l_res = a_client.PrimOnManagersStopped( a_result);
      if (l_res == 0)
      {
         a_client.SetStateToStopped();
      }
   }
   return l_res;
}

