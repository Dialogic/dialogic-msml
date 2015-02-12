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
// File Name: HttpManagerStates.h
//
// Description: Http Manager state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef HttpManagerStates_h
#define HttpManagerStates_h

#include "TypeDefs.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::AHttpManagerState
//
// Description: The abstract HTTP Manager State class and all concrete 
// subclasses comprise a State Pattern implementation of the HTTP Manager
// state machine.  
//
// The abstract HTTP Manager state declares all functions supported by 
// the state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class AHttpManagerState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void Start( AHttpManager& a_HttpManager);
   virtual void OnStarted( AHttpManager& a_HttpManager, int a_result);
   virtual void Stop( AHttpManager& a_HttpManager);
   virtual void OnStopped( AHttpManager& a_HttpManager, int a_result);

private:
   void LogInvalidStateForCommand( AHttpManager& a_manager, const char*  a_command, const std::string& a_msg);
   void LogInvalidStateForEvent( AHttpManager& a_manager, const char*  a_event, const std::string& a_msg);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CHttpManagerStoppedState
//
// Description: HTTP Manager stopped state
//
///////////////////////////////////////////////////////////////////////////////
class CHttpManagerStoppedState : public AHttpManagerState
{
public:
   const char* StateDesc();
   virtual void Start( AHttpManager& a_HttpManager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CHttpManagerStartingState
//
// Description: HTTP Manager starting state
//
///////////////////////////////////////////////////////////////////////////////
class CHttpManagerStartingState : public AHttpManagerState
{
public:
   const char* StateDesc();
   void OnStarted( AHttpManager& a_manager, int a_result);
   void Stop( AHttpManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CHttpManagerStartedState
//
// Description: HTTP Manager started state
//
///////////////////////////////////////////////////////////////////////////////
class CHttpManagerStartedState : public AHttpManagerState
{
public:
   const char* StateDesc();
   void Stop( AHttpManager& a_HttpManager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CHttpManagerStoppingState
//
// Description: HTTP Manager stopping state
//
///////////////////////////////////////////////////////////////////////////////
class CHttpManagerStoppingState : public AHttpManagerState
{
public:
   const char* StateDesc();
   void OnStopped( AHttpManager& a_manager, int a_result);
};

#endif

