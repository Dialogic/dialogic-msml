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
// File Name: RemoteMediaControlClientStates.h
//
// Description: Remote Media Control Client state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef RemoteMediaControlClientStates_h
#define RemoteMediaControlClientStates_h

class ARemoteMediaControlClient;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ARmcClientState
//
// Description: The abstract Remote Media Control Client State class and all 
// concrete subclasses comprise a State Pattern implementation of the Remote 
// Media Control Client state machine.  
//
// The abstract Remote Media Control Client state declares all functions 
// supported by the state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class ARmcClientState
{
public:
   virtual const char* StateDesc() = 0;
   virtual int Start( ARemoteMediaControlClient& a_client) { return -1;}
   virtual int OnResourceManagerStarted( ARemoteMediaControlClient& a_client, int a_result) { return -1;}
   virtual int OnHttpManagerStarted( ARemoteMediaControlClient& a_client, int a_result) { return -1;}
   virtual int OnManagerStarted( ARemoteMediaControlClient& a_client, int a_result)  { return -1;}
   virtual int OnStartup( ARemoteMediaControlClient& a_client, int a_result) { return -1;}
   virtual int Stop( ARemoteMediaControlClient& a_client) { return -1;}
   virtual int OnResourceManagerStopped( ARemoteMediaControlClient& a_client, int a_result) { return -1;}
   virtual int OnHttpManagerStopped( ARemoteMediaControlClient& a_client, int a_result) { return -1;}
   virtual int OnManagerStopped( ARemoteMediaControlClient& a_client, int a_result)  { return -1;}
protected:
   static const int NO_MANAGERS;
   static const int RESOURCE_MANAGER;
   static const int HTTP_MANAGER;
   static const int ALL_MANAGERS;
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CRmcClientStoppedState
//
// Description: Remote Media Control Client stopped state
//
///////////////////////////////////////////////////////////////////////////////
class CRmcClientStoppedState : public ARmcClientState
{
public:
   const char* StateDesc() { return "Stopped"; }
   int Start( ARemoteMediaControlClient& a_client);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CRmcClientStartingState
//
// Description: Remote Media Control Client starting state
//
///////////////////////////////////////////////////////////////////////////////
class CRmcClientStartingState : public ARmcClientState
{
public:
   const char* StateDesc() { return "Starting"; }
   int OnResourceManagerStarted( ARemoteMediaControlClient& a_client, int a_result);
   int OnHttpManagerStarted( ARemoteMediaControlClient& a_client, int a_result);
   int OnManagerStarted( ARemoteMediaControlClient& a_client, int a_result);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CRmcClientStartedState
//
// Description: Remote Media Control Client started state
//
///////////////////////////////////////////////////////////////////////////////
class CRmcClientStartedState : public ARmcClientState
{
public:
   const char* StateDesc() { return "Started"; }
   int OnStartup( ARemoteMediaControlClient& a_client, int a_result);
   int Stop( ARemoteMediaControlClient& a_client);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CRmcClientStoppingState
//
// Description: Remote Media Control Client stopping state
//
///////////////////////////////////////////////////////////////////////////////
class CRmcClientStoppingState : public ARmcClientState
{
public:
   const char* StateDesc() { return "Stopping"; }
   int OnResourceManagerStopped( ARemoteMediaControlClient& a_client, int a_result);
   int OnHttpManagerStopped( ARemoteMediaControlClient& a_client, int a_result);
   int OnManagerStopped( ARemoteMediaControlClient& a_client, int a_result);
};

#endif
