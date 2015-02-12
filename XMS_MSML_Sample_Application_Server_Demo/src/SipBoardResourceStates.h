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
// File Name: SipBoardResourceStates.h
//
// Description: SIP Board Resource state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef SipBoardResourceStates_h
#define SipBoardResourceStates_h

#include "TypeDefs.h"
#include <string>

///////////////////////////////////////////////////////////////////////////////
// Class: ::ASipBoardResourceState
//
// Description: The abstract SIP Board Resource State class and all concrete 
// subclasses comprise a State Pattern implementation of the SIP Board Resource 
// state machine.  
//
// The abstract SIP Board Resource state declares all functions supported by 
// the state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class ASipBoardResourceState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void Open( ASipBoardResource& a_sipBoardResource);
   virtual void OnOpened( ASipBoardResource& a_sipBoardResource, const CMetaEventSptr& a_metaEvent);
   virtual void Close( ASipBoardResource& a_sipBoardResource);
   virtual void OnClosed( ASipBoardResource& a_sipBoardResource);

private:
   void LogInvalidStateForCommand( ASipBoardResource& a_sipBoardResource, const char* a_command);
   void LogInvalidStateForEvent( ASipBoardResource& a_sipBoardResource, const char* a_event);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipBoardResourceClosedState
//
// Description: SIP Board Resource closed state
//
///////////////////////////////////////////////////////////////////////////////
class CSipBoardResourceClosedState : public ASipBoardResourceState
{
public:
   const char* StateDesc() { return "Closed"; }
   void Open( ASipBoardResource& a_sipBoardResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipBoardResourceOpeningState
//
// Description: SIP Board Resource opening state
//
///////////////////////////////////////////////////////////////////////////////
class CSipBoardResourceOpeningState : public ASipBoardResourceState
{
public:
   const char* StateDesc() { return "Opening"; }
   void OnOpened( ASipBoardResource& a_sipBoardResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipBoardResourceOpenedState
//
// Description: SIP Board Resource opened state
//
///////////////////////////////////////////////////////////////////////////////
class CSipBoardResourceOpenedState : public ASipBoardResourceState
{
public:
   virtual const char* StateDesc() { return "Opened"; }
   void Close( ASipBoardResource& a_sipBoardResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipBoardResourceClosingState
//
// Description: SIP Board Resource closing state
//
///////////////////////////////////////////////////////////////////////////////
class CSipBoardResourceClosingState : public ASipBoardResourceState
{
public:
   const char* StateDesc() { return "Closing"; }
   void OnClosed( ASipBoardResource& a_sipBoardResource);
};

#endif
