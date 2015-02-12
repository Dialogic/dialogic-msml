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
// File Name: CallflowManagerStates.h
//
// Description: Callflow Manager state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CallflowManagerStates_h
#define CallflowManagerStates_h

#include "TypeDefs.h"

class ACallflowManager;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ACallflowManagerState
//
// Description: The abstract Callflow State class and all concrete subclasses 
// comprise a State Pattern implementation of the Callflow Manager state 
// machine.  
//
// The abstract Callflow Manager state declares all functions supported by the 
// state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class ACallflowManagerState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void Start( ACallflowManager& a_manager);
   virtual void OnStarted( ACallflowManager& a_manager, int a_result);
   virtual void GetCallflow( ACallflowManager& a_manager, AResourceGroupSptr a_resourceGroup);
   virtual void ResetCallflow( ACallflowManager& a_manager, ACallflowSptr a_callflow);
   virtual void Stop( ACallflowManager& a_manager);
   virtual void OnStopped( ACallflowManager& a_manager, int a_result);

private:
   void LogInvalidStateForCommand( ACallflowManager& a_manager, const char* a_command, const std::string& a_msg);
   void LogInvalidStateForEvent( ACallflowManager& a_manager, const char* a_event, const std::string& a_msg);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowManagerStoppedState
//
// Description: Callflow Manager stopped state
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowManagerStoppedState : public ACallflowManagerState
{
public:
   const char* StateDesc() { return "Stopped";}
   void Start( ACallflowManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowManagerStartingState
//
// Description: Callflow Manager starting state
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowManagerStartingState : public ACallflowManagerState
{
public:
   const char* StateDesc() { return "Starting";}
   void OnStarted( ACallflowManager& a_manager, int a_result);
   void Stop( ACallflowManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowManagerStartedState
//
// Description: Callflow Manager started state
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowManagerStartedState : public ACallflowManagerState
{
public:
   const char* StateDesc() { return "Started";}
   void GetCallflow( ACallflowManager& a_manager, AResourceGroupSptr a_resourceGroup);
   void ResetCallflow( ACallflowManager& a_manager, ACallflowSptr a_callflow);
   void Stop( ACallflowManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowManagerStoppingState
//
// Description: Callflow Manager stopping state
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowManagerStoppingState : public ACallflowManagerState
{
public:
   const char* StateDesc() { return "Stopping";}
   void OnStopped( ACallflowManager& a_manager, int a_result);
};

#endif
