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
// File Name: ASipResource.cpp
//
// Description: ASipResource class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "TypeDefs.h"
#include "ASipResource.h"
#include "CTask.h"
#include "CTaskProcessor.h"

CSipResourceClosedState ASipResource::m_closedState;;
CSipResourceOpeningState ASipResource::m_openingState;
CSipResourceBlockedState ASipResource::m_blockedState;
CSipResourceUnblockedState ASipResource::m_unblockedState;
CSipResourceOfferedState ASipResource::m_offeredState;
CSipResourceAcceptingState ASipResource::m_acceptingState;
CSipResourceAcceptedState ASipResource::m_accepedState;
CSipResourceAnsweringState ASipResource::m_answeringState;
CSipResourceAnsweredState ASipResource::m_answeredState;
CSipResourceDroppingState ASipResource::m_droppingState;
CSipResourceDroppedState ASipResource::m_droppedState;
CSipResourceReleasingState ASipResource::m_releasingState;
CSipResourceMakingCallState ASipResource::m_makingCallState;
CSipResourceDialingState ASipResource::m_dialingState;
CSipResourceAlertingState ASipResource::m_alertingState;
CSipResourceAcking200OkState ASipResource::m_acking200OkState;
CSipResourceConnectedState ASipResource::m_connectedState;
CSipResourceInfoMessageReceivedState ASipResource::m_infoMessageReceivedState;
CSipResourceSendingInfoMessageResponseState ASipResource::m_sendingInfoMessageResponseState;
CSipResourceSendingInfoMessageState ASipResource::m_sendingInfoMessageState;
CSipResourcePendingInfoMessageResponseState ASipResource::m_pendingInfoMessageResponseState;
CSipResourceClosingState ASipResource::m_closingState;

///////////////////////////////////////////////////////////////////////////////
// Function: ASipResource::ASipResource( CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
ASipResource::ASipResource( CTaskProcessorSptr a_taskProcessor)
   : ATaskHandler( a_taskProcessor)
   , m_state( &m_closedState)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ASipResource::~ASipResource()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ASipResource::~ASipResource()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* ASipResource::StateDesc()
//
// Description: Access a description of the current state
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* ASipResource::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum ASipResource::LogObjectType()
//
// Description: Access the LobObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum ASipResource::LogObjectType()
{
   return LogObject_Resource;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ASipResource::IsAnswered()
//
// Description: Test if the SIP Resource is an answered inbound call
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ASipResource::IsAnswered()
{
   return m_state == &m_answeredState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ASipResource::IsConnected()
//
// Description: Test if the SIP Resource is a connected outbound call
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ASipResource::IsConnected()
{
   return m_state == &m_connectedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::Open(const CSrlEventManagerSptr a_srlEventManager)
//
// Description: Queue a task to open the SIP Resource
//
// Return: void
//
// Parameters: const CSrlEventManagerSptr a_srlEventManager
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::Open( const CSrlEventManagerSptr a_srlEventManager)
{
   LogDebug( "Open");
   ATaskSptr l_task( new CTask1<CSrlEventManagerSptr>( 
                                    boost::bind( &ASipResource::BasicOpen, this, _1), 
                                                 a_srlEventManager,
                                                "ASipResource::BasicOpen"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnOpened(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource opened completion event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnOpened( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnOpened");
   ATaskSptr l_task( new CTask1<CMetaEventSptr>( 
                           boost::bind( &ASipResource::BasicOnOpened, this, _1),
                                        a_metaEvent,
                                        "ASipResource::BasicOnOpened"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnSetConfigData(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource set config data 
// completion event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnSetConfigData( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnSetConfigData");
   ATaskSptr l_task( new CTask1<CMetaEventSptr>( 
                           boost::bind( &ASipResource::BasicOnSetConfigData, this, _1),
                                        a_metaEvent,
                                        "ASipResource::BasicOnSetConfigData"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnUnblocked(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource unblocked event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnUnblocked( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnUnblocked");
   ATaskSptr l_task( new CTask1<CMetaEventSptr>( 
                           boost::bind( &ASipResource::BasicOnUnblocked, this, _1),
                                        a_metaEvent,
                                        "ASipResource::BasicOnUnblocked"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::EnableInboundCalls()
//
// Description: Queue a task to enable inbound calls on the SIP Resource
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::EnableInboundCalls()
{
   LogDebug( "EnableInboundCalls");
   ATaskSptr l_task( new CTask0( 
                           boost::bind( &ASipResource::BasicEnableInboundCalls, this),
                                        "ASipResource::BasicEnableInboundCalls"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnBlocked()
//
// Description: Queue a task to handle a SIP Resource blocked event
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnBlocked()
{
   LogDebug( "OnBlocked");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipResource::BasicOnBlocked, this),
                                              "ASipResource::BasicOnBlocked"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::Close()
//
// Description: Queue a task to close the SIP Resource
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::Close()
{
   LogDebug( "Close");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipResource::BasicClose, this),
                                              "ASipResource::BasicClose"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnClosed()
//
// Description: Queue a task to handle a SIP Resource closed completion event
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnClosed()
{
   LogDebug( "OnClosed");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipResource::BasicOnClosed, this),
                                 "ASipResource::BasicOnClosed"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnOffered(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource offered event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnOffered( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnOffered");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>(  boost::bind( &ASipResource::BasicOnOffered, this, _1),
                                                   a_metaEvent,
                                                   "ASipResource::BasicOnOffered"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnReqModifyCall(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource Req Modify Call
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnReqModifyCall( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnReqModifyCall");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>(  boost::bind( &ASipResource::BasicOnReqModifyCall, this, _1),
                                                   a_metaEvent,
                                                   "ASipResource::BasicOnReqModifyCall"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::Reject(const int a_code)
//
// Description: Queue a task to reject an offered call on the SIP Resource
//
// Return: void
//
// Parameters: const int a_code
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::Reject( const int a_code)
{
   LogDebug( "Reject");
   ATaskSptr l_task( new CTask1< int>( boost::bind( &ASipResource::BasicReject, this, _1),
                                       a_code,
                                       "ASipResource::BasicReject"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::Accept()
//
// Description: Queue a task to accept an offered call on the SIP Resource
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::Accept()
{
   LogDebug( "Accept");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipResource::BasicAccept, this),
                                              "ASipResource::BasicAccept"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnAccepted(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource call accepted event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnAccepted( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnAccepted");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnAccepted, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnAccepted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::Answer(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to answer an inbound call on the SIP Resource
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::Answer( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "Answer");
   ATaskSptr l_task( new CTask1<CSipCallInfoSptr>( boost::bind( &ASipResource::BasicAnswer, this, _1),
                                                                a_sipCallInfo,
                                                                "ASipResource::BasicAnswer"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnAnswered(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource call answered event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnAnswered(  const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnAnswered");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnAnswered, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnAnswered"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnAck(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource ACK event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnAck( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnAck");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnAck, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnAck"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnDisconnect(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource call disconnected event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnDisconnect(  const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnDisconnect");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnDisconnect, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnDisconnect"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::DropCall()
//
// Description: Queue a task to drop a call on the SIP Resource
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::DropCall()
{
   LogDebug( "DropCall");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipResource::BasicDropCall, this),
                                              "ASipResource::BasicDropCall"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnCallDropped(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource call dropped event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnCallDropped( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnCallDropped");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnCallDropped, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnCallDropped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::ReleaseCall()
//
// Description: Queue a task to release a call on the SIP Resource
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::ReleaseCall()
{
   LogDebug( "ReleaseCall");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipResource::BasicReleaseCall, this),
                                              "ASipResource::BasicReleaseCall"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnCallReleased(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource call released event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnCallReleased( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnCallReleased");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnCallReleased, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnCallReleased"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::MakeCall(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to make an outbound call on the SIP Resource
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::MakeCall( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "MakeCall");
   ATaskSptr l_task( new CTask1< CSipCallInfoSptr>( boost::bind( &ASipResource::BasicMakeCall, this, _1),
                                                               a_sipCallInfo,
                                                               "ASipResource::BasicMakeCall"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnDialing(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource call dialing event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnDialing( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnDialing");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnDialing, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnDialingd"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnAlerting(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource call alerting event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnAlerting( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnAlerting");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnAlerting, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnAlerting"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnConnected(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource call connected event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnConnected( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnConnected");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnConnected, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnConnected"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::On200Ok(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource 200 OK event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::On200Ok(  const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "On200Ok");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOn200Ok, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOn200Ok"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnAckOk(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource ACK OK event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnAckOk(  const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnAckOk");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnAckOk, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnAckOk"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnInfoMessage(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource INFO message received 
// event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnInfoMessage( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnInfoMessage");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnInfoMessage, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnInfoMessage"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::SendInfoMessageResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to send an INFO message response on the SIP Resource
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::SendInfoMessageResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "SendInfoMessageResponse");
   ATaskSptr l_task( new CTask1< CSipCallInfoSptr>( boost::bind( &ASipResource::BasicSendInfoMessageResponse, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicSendInfoMessageResponse"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::SendInfoMessage(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Queue a task to send an INFO message on the SIP Resource
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::SendInfoMessage( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug( "SendInfoMessage");
   ATaskSptr l_task( new CTask1< CSipCallInfoSptr>( boost::bind( &ASipResource::BasicSendInfoMessage, this, _1),
                                                                 a_sipCallInfo,
                                                                 "ASipResource::BasicSendInfoMessage"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnExtension(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource GC extension event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnExtension( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnExtension");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnExtension, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnExtension"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnExtensionComplete(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource GC Extension complete 
// event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnExtensionComplete( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnExtensionComplete");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnExtensionComplete, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnExtensionComplete"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::OnTaskFail(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle a SIP Resource GC task failed event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::OnTaskFail( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnTaskFail");
   ATaskSptr l_task( new CTask1< CMetaEventSptr>( boost::bind( &ASipResource::BasicOnTaskFail, this, _1),
                                                               a_metaEvent,
                                                               "ASipResource::BasicOnTaskFail"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::Disconnect()
//
// Description: Queue a task to disconnect ( drop and release) a call on the 
// SIP Resource
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::Disconnect()
{
   LogDebug( "Disconnect");
   ATaskSptr l_task( new CTask0( boost::bind(   &ASipResource::BasicDisconnect, this),
                                                "ASipResource::BasicDisconnect"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOpen(const CSrlEventManagerSptr &a_srlEventManager)
//
// Description: Delegate the Open command to the state machine
//
// Return: void
//
// Parameters: const CSrlEventManagerSptr &a_srlEventManager
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOpen( const CSrlEventManagerSptr& a_srlEventManager)
{
   m_state->Open( *this, a_srlEventManager);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnOpened(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnOpened event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnOpened( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnOpened( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnSetConfigData(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnSetConfigData event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnSetConfigData( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnSetConfigData( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnUnblocked(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnUnblocked event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnUnblocked( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnUnblocked( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicEnableInboundCalls()
//
// Description: Delegate the EnableInboundCalls command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicEnableInboundCalls()
{
   m_state->EnableInboundCalls( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnBlocked()
//
// Description: Delegate the OnBlocked event to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnBlocked()
{
   m_state->OnBlocked( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicClose()
//
// Description: Delegate the Close command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicClose()
{
   m_state->Close( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnClosed()
//
// Description: Delegate the OnClosed event to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnClosed()
{
   m_state->OnClosed( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnOffered(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnOffered event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnOffered( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnOffered( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnReqModifyCall(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnReqModifyCall event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnReqModifyCall( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnReqModifyCall( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicReject(int a_code)
//
// Description: Delegate the Reject command to the state machine
//
// Return: void
//
// Parameters: int a_code
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicReject( int a_code)
{
   m_state->Reject( *this, a_code);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicAccept()
//
// Description: Delegate the Accept command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicAccept()
{
   m_state->Accept( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnAccepted(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnAccepted event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnAccepted( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnAccepted( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicAnswer(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the Answer command to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicAnswer( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->Answer( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnAnswered(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnAnswered event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnAnswered(  const CMetaEventSptr& a_metaEvent)
{
   m_state->OnAnswered( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnAck(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnAck event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnAck( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnAck( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnDisconnect(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnDisconnect event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnDisconnect(  const CMetaEventSptr& a_metaEvent)
{
   m_state->OnDisconnect( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicDropCall()
//
// Description: Delegate the DropCall command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicDropCall()
{
   m_state->DropCall( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnCallDropped(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnCallDropped event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnCallDropped( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnCallDropped( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicReleaseCall()
//
// Description: Delegate the ReleaseCall command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicReleaseCall()
{
   m_state->ReleaseCall( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnCallReleased(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnCallReleased event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnCallReleased( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnCallReleased( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicMakeCall(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the MakeCall command to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicMakeCall( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->MakeCall( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnDialing(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnDialing event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnDialing( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnDialing( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnAlerting(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnAlerting event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnAlerting( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnAlerting( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnConnected(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnConnected event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnConnected( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnConnected( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOn200Ok(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the On200Ok event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOn200Ok(  const CMetaEventSptr& a_metaEvent)
{
   m_state->On200Ok( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnAckOk(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnAckOk event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnAckOk(  const CMetaEventSptr& a_metaEvent)
{
   m_state->OnAckOk( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnInfoMessage(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnInfoMessage event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnInfoMessage( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnInfoMessage( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicSendInfoMessageResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the SendInfoMessageResponse command to the state 
// machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicSendInfoMessageResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->SendInfoMessageResponse( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicSendInfoMessage(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Delegate the SendInfoMessage command to the state machine
//
// Return: void
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicSendInfoMessage( const CSipCallInfoSptr& a_sipCallInfo)
{
   m_state->SendInfoMessage( *this, a_sipCallInfo);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnExtension(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnExtension event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnExtension( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnExtension( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnExtensionComplete(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnExtensionComplete event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnExtensionComplete( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnExtensionComplete( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicOnTaskFail(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnTaskFail event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicOnTaskFail( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnTaskFail( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResource::BasicDisconnect()
//
// Description: Delegate the Disconnect command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResource::BasicDisconnect()
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
void ASipResource::SetStateToClosed() { m_state = &m_closedState;}
void ASipResource::SetStateToOpening() { m_state = &m_openingState;}
void ASipResource::SetStateToBlocked() { m_state = &m_blockedState;}
void ASipResource::SetStateToUnblocked() { m_state = &m_unblockedState;}
void ASipResource::SetStateToOffered() { m_state = &m_offeredState;}
void ASipResource::SetStateToAccepting() { m_state = &m_acceptingState;}
void ASipResource::SetStateToAccepted() { m_state = &m_accepedState;}
void ASipResource::SetStateToAnswering() { m_state = &m_answeringState;}
void ASipResource::SetStateToAnswered() { m_state = &m_answeredState;}
void ASipResource::SetStateToDropping() { m_state = &m_droppingState;}
void ASipResource::SetStateToDropped() { m_state = &m_droppedState;}
void ASipResource::SetStateToReleasing() { m_state = &m_releasingState;}
void ASipResource::SetStateToMakingCall() { m_state = &m_makingCallState;}
void ASipResource::SetStateToDialing() { m_state = &m_dialingState;}
void ASipResource::SetStateToAlerting() { m_state = &m_alertingState;}
void ASipResource::SetStateToAcking200Ok() { m_state = &m_acking200OkState;}
void ASipResource::SetStateToConnected() { m_state = &m_connectedState;}
void ASipResource::SetStateToInfoMessageReceived() { m_state = &m_infoMessageReceivedState;}
void ASipResource::SetStateToSendingInfoMessageResponse() { m_state = &m_sendingInfoMessageResponseState;}
void ASipResource::SetStateToSendingInfoMessage() { m_state = &m_sendingInfoMessageState;}
void ASipResource::SetStateToPendingInfoMessageResponse() { m_state = &m_pendingInfoMessageResponseState;}
void ASipResource::SetStateToClosing() { m_state = &m_closingState;}


