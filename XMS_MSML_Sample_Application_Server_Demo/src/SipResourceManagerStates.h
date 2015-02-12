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
// File Name: SipResourceManagerStates.h
//
// Description: SIP Resource Manager state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef SipResourceManagerStates_h
#define SipResourceManagerStates_h

#include "TypeDefs.h"

#include <boost/shared_ptr.hpp>

class ASipResourceManager;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ASipResourceManagerState
//
// Description: The abstract SIP Resource Manager State class and all concrete 
// subclasses comprise a State Pattern implementation of the SIP Resource 
// Manager state machine.  
//
// The abstract SIP Resource Manager state declares all functions supported by 
// the state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class ASipResourceManagerState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void Start( ASipResourceManager& a_manager);
   virtual void OnSrlEventManagerStarted( ASipResourceManager& a_manager, int a_result);
   virtual void OnSipBoardResourceOpened( ASipResourceManager& a_manager, const ASipBoardResourceSptr& a_sipBoardResource);
   virtual void OnSipResourceOpened( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   virtual void OnStarted( ASipResourceManager& a_manager, int a_result);
   virtual void EnableInboundCalls( ASipResourceManager& a_manager);
   virtual void OnCallOffered( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   virtual void OnCallDisconnected( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   virtual void Stop( ASipResourceManager& a_manager);
   virtual void OnSipResourceClosed( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   virtual void OnSipBoardResourceClosed( ASipResourceManager& a_manager, const ASipBoardResourceSptr& a_sipBoardResource);
   virtual void OnSrlEventManagerStopped( ASipResourceManager& a_manager, int a_result);
   virtual void OnStopped( ASipResourceManager& a_manager, int a_result);

private:
   void LogInvalidStateForCommand( ASipResourceManager& a_manager, const char* a_command, const std::string& a_msg);
   void LogInvalidStateForEvent( ASipResourceManager& a_manager, const char* a_event, const std::string& a_msg);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceManagerStoppedState
//
// Description: SIP Resource Manager stopped state
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceManagerStoppedState : public ASipResourceManagerState
{
public:
   const char* StateDesc() { return "Stopped"; }
   void Start( ASipResourceManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceManagerStartingSrlEventManagerState
//
// Description: SIP Resource Manager starting state
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceManagerStartingSrlEventManagerState : public ASipResourceManagerState
{
public:
   const char* StateDesc() { return "Starting Event Mgr"; }
   void OnSrlEventManagerStarted( ASipResourceManager& a_manager, int a_result);
   void Stop( ASipResourceManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceManagerOpeningSipBoardResourceState
//
// Description: Opening the SIP Board Resource
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceManagerOpeningSipBoardResourceState : public ASipResourceManagerState
{
public:
   const char* StateDesc() { return "Opening SipBoardRes"; }
   void OnSipBoardResourceOpened( ASipResourceManager& a_manager, const ASipBoardResourceSptr& a_sipBoardResource);
   void Stop( ASipResourceManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceManagerOpeningSipResourcesState
//
// Description: Opening the SIP resources
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceManagerOpeningSipResourcesState : public ASipResourceManagerState
{
public:
   const char* StateDesc() { return "Opening SipResources"; }
   void OnSipResourceOpened( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   void OnStarted( ASipResourceManager& a_manager, int a_result);
   void Stop( ASipResourceManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceManagerStartedState
//
// Description: SIP Resource Manager started state
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceManagerStartedState : public ASipResourceManagerState
{
public:
   const char* StateDesc() { return "Started"; }
   void EnableInboundCalls( ASipResourceManager& a_manager);
   void OnCallOffered( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
   void OnCallDisconnected( ASipResourceManager& a_manager, const ASipResourceSptr&  a_sipResource);
   void Stop( ASipResourceManager& a_manager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceManagerClosingSipResourcesState
//
// Description: Closing SIP resources
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceManagerClosingSipResourcesState : public ASipResourceManagerState
{
public:
   const char* StateDesc() { return "Closing SipResources"; }
   void OnSipResourceClosed( ASipResourceManager& a_manager, const ASipResourceSptr& a_sipResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceManagerClosingSipBoardResourceState
//
// Description: Closing SIP Board resources
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceManagerClosingSipBoardResourceState : public ASipResourceManagerState
{
public:
   const char* StateDesc() { return "Closing SipBoardRes"; }
   void OnSipBoardResourceClosed( ASipResourceManager& a_manager, const ASipBoardResourceSptr& a_sipBoardResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceManagerStoppingSrlEventManagerState
//
// Description: Stopping the SRL Event Manager
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceManagerStoppingSrlEventManagerState : public ASipResourceManagerState
{
public:
   const char* StateDesc() { return "Stopping Event Mgr"; }
   void OnSrlEventManagerStopped( ASipResourceManager& a_manager, int a_result);
   void OnStopped( ASipResourceManager& a_manager, int a_result);
};

#endif

