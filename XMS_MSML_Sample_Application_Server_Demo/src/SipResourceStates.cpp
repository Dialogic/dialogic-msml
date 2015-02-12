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
// File Name: SipResourceStates.cpp
//
// Description: Implementation of the SipResource state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "SipResourceStates.h"
#include "ASipResource.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::Open(ASipResource &a_sipResource, const CSrlEventManagerSptr &a_srlEventManager)
//
// Description: Open command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSrlEventManagerSptr &a_srlEventManager
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::Open( ASipResource& a_sipResource, const CSrlEventManagerSptr& a_srlEventManager) 
{ 
   LogInvalidStateForCommand( a_sipResource, "Open");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnOpened(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnOpened event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnOpened( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent) 
{ 
   LogInvalidStateForCommand( a_sipResource, "OnOpened");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnSetConfigData(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnSetConfigData event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnSetConfigData( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent) 
{ 
   LogInvalidStateForCommand( a_sipResource, "OnSetConfigData");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnUnblocked(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnUnblocked event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnUnblocked( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent) 
{ 
   LogInvalidStateForEvent( a_sipResource, "OnUnblocked");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::EnableInboundCalls(ASipResource &a_sipResource)
//
// Description: EnableInboundCalls command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::EnableInboundCalls( ASipResource& a_sipResource) 
{ 
   LogInvalidStateForCommand( a_sipResource, "EnableInboundCalls");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnBlocked(ASipResource &a_sipResource)
//
// Description: OnBlocked event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnBlocked( ASipResource& a_sipResource) 
{ 
   LogInvalidStateForEvent( a_sipResource, "OnBlocked");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::Close(ASipResource &a_sipResource)
//
// Description: Close command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::Close( ASipResource& a_sipResource) 
{ 
   LogInvalidStateForCommand( a_sipResource, "Close");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnClosed(ASipResource &a_sipResource)
//
// Description: OnClosed event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnClosed( ASipResource& a_sipResource) 
{ 
   LogInvalidStateForEvent( a_sipResource, "OnClosed");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnOffered(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnOffered event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnOffered( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnOffered");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnOffered(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnReqModifyCall event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnReqModifyCall( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnReqModifyCall");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::Reject(ASipResource &a_sipResource, const int a_code)
//
// Description: Reject command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const int a_code
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::Reject( ASipResource& a_sipResource, const int a_code)
{ 
   LogInvalidStateForCommand( a_sipResource, "Reject");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::Accept(ASipResource &a_sipResource)
//
// Description: Accept command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::Accept( ASipResource& a_sipResource)
{ 
   LogInvalidStateForCommand( a_sipResource, "Accept");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnAccepted(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnAccepted event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnAccepted( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnAccepted");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::Answer(ASipResource &a_sipResource, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Answer command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::Answer( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo)
{ 
   LogInvalidStateForCommand( a_sipResource, "Answer");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnAnswered(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnAnswered event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnAnswered( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnAnswered");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnAck(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnAck event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnAck( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnAck");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnDisconnect(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnDisconnect event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnDisconnect( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnDisconnect");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::DropCall(ASipResource &a_sipResource)
//
// Description: DropCall command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::DropCall( ASipResource& a_sipResource)
{ 
   LogInvalidStateForCommand( a_sipResource, "DropCall");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnCallDropped(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnCallDropped event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnCallDropped( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnCallDropped");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::ReleaseCall(ASipResource &a_sipResource)
//
// Description: ReleaseCall command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::ReleaseCall( ASipResource& a_sipResource)
{ 
   LogInvalidStateForCommand( a_sipResource, "ReleaseCall");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnCallReleased(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnCallReleased event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnCallReleased( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnCallReleased");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::MakeCall(ASipResource &a_sipResource, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: MakeCall command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::MakeCall( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo)
{ 
   LogInvalidStateForCommand( a_sipResource, "MakeCall");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnDialing(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnDialing event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnDialing( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnDialing");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnAlerting(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnAlerting event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnAlerting( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnAlerting");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnConnected(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnConnected event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnConnected( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnConnected");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::On200Ok(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: On200Ok event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::On200Ok( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "On200Ok");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnAckOk(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnAckOk event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnAckOk( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnAckOk");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnInfoMessage(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnInfoMessage event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnInfoMessage( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnInfoMessage");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::SendInfoMessageResponse(ASipResource &a_sipResource, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: SendInfoMessageResponse command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::SendInfoMessageResponse( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo)
{ 
   LogInvalidStateForCommand( a_sipResource, "SendInfoMessageResponse");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::SendInfoMessage(ASipResource &a_sipResource, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: SendInfoMessage command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::SendInfoMessage( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo)
{ 
   LogInvalidStateForCommand( a_sipResource, "SendInfoMessage");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnExtension(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnExtension event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnExtension( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnExtension");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnExtensionComplete(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnExtensionComplete event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnExtensionComplete( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   LogInvalidStateForEvent( a_sipResource, "OnExtensionComplete");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::OnTaskFail(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: OnTaskFail event is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::OnTaskFail( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   a_sipResource.PrimOnTaskFail( a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::Disconnect(ASipResource &a_sipResource)
//
// Description: Disconnect command is invalid in this state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::Disconnect( ASipResource& a_sipResource)
{
   a_sipResource.PrimDisconnect();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::LogInvalidStateForCommand(ASipResource &a_sipResource, const char *a_command)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const char *a_command
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::LogInvalidStateForCommand( ASipResource& a_sipResource, const char* a_command) 
{ 
   a_sipResource.LogError( a_command, "Invalid state for command");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceState::LogInvalidStateForEvent(ASipResource &a_sipResource, const char *a_event)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const char *a_event
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceState::LogInvalidStateForEvent( ASipResource& a_sipResource, const char* a_event) 
{ 
   a_sipResource.LogError( a_event, "Invalid state for event");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceClosedState::Open(ASipResource &a_sipResource, const CSrlEventManagerSptr &a_srlEventManager)
//
// Description: Open the SIP Resource
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSrlEventManagerSptr &a_srlEventManager
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceClosedState::Open( ASipResource& a_sipResource, const CSrlEventManagerSptr& a_srlEventManager) 
{ 
   if (a_sipResource.PrimOpen( a_srlEventManager) == 0) 
   {
      a_sipResource.SetStateToOpening();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceOpeningState::OnOpened(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle the SIP Resource opened compeltion event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceOpeningState::OnOpened( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent) 
{ 
   if (a_sipResource.PrimOnOpened( a_metaEvent) == 0)   
   {
      a_sipResource.SetStateToBlocked();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceOpeningState::OnSetConfigData(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a set configuration data completion event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceOpeningState::OnSetConfigData( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent) 
{ 
   a_sipResource.PrimOnSetConfigData( a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceBlockedState::OnSetConfigData(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a blocked event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceBlockedState::OnSetConfigData( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent) 
{ 
   a_sipResource.PrimOnSetConfigData( a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceBlockedState::OnUnblocked(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an unblocked event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceBlockedState::OnUnblocked( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent) 
{ 
   if (a_sipResource.PrimOnUnblocked( a_metaEvent) == 0) 
   {
      a_sipResource.SetStateToUnblocked();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceBlockedState::Close(ASipResource &a_sipResource)
//
// Description: Close the SIP Resource
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceBlockedState::Close( ASipResource& a_sipResource) 
{ 
   if (a_sipResource.PrimClose() == 0) 
   {
      a_sipResource.SetStateToClosing();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceUnblockedState::OnSetConfigData(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a set configuration data completion event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceUnblockedState::OnSetConfigData( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent) 
{ 
   a_sipResource.PrimOnSetConfigData( a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceUnblockedState::EnableInboundCalls(ASipResource &a_sipResource)
//
// Description: Enable inbound calls on the SIP Resource
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceUnblockedState::EnableInboundCalls( ASipResource& a_sipResource) 
{ 
   a_sipResource.PrimEnableInboundCalls();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceUnblockedState::OnOffered(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an inbound call offered event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceUnblockedState::OnOffered( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   if ( a_sipResource.PrimOnOffered( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToOffered();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceActiveCallState::OnReqModifyCall(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a Request Modify Call
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceActiveCallState::OnReqModifyCall( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   a_sipResource.PrimOnReqModifyCall( a_metaEvent);
}


///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceActiveCallState::OnDisconnect(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a call disconnected event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceActiveCallState::OnDisconnect( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   a_sipResource.PrimOnDisconnect( a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceActiveCallState::Disconnect(ASipResource &a_sipResource)
//
// Description: Disconnect (drop and release) the call
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceActiveCallState::Disconnect( ASipResource& a_sipResource)
{ 
   a_sipResource.PrimDisconnect();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceActiveCallState::Close(ASipResource &a_sipResource)
//
// Description: Close the SIP Resource
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceActiveCallState::Close( ASipResource& a_sipResource) 
{ 
   if (a_sipResource.PrimDropCall() == 0) 
   {
      a_sipResource.SetStateToClosing();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceUnblockedState::MakeCall(ASipResource &a_sipResource, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Make an outbolund call
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceUnblockedState::MakeCall( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo) 
{ 
   if ( a_sipResource.PrimMakeCall( a_sipCallInfo) == 0) 
   {
      a_sipResource.SetStateToMakingCall();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceUnblockedState::OnBlocked(ASipResource &a_sipResource)
//
// Description: Handle a blocked event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceUnblockedState::OnBlocked( ASipResource& a_sipResource) 
{ 
   if ( a_sipResource.PrimOnBlocked() == 0) 
   {
      a_sipResource.SetStateToBlocked();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceUnblockedState::Close(ASipResource &a_sipResource)
//
// Description: Close the SIP Resource
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceUnblockedState::Close( ASipResource& a_sipResource) 
{ 
   if (a_sipResource.PrimClose() == 0) 
   {
      a_sipResource.SetStateToClosing();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceOfferedState::Reject(ASipResource &a_sipResource, const int a_code)
//
// Description: Reject an offered inbound call
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const int a_code
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceOfferedState::Reject( ASipResource& a_sipResource, const int a_code)
{ 
   if ( a_sipResource.PrimReject( a_code) == 0)
   {
      a_sipResource.SetStateToUnblocked();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceOfferedState::Accept(ASipResource &a_sipResource)
//
// Description: Accept an offered inbound call
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceOfferedState::Accept( ASipResource& a_sipResource)
{ 
   if ( a_sipResource.PrimAccept() == 0)
   {
      a_sipResource.SetStateToAccepting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceAcceptingState::OnAccepted(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle the inbound call accepted completion event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceAcceptingState::OnAccepted( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   if ( a_sipResource.PrimOnAccepted( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToAccepted();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceAcceptedState::Answer(ASipResource &a_sipResource, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Answer an inbound call
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceAcceptedState::Answer( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo)
{ 
   if ( a_sipResource.PrimAnswer( a_sipCallInfo) == 0)
   {
      a_sipResource.SetStateToAnswering();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceAnsweringState::OnAnswered(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an inbound call answered completion event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceAnsweringState::OnAnswered( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   a_sipResource.PrimOnAnswered( a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceAnsweringState::OnAck(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an ACK event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceAnsweringState::OnAck( ASipResource& a_sipResource,  const CMetaEventSptr& a_metaEvent)
{ 
   if ( a_sipResource.PrimOnAck( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToConnected();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceActiveCallState::DropCall(ASipResource &a_sipResource)
//
// Description: Drop the call
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceActiveCallState::DropCall( ASipResource& a_sipResource)
{ 
   if ( a_sipResource.PrimDropCall( ) == 0)
   {
      a_sipResource.SetStateToDropping();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceDroppingState::OnCallDropped(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a call dropped completione event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceDroppingState::OnCallDropped( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   if ( a_sipResource.PrimOnCallDropped( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToDropped();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceDroppedState::ReleaseCall(ASipResource &a_sipResource)
//
// Description: Release the call
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceDroppedState::ReleaseCall( ASipResource& a_sipResource)
{ 
   if ( a_sipResource.PrimReleaseCall( ) == 0)
   {
      a_sipResource.SetStateToReleasing();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceReleasingState::OnCallReleased(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a call released completione event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceReleasingState::OnCallReleased( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   if ( a_sipResource.PrimOnCallReleased( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToUnblocked();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceMakingCallState::OnDialing(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an outbound call  "Dialing" event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceMakingCallState::OnDialing( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   if ( a_sipResource.PrimOnDialing( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToDialing();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceDialingState::OnAlerting(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an outbound call alerting event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceDialingState::OnAlerting( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   if ( a_sipResource.PrimOnAlerting( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToAlerting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceAlertingState::OnConnected(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an outbound call connected event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceAlertingState::OnConnected( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   a_sipResource.PrimOnConnected( a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceAlertingState::On200Ok(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an outbound call 200 OK event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceAlertingState::On200Ok( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   if ( a_sipResource.PrimOn200Ok( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToAcking200Ok();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceAcking200OkState::OnAckOk(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an outbound call ACK OK event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceAcking200OkState::OnAckOk( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   if ( a_sipResource.PrimOnAckOk( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToConnected();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceConnectedState::OnInfoMessage(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a SIP INFO message
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceConnectedState::OnInfoMessage( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   if ( a_sipResource.PrimOnInfoMessage( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToInfoMessageReceived();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceConnectedState::SendInfoMessage(ASipResource &a_sipResource, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Send a SIP INFO message
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceConnectedState::SendInfoMessage( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_sipResource.PrimSendInfoMessage( a_sipCallInfo) == 0)
   {
      a_sipResource.SetStateToSendingInfoMessage();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceInfoMessageReceivedState::SendInfoMessageResponse(ASipResource &a_sipResource, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Send a SIP INFO MESSAGE response
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceInfoMessageReceivedState::SendInfoMessageResponse( ASipResource& a_sipResource, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_sipResource.PrimSendInfoMessageResponse( a_sipCallInfo) == 0)
   {
      a_sipResource.SetStateToSendingInfoMessageResponse();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceSendingInfoMessageResponseState::OnExtensionComplete(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an Extension complete event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceSendingInfoMessageResponseState::OnExtensionComplete( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   if ( a_sipResource.PrimOnSendInfoMessageResponse( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToConnected();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceSendingInfoMessageState::OnExtensionComplete(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an Extension complete event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceSendingInfoMessageState::OnExtensionComplete( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   if ( a_sipResource.PrimOnSendInfoMessage( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToPendingInfoMessageResponse();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourcePendingInfoMessageResponseState::OnExtension(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an extension event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourcePendingInfoMessageResponseState::OnExtension( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{
   if ( a_sipResource.PrimOnInfoMessageResponse( a_metaEvent) == 0)
   {
      a_sipResource.SetStateToConnected();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceClosingState::OnClosed(ASipResource &a_sipResource)
//
// Description: Handle the SIP Resource closed completion event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceClosingState::OnClosed( ASipResource& a_sipResource) 
{ 
   if ( a_sipResource.PrimOnClosed() == 0) 
   {
      a_sipResource.SetStateToClosed();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceClosingState::OnCallDropped(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a call dropped completion event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceClosingState::OnCallDropped( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   a_sipResource.PrimOnCallDropped( a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceClosingState::ReleaseCall(ASipResource &a_sipResource)
//
// Description: Release the call
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceClosingState::ReleaseCall( ASipResource& a_sipResource)
{ 
   a_sipResource.PrimReleaseCall( );
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResourceClosingState::OnCallReleased(ASipResource &a_sipResource, const CMetaEventSptr &a_metaEvent)
//
// Description: Handle the call released completion event
//
// Return: void
//
// Parameters: ASipResource &a_sipResource
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResourceClosingState::OnCallReleased( ASipResource& a_sipResource, const CMetaEventSptr& a_metaEvent)
{ 
   a_sipResource.PrimClose();
}

