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
// File Name: AResourceGroup.cpp
//
// Description: AResourceGroup class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "boost/bind.hpp"

#include "AResourceGroup.h"
#include "CTaskProcessor.h"

CResourceGroupInboundOfferedOutboundNullState AResourceGroup::m_offeredNullState;
CResourceGroupInboundOfferedOutboundMakeCallState AResourceGroup::m_offeredMakeCall;
CResourceGroupInboundOfferedOutboundAlertingState AResourceGroup::m_offeredAlertingState;
CResourceGroupInboundOfferedOutboundConnectedState AResourceGroup::m_offeredConnectedState;
CResourceGroupInboundAcceptingOutboundAlertingState AResourceGroup::m_acceptingAlertingState;
CResourceGroupInboundAcceptingOutboundConnectedState AResourceGroup::m_acceptingConnectedState;
CResourceGroupInboundAcceptedOutboundAlertingState AResourceGroup::m_acceptedAlertingState;
CResourceGroupInboundAcceptedOutboundConnectedState AResourceGroup::m_acceptedConnectedState;
CResourceGroupInboundAnsweringOutboundConnectedState AResourceGroup::m_answeringConnectedState;
CResourceGroupInboundAnsweredOutboundConnectedState AResourceGroup::m_answeredConnectedState;
CResourceGroupAvailableState AResourceGroup::m_availableState;
CResourceGroupPassThruInfoFromAvailableState AResourceGroup::m_passThruInfoFromAvailableState;
CResourceGroupDialogRequestedState AResourceGroup::m_dialogRequestedState;
CResourceGroupDialogStartingState AResourceGroup::m_dialogStartingState;
CResourceGroupDialogRunningState AResourceGroup::m_dialogRunningState;
CResourceGroupPassThruInfoFromDialogRunningState AResourceGroup::m_passThruInfoFromDialogRunningState;
CResourceGroupDialogEventPendingState AResourceGroup::m_dialogEventPendingState;
CResourceGroupDialogEventRespondingState AResourceGroup::m_dialogEventRespondingState;
CResourceGroupDialogEndedState AResourceGroup::m_dialogEndedState;
CResourceGroupDialogCompletingState AResourceGroup::m_dialogCompletingState;
CResourceGroupMediaCommandRequestedState AResourceGroup::m_mediaCommandRequestedState;
CResourceGroupMediaCommandPendingState AResourceGroup::m_mediaCommandPendingState;
CResourceGroupResettingState AResourceGroup::m_resettingState;
CResourceGroupInboundCallReleasedState AResourceGroup::m_inboundCallReleasedState;
CResourceGroupOutboundCallReleasedState AResourceGroup::m_outboundCallReleasedState;
CResourceGroupUninitializedState AResourceGroup::m_uninitializedState;

///////////////////////////////////////////////////////////////////////////////
// Function: AResourceGroup::AResourceGroup(CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
AResourceGroup::AResourceGroup( CTaskProcessorSptr a_taskProcessor)
   : ATaskHandler( a_taskProcessor)
   , m_state( &m_offeredNullState)
   , m_videoAvailable(false)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: AResourceGroup::~AResourceGroup()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
AResourceGroup::~AResourceGroup()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char * AResourceGroup::StateDesc()
//
// Description: Return a description of the current state
//
// Return: const char *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const char* AResourceGroup::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum AResourceGroup::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum AResourceGroup::LogObjectType()
{
   return LogObject_ResourceGroup;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool AResourceGroup::HasSipResource(ASipResourceSptr a_sipResource)
//
// Description: Test if the resource group has a SIP resource
//
// Return: bool
//
// Parameters: ASipResourceSptr a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
bool AResourceGroup::HasSipResource( ASipResourceSptr a_sipResource)
{
   return false;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool AResourceGroup::VideoAvailable()
//
// Description: Test if video is available
//
// Return: bool
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
bool AResourceGroup::VideoAvailable()
{
   return m_videoAvailable;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::VideoAvailable(bool a_videoAvailable)
//
// Description: Set if video is available
//
// Return: void
//
// Parameters: bool a_videoAvailable
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::VideoAvailable( bool a_videoAvailable)
{
   m_videoAvailable = a_videoAvailable;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::RejectCall(const int a_code)
//
// Description: Queue a task to reject an offered call the resource group
//
// Return: void
//
// Parameters: const int a_code
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::RejectCall( const int a_code)
{
   LogDebug( "RejectCall");
   ATaskSptr l_task( new CTask1<const int>( boost::bind( &AResourceGroup::BasicRejectCall, this, _1),
                                                         a_code,
                                                         "ASipResource::BasicRejectCall"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::MakeAvailable()
//
// Description: Queue a task to make the resource group available for 
// processing dialogs
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::MakeAvailable()
{
   LogDebug( "MakeAvailable");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroup::BasicMakeAvailable, this),
                                              "ASipResource::BasicRejectCall"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnCallConnected(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to handle a call connected event on an outbound call
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnCallConnected( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "OnCallConnected");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>(  boost::bind( &AResourceGroup::BasicOnCallConnected, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicOnCallConnected"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnCallAlerting(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to handle a call alerting event on an outbound call
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnCallAlerting( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "OnCallAlerting");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>(  boost::bind( &AResourceGroup::BasicOnCallAlerting, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicOnCallAlerting"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::AcceptCall()
//
// Description: Queue a task to accept an offered inbound call
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::AcceptCall()
{
   LogDebug( "AcceptCall");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroup::BasicAcceptCall, this), 
                                              "ASipResource::BasicAcceptCall"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnCallAccepted()
//
// Description: Queue a task to handle a call accepted event on an innbound call
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnCallAccepted()
{
   LogDebug( "OnCallAccepted");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroup::BasicOnCallAccepted, this), 
                                              "ASipResource::BasicOnCallAccepted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::AnswerCall(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to answer an inbound call
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::AnswerCall( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "AnswerCall");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>( boost::bind( &AResourceGroup::BasicAnswerCall, this, _1),
                                                                a_sipCallInfo,
                                                                "ASipResource::BasicAnswerCall"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnCallAnswered(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to handle a call answered event on an inbound call
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnCallAnswered( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "OnCallAnswered");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>(  boost::bind( &AResourceGroup::BasicOnCallAnswered, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicOnCallAnswered"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnAvailable()
//
// Description: Queue a task to handle the OnAvailable event which happens when
// the Resource Group is available to process dialogs.
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnAvailable()
{
   LogDebug( "OnAvailable");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroup::BasicOnAvailable, this),
                                              "ASipResource::BasicOnAvailable"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnCallModify(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle a call Modify mesasage
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnCallModify( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnCallModify");
   ATaskSptr l_task( new CTask1<ASipResourceSptr>(  boost::bind( &AResourceGroup::BasicOnCallModify, this, _1),
                                                                 a_sipResource,
                                                                 "ASipResource::BasicOnCallModify"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnInfoMessage(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle an INFO mesasage
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnInfoMessage( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnInfoMessage");
   ATaskSptr l_task( new CTask1<ASipResourceSptr>(  boost::bind( &AResourceGroup::BasicOnInfoMessage, this, _1),
                                                                 a_sipResource,
                                                                 "ASipResource::BasicOnInfoMessage"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::SendInfoMessage(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to send an INFO message
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::SendInfoMessage( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "SendInfoMessage");
   ATaskSptr l_task( new CTask1<ASipResourceSptr>(  boost::bind( &AResourceGroup::BasicSendInfoMessage, this, _1),
                                                                 a_sipResource,
                                                                 "ASipResource::BasicSendInfoMessage"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnInfoMessageResponse(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle an INFO message response
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnInfoMessageResponse( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnInfoMessageResponse");
   ATaskSptr l_task( new CTask1<ASipResourceSptr>(  boost::bind( &AResourceGroup::BasicOnInfoMessageResponse, this, _1),
                                                                 a_sipResource,
                                                                 "ASipResource::BasicOnInfoMessageResponse"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::SendInfoMessageResponse(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to send an INFO message response
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::SendInfoMessageResponse( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "SendInfoMessageResponse");
   ATaskSptr l_task( new CTask1<ASipResourceSptr>(  boost::bind( &AResourceGroup::BasicSendInfoMessageResponse, this, _1),
                                                                 a_sipResource,
                                                                 "ASipResource::BasicSendInfoMessageResponse"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnSendInfoMessageResponse(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle a call answered event on an inbound call
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnSendInfoMessageResponse( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnSendInfoMessageResponse");
   ATaskSptr l_task( new CTask1<ASipResourceSptr>(  boost::bind( &AResourceGroup::BasicOnSendInfoMessageResponse, this, _1),
                                                                 a_sipResource,
                                                                 "ASipResource::BasicOnSendInfoMessageResponse"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::StartDialog(const ADialogSptr &a_dialog)
//
// Description: Queue a task to start a dialog
//
// Return: void
//
// Parameters: const ADialogSptr &a_dialog
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::StartDialog( const ADialogSptr& a_dialog)
{
   LogDebug( "StartDialog");
   ATaskSptr l_task( new CTask1<ADialogSptr>(  boost::bind( &AResourceGroup::BasicStartDialog, this, _1),
                                                                 a_dialog,
                                                                 "ASipResource::BasicStartDialog"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnStartDialog(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to handle a StartDialog completion event
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnStartDialog( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "OnStartDialog");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>(  boost::bind( &AResourceGroup::BasicOnStartDialog, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicOnStartDialog"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnDialogResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to handle a dialog response event
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnDialogResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "OnDialogResponse");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>(  boost::bind( &AResourceGroup::BasicOnDialogResponse, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicOnDialogResponse"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnDialogEvent(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to handle a dialog event event
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnDialogEvent( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "OnDialogEvent");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>(  boost::bind( &AResourceGroup::BasicOnDialogEvent, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicOnDialogEvent"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::SendDialogEventResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to send a dialog event response
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::SendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "SendDialogEventResponse");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>(  boost::bind( &AResourceGroup::BasicSendDialogEventResponse, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicSendDialogEventResponse"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnSendDialogEventResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to handle a SendDialogEventResponse completion event
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "OnSendDialogEventResponse");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>(  boost::bind( &AResourceGroup::BasicOnSendDialogEventResponse, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicOnSendDialogEventResponse"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::SendMediaCommand(const ADialogSptr &a_dialog)
//
// Description: Queue a task to send a media server command dialog
//
// Return: void
//
// Parameters: const ADialogSptr &a_mediaCommand
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::SendMediaCommand( const ADialogSptr& a_mediaCommand)
{
   LogDebug( "SendMediaCommand");
   ATaskSptr l_task( new CTask1<ADialogSptr>(  boost::bind( &AResourceGroup::BasicSendMediaCommand, this, _1),
                                                                 a_mediaCommand,
                                                                 "ASipResource::BasicSendMediaCommand"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::Reset()
//
// Description: Queue a task to reset the resource group
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::Reset()
{
   LogDebug( "Reset");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroup::BasicReset, this),
                                              "ASipResource::BasicReset"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnInboundCallReleased()
//
// Description: Queue a task to handle a call released event on an inbound call
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnInboundCallReleased()
{
   LogDebug( "OnInboundCallReleased");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroup::BasicOnInboundCallReleased, this),
                                              "ASipResource::BasicOnInboundCallReleased"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnOutboundCallReleased()
//
// Description: Queue a task to handle a call released event on an outbound call
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnOutboundCallReleased()
{
   LogDebug( "OnOutboundCallReleased");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroup::BasicOnOutboundCallReleased, this),
                                              "ASipResource::BasicOnOutboundCallReleased"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::OnReset()
//
// Description: Queue a task to handle a reset completion event
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::OnReset()
{
   LogDebug( "OnReset");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroup::BasicOnReset, this),
                                              "ASipResource::BasicOnReset"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::Disconnect()
//
// Description: Queue a task to disconnect the calls in the resource group
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::Disconnect()
{
   LogDebug( "Disconnect");
   ATaskSptr l_task( new CTask0( boost::bind( &AResourceGroup::BasicDisconnect, this),
                                              "ASipResource::BasicDisconnect"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicRejectCall(const int a_code)
//
// Description: Delegate the RejectCall command to the state machine
//
// Return: void
//
// Parameters: const int a_code
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicRejectCall( const int a_code)
{
   m_state->RejectCall( *this, a_code);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicMakeAvailable()
//
// Description: Delegate the MakeAvailable command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicMakeAvailable()
{
   m_state->MakeAvailable( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnCallAlerting(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the OnCallAlerting event to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnCallAlerting( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->OnCallAlerting( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnCallConnected(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the OnCallConnected event to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnCallConnected( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->OnCallConnected( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicAcceptCall()
//
// Description: Delegate the AcceptCall command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicAcceptCall()
{
   m_state->AcceptCall( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnCallAccepted()
//
// Description: Delegate the OnCallAccepted event to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnCallAccepted()
{
   m_state->OnCallAccepted( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnCallModify(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnCallModify event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnCallModify( const ASipResourceSptr& a_sipResource)
{
   m_state->OnCallModify( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicAnswerCall(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the AnswerCall command to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicAnswerCall( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->AnswerCall( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnCallAnswered(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the OnCallAnswered event to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnCallAnswered( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->OnCallAnswered( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnAvailable()
//
// Description: Delegate the OnAvailable event to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnAvailable()
{
   m_state->OnAvailable( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnInfoMessage(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnInfoMessage event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnInfoMessage( const ASipResourceSptr& a_sipResource)
{
   m_state->OnInfoMessage( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicSendInfoMessage(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the SendInfoMessage command to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicSendInfoMessage( const ASipResourceSptr& a_sipResource)
{
   m_state->SendInfoMessage( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnInfoMessageResponse(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnInfoMessageResponse event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnInfoMessageResponse( const ASipResourceSptr& a_sipResource)
{
   m_state->OnInfoMessageResponse( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicSendInfoMessageResponse(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the SendInfoMessageResponse command to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicSendInfoMessageResponse( const ASipResourceSptr& a_sipResource)
{
   m_state->SendInfoMessageResponse( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnSendInfoMessageResponse(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnSendInfoMessageResponse event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnSendInfoMessageResponse( const ASipResourceSptr& a_sipResource)
{
   m_state->OnSendInfoMessageResponse( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicStartDialog(const ADialogSptr &a_dialog)
//
// Description: Delegate the StartDialog command to the state machine
//
// Return: void
//
// Parameters: const ADialogSptr &a_dialog
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicStartDialog( const ADialogSptr& a_dialog)
{
   m_state->StartDialog( *this, a_dialog);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnStartDialog(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the OnStartDialog event to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnStartDialog( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->OnStartDialog( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnDialogResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the OnDialogResponse event to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnDialogResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->OnDialogResponse( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnDialogEvent(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the OnDialogEvent event to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnDialogEvent( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->OnDialogEvent( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicSendDialogEventResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the SendDialogEventResponse command to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->SendDialogEventResponse( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnSendDialogEventResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the OnSendDialogEventResponse event to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->OnSendDialogEventResponse( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicSendMediaCommand(const ADialogSptr &a_mediaCommand)
//
// Description: Delegate the SendMediaCommand command to the state machine
//
// Return: void
//
// Parameters: const ADialogSptr &a_mediaCommand
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicSendMediaCommand( const ADialogSptr& a_mediaCommand)
{
   m_state->SendMediaCommand( *this, a_mediaCommand);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicReset()
//
// Description: Delegate the Reset command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicReset()
{
   m_state->Reset( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnInboundCallReleased()
//
// Description: Delegate the OnInboundCallReleased event to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnInboundCallReleased()
{
   m_state->OnInboundCallReleased( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnOutboundCallReleased()
//
// Description: Delegate the OnOutboundCallReleased event to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnOutboundCallReleased()
{
   m_state->OnOutboundCallReleased( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicOnReset()
//
// Description: Delegate the OnReset event to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicOnReset()
{
   m_state->OnReset( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AResourceGroup::BasicDisconnect()
//
// Description: Delegate the Disconnect command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::BasicDisconnect()
{
   m_state->Disconnect( *this);
}

///////////////////////////////////////////////////////////////////////////////
//	Function: State setting functions
//
//	Description: These functions set the current state
//
//	Return: void
//
//	Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void AResourceGroup::SetStateToInboundOfferedOutboundNull() { m_state = &m_offeredNullState;}
void AResourceGroup::SetStateToInboundOfferedOutboundMakeCall() { m_state = &m_offeredMakeCall;}
void AResourceGroup::SetStateToInboundOfferedOutboundAlerting() { m_state = &m_offeredAlertingState;}
void AResourceGroup::SetStateToInboundOfferedOutboundConnected() { m_state = &m_offeredConnectedState;}
void AResourceGroup::SetStateToInboundAcceptingOutboundAlerting() { m_state = &m_acceptingAlertingState;}
void AResourceGroup::SetStateToInboundAcceptingOutboundConnected() { m_state = &m_acceptingConnectedState;}
void AResourceGroup::SetStateToInboundAcceptedOutboundAlerting() { m_state = &m_acceptedAlertingState;}
void AResourceGroup::SetStateToInboundAcceptedOutboundConnected() { m_state = &m_acceptedConnectedState;}
void AResourceGroup::SetStateToInboundAnsweringOutboundConnected() { m_state = &m_answeringConnectedState;}
void AResourceGroup::SetStateToInboundAnsweredOutboundConnected() { m_state = &m_answeredConnectedState;}
void AResourceGroup::SetStateToAvailable() { m_state = &m_availableState;}
void AResourceGroup::SetStateToPassThruInfoFromAvailable() { m_state = &m_passThruInfoFromAvailableState;}
void AResourceGroup::SetStateToDialogRequested() { m_state = &m_dialogRequestedState;}
void AResourceGroup::SetStateToDialogStarting() { m_state = &m_dialogStartingState;}
void AResourceGroup::SetStateToDialogRunning() { m_state = &m_dialogRunningState;}
void AResourceGroup::SetStateToPassThruInfoFromDialogRunning() { m_state = &m_passThruInfoFromDialogRunningState;}
void AResourceGroup::SetStateToDialogEventPending() { m_state = &m_dialogEventPendingState;}
void AResourceGroup::SetStateToDialogEventResponding() { m_state = &m_dialogEventRespondingState;}
void AResourceGroup::SetStateToDialogEnded() { m_state = &m_dialogEndedState;}
void AResourceGroup::SetStateToDialogCompleting() { m_state = &m_dialogCompletingState;}
void AResourceGroup::SetStateToMediaCommandRequestedState() { m_state = &m_mediaCommandRequestedState;}
void AResourceGroup::SetStateToMediaCommandPendingState() { m_state = &m_mediaCommandPendingState;}
void AResourceGroup::SetStateToResetting() { m_state = &m_resettingState;}
void AResourceGroup::SetStateToInboundCallReleased() { m_state = &m_inboundCallReleasedState;}
void AResourceGroup::SetStateToOutboundCallReleased() { m_state = &m_outboundCallReleasedState;}
void AResourceGroup::SetStateToUninitialized() { m_state = &m_uninitializedState;}

