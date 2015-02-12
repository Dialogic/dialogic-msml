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
///////////////////////////////////////////////////////////////////////////////// File Name: SrlEventManagerStates.h
//
// Description: SRL Event Manager state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef SrlEventManagerStates_h
#define SrlEventManagerStates_h

#include "TypeDefs.h"

class ASrlEventManager;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ASrlEventManagerState
//
// Description: The abstract SRL Event ManagerState class and all concrete 
// subclasses comprise a State Pattern implementation of the SRL Event Manager
// state machine.  
//
// The abstract SRL Event Manager state declares all functions supported by the 
// state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class ASrlEventManagerState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void Start( ASrlEventManager& a_manager);
   virtual void OnStarted( ASrlEventManager& a_manager, int a_result);
   virtual void Stop( ASrlEventManager& a_manager);
   virtual void OnStopped( ASrlEventManager& a_manager, int a_result);

private:
   void LogInvalidStateForCommand( ASrlEventManager& a_manager, const char* a_command, const std::string& a_msg);
   void LogInvalidStateForEvent( ASrlEventManager& a_manager, const char* a_event, const std::string& a_msg);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSrlEventManagerStoppedState
//
// Description: SRL Event Manager stopped state
//
///////////////////////////////////////////////////////////////////////////////
class CSrlEventManagerStoppedState : public ASrlEventManagerState
{
public:
   const char* StateDesc() { return "Stopped";}
   void Start( ASrlEventManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSrlEventManagerStartingState
//
// Description: SRL Event Manager starting state
//
///////////////////////////////////////////////////////////////////////////////
class CSrlEventManagerStartingState : public ASrlEventManagerState
{
public:
   const char* StateDesc() { return "Starting";}
   void OnStarted( ASrlEventManager& a_manager, int a_result);
   void Stop( ASrlEventManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSrlEventManagerStartedState
//
// Description: SRL Event Manager started state
//
///////////////////////////////////////////////////////////////////////////////
class CSrlEventManagerStartedState : public ASrlEventManagerState
{
public:
   const char* StateDesc() { return "Started";}
   void Stop( ASrlEventManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSrlEventManagerStoppingState
//
// Description: SRL Event Manager stopping state
//
///////////////////////////////////////////////////////////////////////////////
class CSrlEventManagerStoppingState : public ASrlEventManagerState
{
public:
   const char* StateDesc() { return "Stopping";}
   void OnStopped( ASrlEventManager& a_manager, int a_result);
};

#endif

