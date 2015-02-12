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
// File Name: AResourceGroup.h
//
// Description: AResourceGroup class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef AResourceGroup_h
#define AResourceGroup_h

#include "TypeDefs.h"
#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "ResourceGroupStates.h"

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::EnumResourceGroupNotifications
//
// Description: Observer notifications supported by Resource Group objects
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   RESOURCEGROUP_GROUP_AVAILABLE,
   RESOURCEGROUP_GROUP_RESET,
   RESOURCEGROUP_DIALOG_STARTED,
   RESOURCEGROUP_DIALOG_FAILED,
   RESOURCEGROUP_DIALOG_EVENT,
   RESOURCEGROUP_DIALOG_COMPLETE,
   RESOURCEGROUP_MEDIA_COMMAND_COMPLETE,
   RESOURCEGROUP_MEDIA_COMMAND_FAILED
} EnumResourceGroupNotifications;

///////////////////////////////////////////////////////////////////////////////
// Class: ::AResourceGroup
//
// Description: The abstact Resource Groupm class implements the public 
// interface and state machine for concrete Resource Groupm Classes.  Resource 
// Groups are responsible for controling and coordinating two SIP resources.
//
///////////////////////////////////////////////////////////////////////////////
class AResourceGroup : public ATaskHandler, public AObserverSubject
{
   friend class AResouceGroupState;
   friend class AResourceGroupInitializedState;
   friend class CResourceGroupInboundOfferedOutboundNullState;
   friend class CResourceGroupInboundOfferedOutboundMakeCallState;
   friend class CResourceGroupInboundOfferedOutboundAlertingState;
   friend class CResourceGroupInboundOfferedOutboundConnectedState;
   friend class CResourceGroupInboundAcceptingOutboundAlertingState;
   friend class CResourceGroupInboundAcceptingOutboundConnectedState;
   friend class CResourceGroupInboundAcceptedOutboundAlertingState;
   friend class CResourceGroupInboundAcceptedOutboundConnectedState;
   friend class CResourceGroupInboundAnsweringOutboundConnectedState;
   friend class CResourceGroupInboundAnsweredOutboundConnectedState;
   friend class CResourceGroupAvailableState;
   friend class CResourceGroupPassThruInfoFromAvailableState;
   friend class CResourceGroupDialogRequestedState;
   friend class CResourceGroupDialogStartingState;
   friend class CResourceGroupDialogRunningState;
   friend class CResourceGroupPassThruInfoFromDialogRunningState;
   friend class CResourceGroupDialogEventPendingState;
   friend class CResourceGroupDialogEventRespondingState;
   friend class CResourceGroupDialogEndedState;
   friend class CResourceGroupDialogCompletingState;
   friend class CResourceGroupMediaCommandRequestedState;
   friend class CResourceGroupMediaCommandPendingState;
   friend class CResourceGroupResettingState;
   friend class CResourceGroupInboundCallReleasedState;
   friend class CResourceGroupOutboundCallReleasedState;
   friend class CResourceGroupUninitializedState;

public:
   AResourceGroup( CTaskProcessorSptr a_taskProcessor);
   virtual ~AResourceGroup();

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

   virtual bool HasSipResource( ASipResourceSptr a_sipResource);
   virtual ASipResourceSptr& InboundSipResource() = 0;
   virtual ASipResourceSptr& OutboundSipResource() = 0;

   virtual CSipCallInfoSptr& InboundSipCallInfo() = 0;
   virtual CSipCallInfoSptr& OutboundSipCallInfo() = 0;

   virtual const std::string MsmlConnectionTag() = 0;

   void RejectCall( const int a_code);
   void MakeAvailable();
   void AcceptCall();
   void OnCallAccepted();
   void AnswerCall( const CSipCallInfoSptr& a_sipCallInfo);
   void OnCallAnswered( const CSipCallInfoSptr& a_sipCallInfo);
   void OnCallModify( const ASipResourceSptr& a_sipResource);
   void OnCallAlerting( const CSipCallInfoSptr& a_sipCallInfo);
   void OnCallConnected( const CSipCallInfoSptr& a_sipCallInfo);
   void OnAvailable();

   void SendInfoMessage( const ASipResourceSptr& a_sipResource);
   void OnInfoMessage( const ASipResourceSptr& a_sipResource);
   void OnInfoMessageResponse( const ASipResourceSptr& a_sipResource);
   void SendInfoMessageResponse( const ASipResourceSptr& a_sipResource);
   void OnSendInfoMessageResponse( const ASipResourceSptr& a_sipResource);

   void StartDialog( const ADialogSptr& a_dialog);
   void OnStartDialog( const CSipCallInfoSptr& a_sipCallInfo);
   void OnDialogResponse( const CSipCallInfoSptr& a_sipCallInfo);
   void OnDialogEvent( const CSipCallInfoSptr& a_sipCallInfo);
   void SendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo);
   void OnSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo);

   void SendMediaCommand( const ADialogSptr& a_mediaCommand);

   void Reset();
   void OnInboundCallReleased();
   void OnOutboundCallReleased();
   void OnReset();

   void Disconnect();

   bool VideoAvailable();

protected:
   virtual int PrimRejectCall( const int a_code) = 0;
   virtual int PrimMakeAvailable() = 0;
   virtual int PrimAcceptCall() = 0;
   virtual int PrimOnCallAccepted() = 0;
   virtual int PrimAnswerCall( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnCallAnswered( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnCallAlerting( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnCallConnected( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnAvailable() = 0;

   virtual int PrimOnInfoMessagePassThru( const ASipResourceSptr& a_sipResource) = 0;
   virtual int PrimSendInfoMessagePassThru( const ASipResourceSptr& a_sipResource) = 0;
   virtual int PrimOnInfoMessageResponsePassThru( const ASipResourceSptr& a_sipResource) = 0;
   virtual int PrimSendInfoMessageResponsePassThru( const ASipResourceSptr& a_sipResource) = 0;
   virtual int PrimOnSendInfoMessageResponsePassThru( const ASipResourceSptr& a_sipResource) = 0;

   virtual int PrimStartDialog( const ADialogSptr& a_dialog) = 0;
   virtual int PrimOnStartDialog( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnDialogResponse( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnDialogEvent( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo) = 0;

   virtual int PrimSendMediaCommand( const ADialogSptr& a_mediaCommand) = 0;
   virtual int PrimOnMediaCommandSent( const CSipCallInfoSptr& a_sipCallInfo) = 0;
   virtual int PrimOnMediaCommandResponse( const CSipCallInfoSptr& a_sipCallInfo) = 0;

   virtual int PrimReset() = 0;
   virtual int PrimOnInboundCallReleased() = 0;
   virtual int PrimOnOutboundCallReleased() = 0;
   virtual int PrimOnReset() = 0;

   virtual int PrimDisconnect() = 0;

   void VideoAvailable( bool videoAvailable);

private:
   void BasicRejectCall( const int a_code);
   void BasicMakeAvailable();
   void BasicAcceptCall();
   void BasicOnCallAccepted();
   void BasicAnswerCall( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnCallAnswered( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnCallAlerting( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnCallConnected( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnAvailable();

   void BasicOnCallModify( const ASipResourceSptr& a_sipResource);
   
   void BasicOnInfoMessage( const ASipResourceSptr& a_sipResource);
   void BasicSendInfoMessage( const ASipResourceSptr& a_sipResource);
   void BasicOnInfoMessageResponse( const ASipResourceSptr& a_sipResource);
   void BasicSendInfoMessageResponse( const ASipResourceSptr& a_sipResource);
   void BasicOnSendInfoMessageResponse( const ASipResourceSptr& a_sipResource);

   void BasicStartDialog( const ADialogSptr& a_dialog);
   void BasicOnStartDialog( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnDialogResponse( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnDialogEvent( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo);
   void BasicOnSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo);

   void BasicSendMediaCommand( const ADialogSptr& a_mediaCommand);

   void BasicReset();
   void BasicOnInboundCallReleased();
   void BasicOnOutboundCallReleased();
   void BasicOnReset();

   void BasicDisconnect();

   void SetStateToInboundOfferedOutboundNull();
   void SetStateToInboundOfferedOutboundMakeCall();
   void SetStateToInboundOfferedOutboundAlerting();
   void SetStateToInboundOfferedOutboundConnected();
   void SetStateToInboundAcceptingOutboundAlerting();
   void SetStateToInboundAcceptingOutboundConnected();
   void SetStateToInboundAcceptedOutboundAlerting();
   void SetStateToInboundAcceptedOutboundConnected();
   void SetStateToInboundAnsweringOutboundConnected();
   void SetStateToInboundAnsweredOutboundConnected();
   void SetStateToAvailable();
   void SetStateToPassThruInfoFromAvailable();
   void SetStateToDialogRequested();
   void SetStateToDialogStarting();
   void SetStateToDialogRunning();
   void SetStateToPassThruInfoFromDialogRunning();
   void SetStateToDialogEventPending();
   void SetStateToDialogEventResponding();
   void SetStateToDialogEnded();
   void SetStateToDialogCompleting();
   void SetStateToMediaCommandRequestedState();
   void SetStateToMediaCommandPendingState();
   void SetStateToResetting();
   void SetStateToInboundCallReleased();
   void SetStateToOutboundCallReleased();
   void SetStateToUninitialized();

   AResourceGroupState* m_state; 
   static CResourceGroupInboundOfferedOutboundNullState m_offeredNullState;
   static CResourceGroupInboundOfferedOutboundMakeCallState m_offeredMakeCall;
   static CResourceGroupInboundOfferedOutboundAlertingState m_offeredAlertingState;
   static CResourceGroupInboundOfferedOutboundConnectedState m_offeredConnectedState;
   static CResourceGroupInboundAcceptingOutboundAlertingState m_acceptingAlertingState;
   static CResourceGroupInboundAcceptingOutboundConnectedState m_acceptingConnectedState;
   static CResourceGroupInboundAcceptedOutboundAlertingState m_acceptedAlertingState;
   static CResourceGroupInboundAcceptedOutboundConnectedState m_acceptedConnectedState;
   static CResourceGroupInboundAnsweringOutboundConnectedState m_answeringConnectedState;
   static CResourceGroupInboundAnsweredOutboundConnectedState m_answeredConnectedState;
   static CResourceGroupAvailableState m_availableState;
   static CResourceGroupPassThruInfoFromAvailableState m_passThruInfoFromAvailableState;
   static CResourceGroupDialogRequestedState m_dialogRequestedState;
   static CResourceGroupDialogStartingState m_dialogStartingState;
   static CResourceGroupDialogRunningState m_dialogRunningState;
   static CResourceGroupPassThruInfoFromDialogRunningState m_passThruInfoFromDialogRunningState;
   static CResourceGroupDialogEventPendingState m_dialogEventPendingState;
   static CResourceGroupDialogEventRespondingState m_dialogEventRespondingState;
   static CResourceGroupDialogEndedState m_dialogEndedState;
   static CResourceGroupDialogCompletingState m_dialogCompletingState;
   static CResourceGroupMediaCommandRequestedState m_mediaCommandRequestedState;
   static CResourceGroupMediaCommandPendingState m_mediaCommandPendingState;
   static CResourceGroupResettingState m_resettingState;
   static CResourceGroupInboundCallReleasedState m_inboundCallReleasedState;
   static CResourceGroupOutboundCallReleasedState m_outboundCallReleasedState;
   static CResourceGroupUninitializedState m_uninitializedState;

   bool m_videoAvailable;
};

#endif
