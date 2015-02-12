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
// File Name: AHttpManager.h
//
// Description: AHttpManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef AHttpManager_h
#define AHttpManager_h

#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "HttpManagerStates.h"

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::EnumHttpManagerNotifications
//
// Description: Observer notifications supported by the HTTP Manager
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   HTTP_MANAGER_STARTED,
   HTTP_MANAGER_STOPPED,
} EnumHttpManagerNotifications;

///////////////////////////////////////////////////////////////////////////////
// Class: ::AHttpManager
//
// Description: The abstract HTTP Manager class implements the public 
// interface and state machine for the concrete HTTP Manager class.  
// The HTTP Manager is a singleton responsible for asynchronously processing 
// HTTP requests.
//
///////////////////////////////////////////////////////////////////////////////
class AHttpManager : public ATaskHandler, public AObserverSubject
{
   friend class AHttpManagerState;
   friend class CHttpManagerStoppedState;
   friend class CHttpManagerStartingState;
   friend class CHttpManagerStartedState;
   friend class CHttpManagerStoppingState;

public:
   AHttpManager( CTaskProcessorSptr a_taskProcessor);
   virtual ~AHttpManager();

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

   void Start();
   void OnStarted( int a_result);
   void Stop();
   void OnStopped( int a_result);

   bool IsStopped();

protected:
   AHttpManager();
   
   virtual int PrimStart() = 0;
   virtual int PrimOnStarted( int a_result) = 0;
   virtual int PrimStop() = 0;
   virtual int PrimOnStopped( int a_result) = 0;

   bool IsStopping();

private:
   void BasicStart();
   void BasicOnStarted( int a_result);
   void BasicStop();
   void BasicOnStopped( int a_result);

   void SetStateToStarting();
   void SetStateToStarted();
   void SetStateToStopped();
   void SetStateToStopping();

   AHttpManagerState* m_state;
   static CHttpManagerStoppedState m_stoppedState;
   static CHttpManagerStartingState m_startingState;
   static CHttpManagerStartedState m_startedState;
   static CHttpManagerStoppingState m_stoppingState;
};

#endif

