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
// File Name: ResourceGroupStates.h
//
// Description: Resource Group state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ResourceGroupStates_h
#define ResourceGroupStates_h

#include "TypeDefs.h"

#include <string>

class AResourceGroup;

///////////////////////////////////////////////////////////////////////////////
// Class: ::AResourceGroupState
//
// Description: The abstract Resource Group State class and all concrete 
// subclasses comprise a State Pattern implementation of the Resource Group 
// state machine.  
//
// The abstract Resource Group state declares all functions supported by the 
// state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class AResourceGroupState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void RejectCall( AResourceGroup& a_resourceGroup, const int a_code);
   virtual void MakeAvailable( AResourceGroup& a_resourceGroup);
   virtual void OnCallAlerting( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void OnCallConnected( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void AcceptCall( AResourceGroup& a_resourceGroup);
   virtual void OnCallAccepted( AResourceGroup& a_resourceGroup);
   virtual void AnswerCall( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void OnCallAnswered( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void OnAvailable( AResourceGroup& a_resourceGroup);

   virtual void OnCallModify( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);

   virtual void OnInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   virtual void SendInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   virtual void OnInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   virtual void SendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   virtual void OnSendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);

   virtual void StartDialog( AResourceGroup& a_resourceGroup, const ADialogSptr& a_dialog);
   virtual void OnStartDialog( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void OnDialogResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void OnDialogEvent( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void SendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
   virtual void OnSendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);

   virtual void SendMediaCommand( AResourceGroup& a_resourceGroup, const ADialogSptr& a_mediaCommand);

   virtual void Reset( AResourceGroup& a_resourceGroup);
   virtual void OnInboundCallReleased( AResourceGroup& a_resourceGroup);
   virtual void OnOutboundCallReleased( AResourceGroup& a_resourceGroup);
   virtual void OnReset( AResourceGroup& a_resourceGroup);

   virtual void Disconnect( AResourceGroup& a_resourceGroup);

private:
   void LogInvalidStateForCommand( AResourceGroup& a_resourceGroup, const char* a_command);
   void LogInvalidStateForEvent( AResourceGroup& a_resourceGroup, const char* a_event);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::AResourceGroupInitializedState
//
// Description: Abstract Resource Group initialized state consists of 
// functionality common to all states where the Resource Group has been 
// initialized 
//
///////////////////////////////////////////////////////////////////////////////
class AResourceGroupInitializedState : public AResourceGroupState
{
   const char* StateDesc() = 0;
   void Reset( AResourceGroup& a_resourceGroup);
   void Disconnect( AResourceGroup& a_resourceGroup);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundOfferedOutboundNullState
//
// Description: Resource Group state where the inbound call has been offered 
// and the outbound call is in the null state.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundOfferedOutboundNullState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Offered-Null"; }
   void MakeAvailable( AResourceGroup& a_resourceGroup);
   void RejectCall( AResourceGroup& a_resourceGroup, const int a_code);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundOfferedOutboundMakeCallState
//
// Description: Resource Group state where the inbound call has been offered 
// and the outbound call is being attempted.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundOfferedOutboundMakeCallState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Offered-Dialing"; }
   void OnCallAlerting( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundOfferedOutboundAlertingState
//
// Description: Resource Group state where the inbound call has been offered 
// and the outbound call is in the alerting state.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundOfferedOutboundAlertingState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Offered-Alerting"; }
   void AcceptCall( AResourceGroup& a_resourceGroup);
   void OnCallConnected( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundAcceptingOutboundAlertingState
//
// Description: Resource Group state where the inbound call is being accepted 
// and the outbound call is in the alerting state.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundAcceptingOutboundAlertingState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Accepting-Alerting"; }
   void OnCallAccepted( AResourceGroup& a_resourceGroup);
   void OnCallConnected( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundAcceptedOutboundAlertingState
//
// Description: Resource Group state where the inbound call has been accepted 
// and the outbound call is in the alerting state.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundAcceptedOutboundAlertingState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Accepted-Alerting"; }
   void OnCallConnected( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundAcceptedOutboundConnectedState
//
// Description: Resource Group state where the inbound call has been accepted 
// and the outbound call is connected.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundAcceptedOutboundConnectedState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Accepted-Connected"; }
   void AnswerCall( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundAnsweringOutboundConnectedState
//
// Description: Resource Group state where the inbound call is being answered 
// and the outbound call is connected.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundAnsweringOutboundConnectedState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Answering-Connected"; }
   void OnCallAnswered( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundAnsweredOutboundConnectedState
//
// Description: Resource Group state where the inbound call has been answered 
// and the outbound call is connected.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundAnsweredOutboundConnectedState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Answering-Connected"; }
   void OnAvailable( AResourceGroup& a_resourceGroup);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundAcceptingOutboundConnectedState
//
// Description: Resource Group state where the inbound call is being accepted 
// and the outbound call is connected.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundAcceptingOutboundConnectedState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Accepting-Connected"; }
   void OnCallAccepted( AResourceGroup& a_resourceGroup);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundOfferedOutboundConnectedState
//
// Description: Resource Group state where the inbound call has been offered 
// and the outbound call is connected.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundOfferedOutboundConnectedState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Accepting-Connected"; }
   void AcceptCall( AResourceGroup& a_resourceGroup);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupAvailableState
//
// Description: Resource Group state where the inbound call has been answered, 
// the outbound call is connected, and the group is ready for dialog operations.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupAvailableState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Available"; }
   void OnInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   void StartDialog( AResourceGroup& a_resourceGroup, const ADialogSptr& a_dialog);
   void OnDialogEvent(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo);
   void SendMediaCommand( AResourceGroup& a_resourceGroup, const ADialogSptr& a_mediaCommand);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupPassThruInfoFromAvailableState
//
// Description: A non-dialog invloved SIP INFO meassage has been received while
// in the available state.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupPassThruInfoFromAvailableState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Processing INFO"; }
   void SendInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   void OnInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   void SendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   void OnSendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupDialogRequestedState
//
// Description: A dialog has been requested from the server
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupDialogRequestedState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "dialog requested"; }
   void OnStartDialog( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupDialogStartingState
//
// Description: Waiting for notification that the dialog was received
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupDialogStartingState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "dialog starting"; }
   void OnDialogResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupDialogRunningState
//
// Description: A dialog is executing on the server
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupDialogRunningState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "dialog running"; }
   void OnInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   void OnDialogEvent( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
   //JM: TODO create new state for active conf with dialog running?
    void SendMediaCommand( AResourceGroup& a_resourceGroup, const ADialogSptr& a_mediaCommand);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupPassThruInfoFromDialogRunningState
//
// Description: A non-dialog invloved SIP INFO meassage has been received while
// a dialog is executing.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupPassThruInfoFromDialogRunningState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Processing INFO"; }
   void SendInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   void OnInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   void SendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
   void OnSendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupDialogEventPendingState
//
// Description: A dialog event has been received
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupDialogEventPendingState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "dialog event pending"; }
   void SendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupDialogEventRespondingState
//
// Description: Sending the response to a dialog evnet
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupDialogEventRespondingState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "responding dialog event"; }
   void OnSendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupDialogEndedState
//
// Description: Received notification that the dialog has ended
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupDialogEndedState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "dialog ended"; }
   void SendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupDialogCompletingState
//
// Description: Waiting for the dialog to complete
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupDialogCompletingState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "dialog completing"; }
   void OnSendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupMediaCommandRequestedState
//
// Description: A media command has been requested
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupMediaCommandRequestedState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Media Cmd Req"; }
   void OnStartDialog( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupMediaCommandPendingState
//
// Description: A media command is pending completion
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupMediaCommandPendingState : public AResourceGroupInitializedState
{
public:
   const char* StateDesc() { return "Media Cmd Pending"; }
   void OnDialogResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupResettingState
//
// Description: Resetting resources used by the Resource Group
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupResettingState : public AResourceGroupState
{
public:
   const char* StateDesc() { return "Resetting"; }
   void OnInboundCallReleased( AResourceGroup& a_resourceGroup);
   void OnOutboundCallReleased( AResourceGroup& a_resourceGroup);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupInboundCallReleasedState
//
// Description: Received notification that the inbound call has been dropped 
// and released.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupInboundCallReleasedState : public AResourceGroupState
{
public:
   const char* StateDesc() { return "Resetting-outbound"; }
   void OnOutboundCallReleased( AResourceGroup& a_resourceGroup);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupOutboundCallReleasedState
//
// Description: Received notification that the outbound call has been dropped 
// and released.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupOutboundCallReleasedState : public AResourceGroupState
{
public:
   const char* StateDesc() { return "Resetting-inbound"; }
   void OnInboundCallReleased( AResourceGroup& a_resourceGroup);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupUninitializedState
//
// Description: The Resource Group is uninitialized
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupUninitializedState : public AResourceGroupState
{
public:
   const char* StateDesc() { return "Uninitialized"; }
   void OnReset( AResourceGroup& a_resourceGroup);
};

#endif
