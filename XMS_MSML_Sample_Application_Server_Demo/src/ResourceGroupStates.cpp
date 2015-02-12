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
// File Name: ResourceGroupStates.cpp
//
// Description: Implementation of the ResourceGroup state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "ResourceGroupStates.h"
#include "AResourceGroup.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::RejectCall(AResourceGroup &a_resourceGroup, const int a_code)
//
// Description: Reject Call command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const int a_code
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::RejectCall( AResourceGroup& a_resourceGroup, const int a_code)
{
   LogInvalidStateForCommand( a_resourceGroup, "RejectCall");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::MakeAvailable(AResourceGroup &a_resourceGroup)
//
// Description: MakeAvailable command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::MakeAvailable( AResourceGroup& a_resourceGroup)
{
   LogInvalidStateForCommand( a_resourceGroup, "MakeAvailable");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnCallAlerting(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: OnCallAlerting event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnCallAlerting( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnCallAlerting");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnCallConnected(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: OnCallConnected event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnCallConnected( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnCallConnected");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::AcceptCall(AResourceGroup &a_resourceGroup)
//
// Description: AcceptCall command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::AcceptCall( AResourceGroup& a_resourceGroup)
{
   LogInvalidStateForCommand( a_resourceGroup, "AcceptCall");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnCallAccepted(AResourceGroup &a_resourceGroup)
//
// Description: OnCallAccepted event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnCallAccepted( AResourceGroup& a_resourceGroup)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnCallAccepted");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnCallModify(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: OnCallModify event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnCallModify( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnCallModify");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::AnswerCall(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: AnswerCall command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::AnswerCall( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   LogInvalidStateForCommand( a_resourceGroup, "AnswerCall");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnCallAnswered(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: OnCallAnswered event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnCallAnswered( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnCallAnswered");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnAvailable(AResourceGroup &a_resourceGroup)
//
// Description: OnAvailable event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnAvailable( AResourceGroup& a_resourceGroup)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnResourceGroupAvailable");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnInfoMessage(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: OnInfoMessage event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnInfoMessage");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::SendInfoMessage(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: SendInfoMessage command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::SendInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   LogInvalidStateForCommand( a_resourceGroup, "SendInfoMessage");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnInfoMessageResponse(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: OnInfoMessageResponse event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnInfoMessageResponse");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::SendInfoMessageResponse(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: SendInfoMessageResponse command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::SendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   LogInvalidStateForCommand( a_resourceGroup, "SendInfoMessageResponse");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnSendInfoMessageResponse(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: OnSendInfoMessageResponse event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnSendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnSendInfoMessageResponse");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::StartDialog(AResourceGroup &a_resourceGroup, const ADialogSptr &a_dialog)
//
// Description: StartDialog command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ADialogSptr &a_dialog
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::StartDialog( AResourceGroup& a_resourceGroup, const ADialogSptr& a_dialog)
{
   LogInvalidStateForCommand( a_resourceGroup, "StartDialog");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnStartDialog(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: OnStartDialog event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnStartDialog( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnStartDialog");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnDialogResponse(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: OnDialogResponse event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnDialogResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnDialogResponse");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::SendMediaCommand(AResourceGroup &a_resourceGroup, const ADialogSptr &a_mediaCommand)
//
// Description: SendMediaCommand command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ADialogSptr &a_mediaCommand
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::SendMediaCommand( AResourceGroup& a_resourceGroup, const ADialogSptr& a_mediaCommand)
{
   LogInvalidStateForCommand( a_resourceGroup, "SendMediaCommand");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnDialogEvent(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: OnDialogEvent event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnDialogEvent( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnDialogEvent");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::SendDialogEventResponse(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: SendDialogEventResponse command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::SendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   LogInvalidStateForCommand( a_resourceGroup, "SendDialogEventResponse");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnSendDialogEventResponse(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: OnSendDialogEventResponse event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnSendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnSendDialogEventResponse");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::Reset(AResourceGroup &a_resourceGroup)
//
// Description: Reset command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::Reset( AResourceGroup& a_resourceGroup)
{
   LogInvalidStateForCommand( a_resourceGroup, "Reset");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnInboundCallReleased(AResourceGroup &a_resourceGroup)
//
// Description: OnInboundCallReleased event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnInboundCallReleased( AResourceGroup& a_resourceGroup)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnInboundCallReleased");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnOutboundCallReleased(AResourceGroup &a_resourceGroup)
//
// Description: OnOutboundCallReleased event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnOutboundCallReleased( AResourceGroup& a_resourceGroup)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnOutboundCallReleased");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::OnReset(AResourceGroup &a_resourceGroup)
//
// Description: OnReset event is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::OnReset( AResourceGroup& a_resourceGroup)
{
   LogInvalidStateForEvent( a_resourceGroup, "OnReset");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::Disconnect(AResourceGroup &a_resourceGroup)
//
// Description: Disconnect command is invalid in this state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::Disconnect( AResourceGroup& a_resourceGroup)
{
   LogInvalidStateForEvent( a_resourceGroup, "Disconnect");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::LogInvalidStateForCommand(AResourceGroup &a_resourceGroup, const char *a_command)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const char *a_command
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::LogInvalidStateForCommand( AResourceGroup& a_resourceGroup, const char* a_command)
{
   a_resourceGroup.LogError( a_command, "Invalid state for command");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupState::LogInvalidStateForEvent(AResourceGroup &a_resourceGroup, const char *a_event)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const char *a_event
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupState::LogInvalidStateForEvent( AResourceGroup& a_resourceGroup, const char* a_event)
{
   a_resourceGroup.LogError( a_event, "Invalid state for event");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundOfferedOutboundNullState::RejectCall(AResourceGroup &a_resourceGroup, const int a_code)
//
// Description: Reject the inbound call
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const int a_code
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundOfferedOutboundNullState::RejectCall( AResourceGroup& a_resourceGroup, const int a_code)
{
   a_resourceGroup.PrimRejectCall( a_code);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundOfferedOutboundNullState::MakeAvailable(AResourceGroup &a_resourceGroup)
//
// Description: Make the Resource Group available
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundOfferedOutboundNullState::MakeAvailable( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimMakeAvailable() == 0)
   {
      a_resourceGroup.SetStateToInboundOfferedOutboundMakeCall();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundOfferedOutboundMakeCallState::OnCallAlerting(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle SIP Resource call alerting event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundOfferedOutboundMakeCallState::OnCallAlerting( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnCallAlerting( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToInboundOfferedOutboundAlerting();
      a_resourceGroup.AcceptCall();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundOfferedOutboundAlertingState::AcceptCall(AResourceGroup &a_resourceGroup)
//
// Description: Accept the inbound call
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundOfferedOutboundAlertingState::AcceptCall( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimAcceptCall() == 0)
   {
      a_resourceGroup.SetStateToInboundAcceptingOutboundAlerting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundOfferedOutboundAlertingState::OnCallConnected(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle the outbound call connected event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundOfferedOutboundAlertingState::OnCallConnected( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnCallConnected( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToInboundOfferedOutboundConnected();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundAcceptingOutboundAlertingState::OnCallAccepted(AResourceGroup &a_resourceGroup)
//
// Description: Handle the inbound call accepted completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundAcceptingOutboundAlertingState::OnCallAccepted( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimOnCallAccepted() == 0)
   {
      a_resourceGroup.SetStateToInboundAcceptedOutboundAlerting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundAcceptingOutboundAlertingState::OnCallConnected(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle the outbound call connected event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundAcceptingOutboundAlertingState::OnCallConnected( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnCallConnected( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToInboundAcceptingOutboundConnected();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundAcceptedOutboundAlertingState::OnCallConnected(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle the outbound call accepted completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundAcceptedOutboundAlertingState::OnCallConnected( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnCallConnected( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToInboundAcceptedOutboundConnected();
      a_resourceGroup.AnswerCall( a_resourceGroup.InboundSipCallInfo());
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundAcceptedOutboundConnectedState::AnswerCall(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Answer the inbound call
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundAcceptedOutboundConnectedState::AnswerCall( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimAnswerCall( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToInboundAnsweringOutboundConnected();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundAnsweringOutboundConnectedState::OnCallAnswered(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle the inbound call answered completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundAnsweringOutboundConnectedState::OnCallAnswered( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnCallAnswered( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToInboundAnsweredOutboundConnected();
      a_resourceGroup.OnAvailable();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundAnsweredOutboundConnectedState::OnAvailable(AResourceGroup &a_resourceGroup)
//
// Description: Handle the Resource Group available completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundAnsweredOutboundConnectedState::OnAvailable( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimOnAvailable() == 0)
   {
      a_resourceGroup.SetStateToAvailable();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundOfferedOutboundConnectedState::AcceptCall(AResourceGroup &a_resourceGroup)
//
// Description: Accept the inbound call
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundOfferedOutboundConnectedState::AcceptCall( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimAcceptCall() == 0)
   {
      a_resourceGroup.SetStateToInboundAcceptingOutboundConnected();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundAcceptingOutboundConnectedState::OnCallAccepted(AResourceGroup &a_resourceGroup)
//
// Description: Hnadle the inbound call accepted completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundAcceptingOutboundConnectedState::OnCallAccepted( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimOnCallAccepted() == 0)
   {
      a_resourceGroup.SetStateToInboundAcceptedOutboundConnected();
      a_resourceGroup.AnswerCall( a_resourceGroup.InboundSipCallInfo());
   }
}
///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupAvailableState::OnInfoMessage(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a SIP INFO message
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupAvailableState::OnInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   if ( a_resourceGroup.PrimOnInfoMessagePassThru( a_sipResource) == 0)
   {
      a_resourceGroup.SetStateToPassThruInfoFromAvailable();
      a_resourceGroup.SendInfoMessage( a_sipResource);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupPassThruInfoFromAvailableState::SendInfoMessage(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Send a SIP INFO message
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupPassThruInfoFromAvailableState::SendInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   a_resourceGroup.PrimSendInfoMessagePassThru( a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupPassThruInfoFromAvailableState::OnInfoMessageResponse(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a SIP INFO message response
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupPassThruInfoFromAvailableState::OnInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   if ( a_resourceGroup.PrimOnInfoMessageResponsePassThru( a_sipResource) == 0)
   {
      a_resourceGroup.SendInfoMessageResponse( a_sipResource);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupPassThruInfoFromAvailableState::SendInfoMessageResponse(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Send a SIP INFO message response
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupPassThruInfoFromAvailableState::SendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   a_resourceGroup.PrimSendInfoMessageResponsePassThru( a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupPassThruInfoFromAvailableState::OnSendInfoMessageResponse(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a send SIP INFO message response completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupPassThruInfoFromAvailableState::OnSendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   if ( a_resourceGroup.PrimOnSendInfoMessageResponsePassThru( a_sipResource) == 0)
   {
      a_resourceGroup.SetStateToAvailable();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupAvailableState::StartDialog(AResourceGroup &a_resourceGroup, const ADialogSptr &a_dialog)
//
// Description: Start a dialog
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ADialogSptr &a_dialog
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupAvailableState::StartDialog( AResourceGroup& a_resourceGroup, const ADialogSptr& a_dialog)
{
   if ( a_resourceGroup.PrimStartDialog( a_dialog) == 0)
   {
      a_resourceGroup.SetStateToDialogRequested();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupDialogRequestedState::OnStartDialog(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a start dialog completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupDialogRequestedState::OnStartDialog( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnStartDialog( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToDialogStarting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupDialogStartingState::OnDialogResponse(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a dialog response
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupDialogStartingState::OnDialogResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnDialogResponse( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToDialogRunning();
   }
   else
   {
      a_resourceGroup.SetStateToAvailable();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupDialogRunningState::OnDialogEvent(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a Dialog event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupDialogRunningState::OnDialogEvent( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   int l_response = a_resourceGroup.PrimOnDialogEvent( a_sipCallInfo);
   if ( l_response == 0)
   {
      a_resourceGroup.SetStateToDialogEnded();
      a_resourceGroup.SendDialogEventResponse( a_sipCallInfo);
   }
   else if ( l_response > 0)
   {
      a_resourceGroup.SetStateToDialogEventPending();
      a_resourceGroup.SendDialogEventResponse( a_sipCallInfo);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupDialogRunningState::OnInfoMessage(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a SIP INFO message
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupDialogRunningState::OnInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   if ( a_resourceGroup.PrimOnInfoMessagePassThru( a_sipResource) == 0)
   {
      a_resourceGroup.SetStateToPassThruInfoFromDialogRunning();
      a_resourceGroup.SendInfoMessage( a_sipResource);
   }
}
//JM: May need to movce to own state.
///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupDialogRunningState::SendMediaCommand(AResourceGroup &a_resourceGroup, const ADialogSptr &a_mediaCommand)
//
// Description: Send a command ti the Mesia Server
//
// Return: void 
//
// Parameters: AResourceGroup &a_resourceGroup 
//             const ADialogSptr &a_mediaCommand 
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupDialogRunningState::SendMediaCommand( AResourceGroup& a_resourceGroup, const ADialogSptr& a_mediaCommand)
{
   if ( a_resourceGroup.PrimSendMediaCommand( a_mediaCommand) == 0)
   {
      a_resourceGroup.SetStateToMediaCommandRequestedState();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupPassThruInfoFromDialogRunningState::SendInfoMessage(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Send a SIP INFO message
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupPassThruInfoFromDialogRunningState::SendInfoMessage( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   a_resourceGroup.PrimSendInfoMessagePassThru( a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupPassThruInfoFromDialogRunningState::OnInfoMessageResponse(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a SIP INFO message response
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupPassThruInfoFromDialogRunningState::OnInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   if ( a_resourceGroup.PrimOnInfoMessageResponsePassThru( a_sipResource) == 0)
   {
      a_resourceGroup.SendInfoMessageResponse( a_sipResource);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupPassThruInfoFromDialogRunningState::SendInfoMessageResponse(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Send a SIP INFO message response
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupPassThruInfoFromDialogRunningState::SendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   a_resourceGroup.PrimSendInfoMessageResponsePassThru( a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupPassThruInfoFromDialogRunningState::OnSendInfoMessageResponse(AResourceGroup &a_resourceGroup, const ASipResourceSptr &a_sipResource)
//
// Description: Handle a send SIP INFO message response completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupPassThruInfoFromDialogRunningState::OnSendInfoMessageResponse( AResourceGroup& a_resourceGroup, const ASipResourceSptr& a_sipResource)
{
   if ( a_resourceGroup.PrimOnSendInfoMessageResponsePassThru( a_sipResource) == 0)
   {
      a_resourceGroup.SetStateToDialogRunning();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupDialogEventPendingState::SendDialogEventResponse(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Send a dialog event response 
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupDialogEventPendingState::SendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimSendDialogEventResponse( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToDialogEventResponding();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupDialogEventRespondingState::OnSendDialogEventResponse(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handl;e a send dialog event response completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupDialogEventRespondingState::OnSendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnSendDialogEventResponse( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToDialogRunning();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupDialogEndedState::SendDialogEventResponse(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Send a dialog event response
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupDialogEndedState::SendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimSendDialogEventResponse( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToDialogCompleting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupDialogCompletingState::OnSendDialogEventResponse(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a send dialog event response completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupDialogCompletingState::OnSendDialogEventResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnSendDialogEventResponse( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToAvailable();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupAvailableState::OnDialogEvent(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a Dialog event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//             const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupAvailableState::OnDialogEvent( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   int l_response = a_resourceGroup.PrimOnDialogEvent( a_sipCallInfo);
   if ( l_response == 0)
   {
      a_resourceGroup.SetStateToDialogEnded();
      a_resourceGroup.SendDialogEventResponse( a_sipCallInfo);
   }
   else if ( l_response > 0)
   {
      a_resourceGroup.SetStateToDialogEventPending();
      a_resourceGroup.SendDialogEventResponse( a_sipCallInfo);
   }
}
///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupAvailableState::SendMediaCommand(AResourceGroup &a_resourceGroup, const ADialogSptr &a_mediaCommand)
//
// Description: Send a command ti the Mesia Server
//
// Return: void 
//
// Parameters: AResourceGroup &a_resourceGroup 
//             const ADialogSptr &a_mediaCommand 
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupAvailableState::SendMediaCommand( AResourceGroup& a_resourceGroup, const ADialogSptr& a_mediaCommand)
{
   if ( a_resourceGroup.PrimSendMediaCommand( a_mediaCommand) == 0)
   {
      a_resourceGroup.SetStateToMediaCommandRequestedState();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupMediaCommandRequestedState::OnStartDialog(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a Send command started event
//
// Return: void 
//
// Parameters: AResourceGroup &a_resourceGroup 
//             const CSipCallInfoSptr &a_sipCallInfo 
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupMediaCommandRequestedState::OnStartDialog( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   if ( a_resourceGroup.PrimOnMediaCommandSent( a_sipCallInfo) == 0)
   {
      a_resourceGroup.SetStateToMediaCommandPendingState();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupMediaCommandPendingState::OnDialogResponse(AResourceGroup &a_resourceGroup, const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a command response
//
// Return: void 
//
// Parameters: AResourceGroup &a_resourceGroup 
//             const CSipCallInfoSptr &a_sipCallInfo 
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupMediaCommandPendingState::OnDialogResponse( AResourceGroup& a_resourceGroup, const CSipCallInfoSptr& a_sipCallInfo)
{
   a_resourceGroup.PrimOnMediaCommandResponse( a_sipCallInfo);
   a_resourceGroup.SetStateToAvailable();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupInitializedState::Reset(AResourceGroup &a_resourceGroup)
//
// Description: Reset the Resource Group
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupInitializedState::Reset( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimReset() == 0)
   {
      a_resourceGroup.SetStateToResetting();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroupInitializedState::Disconnect(AResourceGroup &a_resourceGroup)
//
// Description: Disconnect the calls in the Resource Group
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroupInitializedState::Disconnect( AResourceGroup& a_resourceGroup)
{
   a_resourceGroup.PrimDisconnect();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupResettingState::OnInboundCallReleased(AResourceGroup &a_resourceGroup)
//
// Description: Handle a call released event from the inbound call
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupResettingState::OnInboundCallReleased( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimOnInboundCallReleased() == 0)
   {
      a_resourceGroup.SetStateToInboundCallReleased();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupResettingState::OnOutboundCallReleased(AResourceGroup &a_resourceGroup)
//
// Description: Handle the call released event from the outbound call
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupResettingState::OnOutboundCallReleased( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimOnOutboundCallReleased() == 0)
   {
      a_resourceGroup.SetStateToOutboundCallReleased();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupInboundCallReleasedState::OnOutboundCallReleased(AResourceGroup &a_resourceGroup)
//
// Description: Handle the call released event from the outbound call
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupInboundCallReleasedState::OnOutboundCallReleased( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimOnOutboundCallReleased() == 0)
   {
      a_resourceGroup.SetStateToUninitialized();
      a_resourceGroup.OnReset();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupOutboundCallReleasedState::OnInboundCallReleased(AResourceGroup &a_resourceGroup)
//
// Description: Handle the call released event from the inbound call
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupOutboundCallReleasedState::OnInboundCallReleased( AResourceGroup& a_resourceGroup)
{
   if ( a_resourceGroup.PrimOnInboundCallReleased() == 0)
   {
      a_resourceGroup.SetStateToUninitialized();
      a_resourceGroup.OnReset();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroupUninitializedState::OnReset(AResourceGroup &a_resourceGroup)
//
// Description: Handle the Resource Group reset completion event
//
// Return: void
//
// Parameters: AResourceGroup &a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroupUninitializedState::OnReset( AResourceGroup& a_resourceGroup)
{
   a_resourceGroup.PrimOnReset();
}

