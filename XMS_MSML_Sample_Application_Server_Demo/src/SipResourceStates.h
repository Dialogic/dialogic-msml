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
// File Name: SipResourceStates.h
//
// Description: SIP Resource state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef SipResourceStates_h
#define SipResourceStates_h

#include "TypeDefs.h"
#include <string>

///////////////////////////////////////////////////////////////////////////////
// Class: ::ASipResourceState
//
// Description: The abstract SIP Resource State class and all concrete 
// subclasses comprise a State Pattern implementation of the SIP Resource state 
// machine.  
//
// The abstract SIP Resource state declares all functions supported by the 
// state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class ASipResourceState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void Open( ASipResource& a_sipResource, const CSrlEventManagerSptr& a_srlEventManager);
   virtual void OnOpened( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void OnSetConfigData( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void OnUnblocked( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void EnableInboundCalls( ASipResource& a_sipResource);
   virtual void OnBlocked( ASipResource& a_sipResource);
   virtual void Close( ASipResource& a_sipResource);
   virtual void OnClosed( ASipResource& a_sipResource);

   virtual void OnOffered( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent);
   virtual void OnReqModifyCall( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent);
   virtual void Reject( ASipResource& a_sipResource, int a_code);
   virtual void Accept( ASipResource& a_sipResource);
   virtual void OnAccepted( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void Answer( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void OnAnswered( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void OnAck( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void OnDisconnect( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void DropCall( ASipResource& a_sipResource);
   virtual void OnCallDropped( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void ReleaseCall( ASipResource& a_sipResource);
   virtual void OnCallReleased( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);

   virtual void MakeCall( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void OnDialing( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void OnAlerting( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void OnConnected( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void On200Ok( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void OnAckOk( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);

   virtual void OnInfoMessage( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void SendInfoMessageResponse( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void SendInfoMessage( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void OnExtension( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   virtual void OnExtensionComplete( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);

   virtual void OnTaskFail( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);

   virtual void Disconnect( ASipResource& a_sipResource);

private:
   void LogInvalidStateForCommand( ASipResource& a_sipResource, const char* a_command);
   void LogInvalidStateForEvent( ASipResource& a_sipResource, const char* a_event);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceClosedState
//
// Description: SIP Resource closed state
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceClosedState : public ASipResourceState
{
public:
   const char* StateDesc() { return "Closed"; }
   void Open( ASipResource& a_sipResource, const CSrlEventManagerSptr& a_srlEventManager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceOpeningState
//
// Description: SIP Resource opening state
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceOpeningState : public ASipResourceState
{
public:
   const char* StateDesc() { return "Opening"; }
   void OnOpened( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   void OnSetConfigData( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceBlockedState
//
// Description: SIP Resource blocked state
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceBlockedState : public ASipResourceState
{
public:
   const char* StateDesc() { return "Blocked"; }
   void OnSetConfigData( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   void OnUnblocked( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   void Close( ASipResource& a_sipResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceUnblockedState
//
// Description: SIP Resource unblocked state
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceUnblockedState : public ASipResourceState
{
public:
   virtual const char* StateDesc() { return "Unblocked"; }
   void OnSetConfigData( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   void EnableInboundCalls( ASipResource& a_sipResource);
   void OnOffered( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent);
   void MakeCall( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo);
   void OnBlocked( ASipResource& a_sipResource);
   void Close( ASipResource& a_sipResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::ASipResourceActiveCallState
//
// Description: Abstract SIP Resource state class for functionality common to 
// all states whre there is an active all.
//
///////////////////////////////////////////////////////////////////////////////
class ASipResourceActiveCallState : public CSipResourceUnblockedState
{
   void OnReqModifyCall( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent);
   void OnDisconnect( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent);
   void DropCall( ASipResource& a_sipResource);
   void Disconnect( ASipResource& a_sipResource);
   void Close( ASipResource& a_sipResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceOfferedState
//
// Description: Call offered
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceOfferedState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Call offered"; }
   void Reject( ASipResource& a_sipResource, int a_code);
   void Accept( ASipResource& a_sipResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceAcceptingState
//
// Description: Accepting inbound call
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceAcceptingState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Accepting call"; }
   void OnAccepted( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceAcceptedState
//
// Description: Inbound call has been accepted
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceAcceptedState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Call accepted"; }
   void Answer( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceAnsweringState
//
// Description: Answering an inbound call
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceAnsweringState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Answering call"; }
   void OnAnswered( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent);
   void OnAck( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceAnsweredState
//
// Description: Inbound call has been answered
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceAnsweredState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Call answered"; }
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceDroppingState
//
// Description: Call is being Dropped
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceDroppingState : public CSipResourceUnblockedState
{
public:
   const char* StateDesc() { return "Dropping Call"; }
   void OnCallDropped( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceDroppedState
//
// Description: Call has been dropped
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceDroppedState : public CSipResourceUnblockedState
{
public:
   const char* StateDesc() { return "Call dropped"; }
   void ReleaseCall( ASipResource& a_sipResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceReleasingState
//
// Description: Releasing the call
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceReleasingState : public CSipResourceUnblockedState
{
public:
   const char* StateDesc() { return "Releasing call"; }
   void OnCallReleased( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceMakingCallState
//
// Description: Attempting an outbound call
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceMakingCallState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Making Call"; }
   void OnDialing( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceDialingState
//
// Description: The outbound call is being "dialed"
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceDialingState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Dialing"; }
   void OnAlerting( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceAlertingState
//
// Description: The outbound call is alerting
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceAlertingState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Alerting"; }
   void OnConnected( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   void On200Ok( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceAcking200OkState
//
// Description: Acking a 200OK message
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceAcking200OkState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Acking 200OK"; }
   void OnAckOk( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceConnectedState
//
// Description: The outbound call has been connected
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceConnectedState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Connected"; }
   void OnInfoMessage( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   void SendInfoMessage( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceInfoMessageReceivedState
//
// Description: A SIP INFO message has been received
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceInfoMessageReceivedState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "INFO received"; }
   virtual void SendInfoMessageResponse( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceSendingInfoMessageResponseState
//
// Description: Sending the response to a SIP info message
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceSendingInfoMessageResponseState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "INFO response"; }
   void OnExtensionComplete( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceSendingInfoMessageState
//
// Description: Sending a SIP info message
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceSendingInfoMessageState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Sending INFO"; }
   void OnExtensionComplete( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourcePendingInfoMessageResponseState
//
// Description: SIP INFO message sent, waiting for a response
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourcePendingInfoMessageResponseState : public ASipResourceActiveCallState
{
public:
   const char* StateDesc() { return "Pending INFO response"; }
   void OnExtension( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceClosingState
//
// Description: SIP Resource closing state
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceClosingState : public ASipResourceState
{
public:
   const char* StateDesc() { return "Closing"; }
   void OnCallDropped( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   void ReleaseCall( ASipResource& a_sipResource);
   void OnCallReleased( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent);
   void OnClosed( ASipResource& a_sipResource);
};

#endif
