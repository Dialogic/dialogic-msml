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
// File Name: ARemoteMediaControlClient.h
//
// Description: ARemoteMediaControlClient class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ARemoteMediaControlClient_h
#define ARemoteMediaControlClient_h

#include "TypeDefs.h"
#include "ATaskHandler.h"
#include "CTaskProcessor.h"
#include "RemoteMediaControlClientStates.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::ARemoteMediaControlClient
//
// Description: The abstract Remote Media Client class implements the public 
// interface and state machine for the concrete Remote Media Client class.
// The Remote Media Client is responsible for starting the application logger,
// task processor and resource manger.
//
///////////////////////////////////////////////////////////////////////////////
class ARemoteMediaControlClient : public ATaskHandler
{
   friend class ARmcClientState;
   friend class CRmcClientStoppedState;
   friend class CRmcClientStartingState;
   friend class CRmcClientStartedState;
   friend class CRmcClientStoppingState;

public:
   virtual ~ARemoteMediaControlClient();

   int Start();
   int OnResourceManagerStarted( int a_result);
   int OnHttpManagerStarted( int a_result);
   int OnStartup( int a_result);
   int Stop();
   int OnResourceManagerStopped( int a_result);
   int OnHttpManagerStopped( int a_result);

   bool IsStarted();
   bool IsStopped();

   int SubStateStatus();
   void SubStateStatus( int a_subStateStatus);

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

protected:
   ARemoteMediaControlClient();

   virtual int PrimStart() = 0;
   virtual int PrimOnManagersStarted( int a_result) = 0;
   virtual int PrimOnStartup( int a_result) = 0;
   virtual int PrimStop() = 0;
   virtual int PrimOnManagersStopped( int a_result) = 0;

private:
   void SetStateToStopped();
   void SetStateToStarting();
   void SetStateToStarted();
   void SetStateToStopping();

   ARmcClientState* m_state;
   static CRmcClientStoppedState m_stoppedState;
   static CRmcClientStartingState m_startingState;
   static CRmcClientStartedState m_startedState;
   static CRmcClientStoppingState m_stoppingState;

   int m_subStateStatus;
};

#endif


