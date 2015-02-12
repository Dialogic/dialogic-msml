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
// File Name: ASipResource.h
//
// Description: ASipResource class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ASipResource_h
#define ASipResource_h

#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "SipResourceStates.h"

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::EnumSipResourceNotifications
//
// Description: Observer notifications supported by SIP Resource objects
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   SIP_RESOURCE_OPENED,
   SIP_RESOURCE_BLOCKED,
   SIP_RESOURCE_UNBLOCKED,
   SIP_RESOURCE_CLOSED,
   SIP_RESOURCE_OFFERED_RESOURCE,
   SIP_RESOURCE_OFFERED_MESSAGE,
   SIP_RESOURCE_ACCEPTED,
   SIP_RESOURCE_REQ_MODIFY_CALL,
   SIP_RESOURCE_ANSWERED_MESSAGE,
   SIP_RESOURCE_ACK,
   SIP_RESOURCE_DISCONNECTED_RESOURCE,
   SIP_RESOURCE_DISCONNECTED_MESSAGE,
   SIP_RESOURCE_CALL_DROPPED,
   SIP_RESOURCE_CALL_RELEASED,
   SIP_RESOURCE_MAKING_CALL,
   SIP_RESOURCE_DIALING,
   SIP_RESOURCE_ALERTING,
   SIP_RESOURCE_CONNECTED,
   SIP_RESOURCE_200OK,
   SIP_RESOURCE_INFO_SENT,
   SIP_RESOURCE_INFO_RECEIVED,
   SIP_RESOURCE_INFO_RESPONSE_SENT,
   SIP_RESOURCE_INFO_RESPONSE,
   SIP_RESOURCE_MSML_SENT,
   SIP_RESOURCE_MSML_RECEIVED,
   SIP_RESOURCE_MSML_RESPONSE_SENT,
   SIP_RESOURCE_MSML_RESPONSE,
   SIP_RESOURCE_TASKFAIL
} EnumSipResourceNotifications;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ASipResource
//
// Description: The abstract SIP Resource class implements the public interface
// and state machine for the concrete SIP Resource class.  The SIP Resource 
// class is responsible or opening/closing GC SIP devices, handling GC device 
// events and making all SIP device GC API calls.
//
///////////////////////////////////////////////////////////////////////////////
class ASipResource : public ATaskHandler, public AObserverSubject
{
   friend class ASipResourceState;
   friend class CSipResourceClosedState;
   friend class CSipResourceOpeningState;
   friend class CSipResourceBlockedState;
   friend class CSipResourceUnblockedState;
   friend class ASipResourceActiveCallState;
   friend class CSipResourceOfferedState;
   friend class CSipResourceAcceptingState;
   friend class CSipResourceAcceptedState;
   friend class CSipResourceAnsweringState;
   friend class CSipResourceAnsweredState;
   friend class CSipResourceDroppingState;
   friend class CSipResourceDroppedState;
   friend class CSipResourceMakingCallState;
   friend class CSipResourceReleasingState;
   friend class CSipResourceDialingState;
   friend class CSipResourceAlertingState;
   friend class CSipResourceConnectedState;
   friend class CSipResourceAcking200OkState;
   friend class CSipResourceInfoMessageReceivedState;
   friend class CSipResourceSendingInfoMessageResponseState;
   friend class CSipResourceSendingInfoMessageState;
   friend class CSipResourcePendingInfoMessageResponseState;
   friend class CSipResourceClosingState;

public:
   ASipResource( CTaskProcessorSptr a_taskProcessor);
   virtual ~ASipResource();

   void Open( CSrlEventManagerSptr a_srlEventManager);
   void OnOpened( const CMetaEventSptr& a_metaEvent);
   void OnSetConfigData( const CMetaEventSptr& a_metaEvent);
   void OnUnblocked( const CMetaEventSptr& a_metaEvent);
   void EnableInboundCalls();
   void OnBlocked();
   void Close();
   void OnClosed();

   void OnOffered( const CMetaEventSptr& a_metaEvent);
   void OnReqModifyCall( const CMetaEventSptr& a_metaEvent);
   void Reject( int a_code);
   void Accept();
   void OnAccepted( const CMetaEventSptr& a_metaEvent);
   void Answer( const CSipCallInfoSptr& a_sipCallInfo);
   void OnAnswered( const CMetaEventSptr& a_metaEvent);
   void OnAck( const CMetaEventSptr& a_metaEvent);
   void OnDisconnect( const CMetaEventSptr& a_metaEvent);
   void DropCall();
   void OnCallDropped( const CMetaEventSptr& a_metaEvent);
   void ReleaseCall();
   void OnCallReleased( const CMetaEventSptr& a_metaEvent);

   void MakeCall( const CSipCallInfoSptr& a_sipCallInfo);
   void OnDialing( const CMetaEventSptr& a_metaEvent);
   void OnAlerting( const CMetaEventSptr& a_metaEvent);
   void OnConnected( const CMetaEventSptr& a_metaEvent);
   void On200Ok( const CMetaEventSptr& a_metaEvent);
   void OnAckOk( const CMetaEventSptr& a_metaEvent);

   void OnInfoMessage( const CMetaEventSptr& a_metaEvent);
   void SendInfoMessageResponse( const CSipCallInfoSptr& a_sipCallInfo);
   void SendInfoMessage( const CSipCallInfoSptr& a_sipCallInfo);
   void OnExtension( const CMetaEventSptr& a_metaEvent);
   void OnExtensionComplete( const CMetaEventSptr& a_metaEvent);

   void OnTaskFail( const CMetaEventSptr& a_metaEvent);

   void Disconnect();

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

   virtual CSipCallInfoSptr& SipCallInfo() = 0;

   bool IsAnswered();
   bool IsConnected();

protected:
   virtual int PrimOpen( const CSrlEventManagerSptr& a_srlEventManager) = 0;
   virtual int PrimOnOpened( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOnSetConfigData( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOnUnblocked( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimEnableInboundCalls() = 0;
   virtual int PrimOnBlocked() = 0;
   virtual int PrimClose() = 0;
   virtual int PrimOnClosed() = 0;

   virtual int PrimOnOffered(  const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOnReqModifyCall(  const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimReject( int a_code) = 0;
   virtual int PrimAccept() = 0;
   virtual int PrimOnAccepted( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimAnswer( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnAck( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOnAnswered(  const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOnDisconnect(  const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimDropCall() = 0;
   virtual int PrimOnCallDropped( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimReleaseCall() = 0;
   virtual int PrimOnCallReleased( const CMetaEventSptr& a_metaEvent) = 0;

   virtual int PrimMakeCall( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnDialing( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOnAlerting( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOnConnected( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOn200Ok(  const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOnAckOk(  const CMetaEventSptr& a_metaEvent) = 0;

   virtual int PrimOnInfoMessage( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimSendInfoMessageResponse( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnSendInfoMessageResponse( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimSendInfoMessage( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnSendInfoMessage( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimOnInfoMessageResponse( const CMetaEventSptr& a_metaEvent) = 0;

   virtual int PrimOnTaskFail( const CMetaEventSptr& a_metaEvent) = 0;

   virtual int PrimDisconnect() = 0;
private:
   ASipResource();

   void BasicOpen( const CSrlEventManagerSptr& a_srlEventManager);
   void BasicOnOpened( const CMetaEventSptr& a_metaEvent);
   void BasicOnSetConfigData( const CMetaEventSptr& a_metaEvent);
   void BasicOnUnblocked( const CMetaEventSptr& a_metaEvent);
   void BasicEnableInboundCalls();
   void BasicOnBlocked();
   void BasicClose();
   void BasicOnClosed();

   void BasicOnOffered( const CMetaEventSptr& a_metaEvent);
   void BasicOnReqModifyCall( const CMetaEventSptr& a_metaEvent);
   void BasicReject( int a_code);
   void BasicAccept();
   void BasicOnAccepted( const CMetaEventSptr& a_metaEvent);
   void BasicAnswer( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnAnswered(  const CMetaEventSptr& a_metaEvent);
   void BasicOnAck( const CMetaEventSptr& a_metaEvent);
   void BasicOnDisconnect(  const CMetaEventSptr& a_metaEvent);
   void BasicDropCall();
   void BasicOnCallDropped( const CMetaEventSptr& a_metaEvent);
   void BasicReleaseCall();
   void BasicOnCallReleased( const CMetaEventSptr& a_metaEvent);

   void BasicMakeCall( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnDialing( const CMetaEventSptr& a_metaEvent);
   void BasicOnAlerting( const CMetaEventSptr& a_metaEvent);
   void BasicOnConnected( const CMetaEventSptr& a_metaEvent);
   void BasicOn200Ok(  const CMetaEventSptr& a_metaEvent);
   void BasicOnAckOk( const CMetaEventSptr& a_metaEvent);

   void BasicOnInfoMessage( const CMetaEventSptr& a_metaEvent);
   void BasicSendInfoMessageResponse( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicSendInfoMessage( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnExtension( const CMetaEventSptr& a_metaEvent);
   void BasicOnExtensionComplete( const CMetaEventSptr& a_metaEvent);

   void BasicOnTaskFail( const CMetaEventSptr& a_metaEvent);

   void BasicDisconnect();

   void SetStateToClosed();
   void SetStateToOpening();
   void SetStateToBlocked();
   void SetStateToUnblocked();
   void SetStateToOffered();
   void SetStateToAccepting();
   void SetStateToAccepted();
   void SetStateToAnswering();
   void SetStateToAnswered();
   void SetStateToDropping();
   void SetStateToDropped();
   void SetStateToReleasing();
   void SetStateToMakingCall();
   void SetStateToDialing();
   void SetStateToAlerting();
   void SetStateToAcking200Ok();
   void SetStateToConnected();
   void SetStateToInfoMessageReceived();
   void SetStateToSendingInfoMessageResponse();
   void SetStateToSendingInfoMessage();
   void SetStateToPendingInfoMessageResponse();
   void SetStateToClosing();

   ASipResourceState* m_state; 
   static CSipResourceClosedState m_closedState;
   static CSipResourceOpeningState m_openingState;
   static CSipResourceBlockedState m_blockedState;
   static CSipResourceUnblockedState m_unblockedState;
   static CSipResourceOfferedState m_offeredState;
   static CSipResourceAcceptingState m_acceptingState;
   static CSipResourceAcceptedState m_accepedState;
   static CSipResourceAnsweringState m_answeringState;
   static CSipResourceAnsweredState m_answeredState;
   static CSipResourceDroppingState m_droppingState;
   static CSipResourceDroppedState m_droppedState;
   static CSipResourceReleasingState m_releasingState;
   static CSipResourceMakingCallState m_makingCallState;
   static CSipResourceDialingState m_dialingState;
   static CSipResourceAlertingState m_alertingState;
   static CSipResourceAcking200OkState m_acking200OkState;
   static CSipResourceConnectedState m_connectedState;
   static CSipResourceInfoMessageReceivedState m_infoMessageReceivedState;
   static CSipResourceSendingInfoMessageResponseState m_sendingInfoMessageResponseState;
   static CSipResourceSendingInfoMessageState m_sendingInfoMessageState;
   static CSipResourcePendingInfoMessageResponseState m_pendingInfoMessageResponseState;
   static CSipResourceClosingState m_closingState; 
};

#endif
