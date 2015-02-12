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
// File Name: CResourceGroup.cpp
//
// Description: CResourceGroup class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "boost/bind.hpp"

#include "TypeDefs.h"
#include "CResourceGroup.h"
#include "CSipResource.h"
#include "CSipCallInfo.h"
#include "CConfigOptions.h"
#include "CMsmlDialog.h"
#include "CMsmlResponse.h"
#include "CMsmlEvent.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CResourceGroup::CResourceGroup(CTaskProcessorSptr a_taskProcessor, ASipResourceSptr a_inboundSipResource, ASipResourceSptr a_outboundSipResource)
//
// Description: Initializing constructor - register for SIP resource events 
// from the inbounc and outbound calls
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//             ASipResourceSptr a_inboundSipResource
//             ASipResourceSptr a_outboundSipResource
//
///////////////////////////////////////////////////////////////////////////////
CResourceGroup::CResourceGroup( CTaskProcessorSptr a_taskProcessor, 
                                ASipResourceSptr a_inboundSipResource, 
                                ASipResourceSptr a_outboundSipResource) 
   : AResourceGroup( a_taskProcessor)
   , m_inboundSipCall( a_inboundSipResource)
   , m_outboundSipCall( a_outboundSipResource)
   , m_inboundSipCallInfo( CSipCallInfoSptr (new CSipCallInfo()))
   , m_outboundSipCallInfo( CSipCallInfoSptr (new CSipCallInfo()))
{
   Name( a_inboundSipResource->Name());

   ATaskSptr l_onInbouundReleasedTask( new CTask0( boost::bind( &CResourceGroup::OnInboundCallReleased, this),
                                                                "CResourceGroup::OnInboundCallReleased"));
   a_inboundSipResource->RegisterForNotification( this, l_onInbouundReleasedTask, SIP_RESOURCE_CALL_RELEASED);

   ATaskSptr l_onAcceptedTask( new CTask0(
                                    boost::bind( &CResourceGroup::OnCallAccepted, this),
                                                 "CResourceGroup::OnCallAccepted"));
   a_inboundSipResource->RegisterForNotification( this, l_onAcceptedTask, SIP_RESOURCE_ACCEPTED);

   ATaskSptr l_onAnsweredTask( new CTask1<CSipCallInfoSptr>(  
                                    boost::bind( &CResourceGroup::OnCallAnswered, this, _1),
                                                 "CResourceGroup::OnCallAnswered"));
   a_inboundSipResource->RegisterForNotification( this, l_onAnsweredTask, SIP_RESOURCE_ANSWERED_MESSAGE);

   ATaskSptr l_onReqModifyCallTask( new CTask1<CSipResourceSptr>(
                                    boost::bind( &CResourceGroup::OnCallModify, this, _1),
                                                 "CResourceGroup::OnCallModify"));
   a_inboundSipResource->RegisterForNotification( this, l_onReqModifyCallTask, SIP_RESOURCE_REQ_MODIFY_CALL);
   
   ATaskSptr l_onOutboundReleasedTask( new CTask0( boost::bind( &CResourceGroup::OnOutboundCallReleased, this),
                                                                "CResourceGroup::OnOutboundCallReleased"));
   a_outboundSipResource->RegisterForNotification( this, l_onOutboundReleasedTask, SIP_RESOURCE_CALL_RELEASED);

   ATaskSptr l_onCallAlertingTask( new CTask1<CSipCallInfoSptr>(  
                                    boost::bind( &CResourceGroup::OnCallAlerting, this, _1),
                                                 "CResourceGroup::OnCallAlerting"));
   a_outboundSipResource->RegisterForNotification( this, l_onCallAlertingTask, SIP_RESOURCE_ALERTING);

   ATaskSptr l_onConnectedTask( new CTask1<CSipCallInfoSptr>(  
                                    boost::bind( &CResourceGroup::OnCallConnected, this, _1),
                                                 "CResourceGroup::OnCallConnected"));
   a_outboundSipResource->RegisterForNotification( this, l_onConnectedTask, SIP_RESOURCE_CONNECTED);

   ATaskSptr l_onInboundInfoTask( new CTask1<CSipResourceSptr>(  
                                    boost::bind( &CResourceGroup::OnInfoMessage, this, _1),
                                                 "CResourceGroup::OnInfoMessage"));
   a_inboundSipResource->RegisterForNotification( this, l_onInboundInfoTask, SIP_RESOURCE_INFO_RECEIVED);

   ATaskSptr l_onOutboundInfoTask( new CTask1<CSipResourceSptr>(  
                                    boost::bind( &CResourceGroup::OnInfoMessage, this, _1),
                                                 "CResourceGroup::OnInfoMessage"));
   a_outboundSipResource->RegisterForNotification( this, l_onOutboundInfoTask, SIP_RESOURCE_INFO_RECEIVED);

   ATaskSptr l_onInboundInfoResponseTask( new CTask1<CSipResourceSptr>(
                                    boost::bind( &CResourceGroup::OnInfoMessageResponse, this, _1),
                                                 "CResourceGroup::OnInfoMessageResponse"));
   a_inboundSipResource->RegisterForNotification( this, l_onInboundInfoResponseTask, SIP_RESOURCE_INFO_RESPONSE);

   ATaskSptr l_onOutboundInfoResponseTask( new CTask1<CSipResourceSptr>(
                                    boost::bind( &CResourceGroup::OnInfoMessageResponse, this, _1),
                                                 "CResourceGroup::OnInfoMessageResponse"));
   a_outboundSipResource->RegisterForNotification( this, l_onOutboundInfoResponseTask, SIP_RESOURCE_INFO_RESPONSE);

   ATaskSptr l_onInboundInfoResponseSentTask( new CTask1<CSipResourceSptr>(
                                    boost::bind( &CResourceGroup::OnSendInfoMessageResponse, this, _1),
                                                 "CResourceGroup::OnSendInfoMessageResponse"));
   a_inboundSipResource->RegisterForNotification( this, l_onInboundInfoResponseSentTask, SIP_RESOURCE_INFO_RESPONSE_SENT);

   ATaskSptr l_onOutboundInfoResponseSentTask( new CTask1<CSipResourceSptr>(
                                    boost::bind( &CResourceGroup::OnSendInfoMessageResponse, this, _1),
                                                 "CResourceGroup::OnSendInfoMessageResponse"));
   a_outboundSipResource->RegisterForNotification( this, l_onOutboundInfoResponseSentTask, SIP_RESOURCE_INFO_RESPONSE_SENT);

   ATaskSptr l_onDialogStartedTask( new CTask1<CSipCallInfoSptr>(
                                    boost::bind( &CResourceGroup::OnStartDialog, this, _1),
                                                 "CResourceGroup::OnStartDialog"));
   a_outboundSipResource->RegisterForNotification( this, l_onDialogStartedTask, SIP_RESOURCE_MSML_SENT);

   ATaskSptr l_onDialogResponseTask( new CTask1<CSipCallInfoSptr>(
                                    boost::bind( &CResourceGroup::OnDialogResponse, this, _1),
                                                 "CResourceGroup::OnDialogResponse"));
   a_outboundSipResource->RegisterForNotification( this, l_onDialogResponseTask, SIP_RESOURCE_MSML_RESPONSE);

   ATaskSptr l_onDialogEventTask( new CTask1<CSipCallInfoSptr>(
                                    boost::bind( &CResourceGroup::OnDialogEvent, this, _1),
                                                 "CResourceGroup::OnDialogEvent"));
   a_outboundSipResource->RegisterForNotification( this, l_onDialogEventTask, SIP_RESOURCE_MSML_RECEIVED);

   ATaskSptr l_onSendDialogEventResponseTask( new CTask1<CSipCallInfoSptr>(
                                    boost::bind( &CResourceGroup::OnSendDialogEventResponse, this, _1),
                                                 "CResourceGroup::OnSendDialogEventResponse"));
   a_outboundSipResource->RegisterForNotification( this, l_onSendDialogEventResponseTask, SIP_RESOURCE_MSML_RESPONSE_SENT);
   
}

///////////////////////////////////////////////////////////////////////////////
// Function: CResourceGroup::~CResourceGroup()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CResourceGroup::~CResourceGroup()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CResourceGroupSptr CResourceGroup::SharedPtr()
//
// Description: Obtain a shared pointer for the object
//
// Return: CResourceGroupSptr 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CResourceGroupSptr CResourceGroup::SharedPtr()
{
   return shared_from_this();
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CResourceGroup::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CResourceGroup::ClassName()
{
   return "CResourceGroup";
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CResourceGroup::HasSipResource(ASipResourceSptr a_sipResource)
//
// Description: Test if the Resource Group has a given SIP Resource
//
// Return: bool 
//
// Parameters: ASipResourceSptr a_sipResource 
//
///////////////////////////////////////////////////////////////////////////////
bool CResourceGroup::HasSipResource( ASipResourceSptr a_sipResource)
{
   return (a_sipResource == m_inboundSipCall) || (a_sipResource == m_outboundSipCall);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroup::OutboundSipResource(ASipResourceSptr a_sipResource)
//
// Description: Set the SIP Resource used for outbound calls
//
// Return: void 
//
// Parameters: ASipResourceSptr a_sipResource 
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroup::OutboundSipResource( ASipResourceSptr a_sipResource)
{
   m_outboundSipCall = a_sipResource;
}

///////////////////////////////////////////////////////////////////////////////
// Function: ASipResourceSptr& CResourceGroup::InboundSipResource()
//
// Description: Access the SIP Resource used for inbound calls
//
// Return: ASipResourceSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ASipResourceSptr& CResourceGroup::InboundSipResource()
{
   return m_inboundSipCall;
}

///////////////////////////////////////////////////////////////////////////////
// Function: ASipResourceSptr& CResourceGroup::OutboundSipResource()
//
// Description: Access the SIP Resource used for outbound calls
//
// Return: ASipResourceSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ASipResourceSptr& CResourceGroup::OutboundSipResource()
{
   return m_outboundSipCall;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipCallInfoSptr& CResourceGroup::InboundSipCallInfo()
//
// Description: Access the SIP call info for the inbound call
//
// Return: CSipCallInfoSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CSipCallInfoSptr& CResourceGroup::InboundSipCallInfo()
{
   return m_inboundSipCallInfo;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipCallInfoSptr& CResourceGroup::OutboundSipCallInfo()
//
// Description: Access the SIP call info for the outbound call
//
// Return: CSipCallInfoSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CSipCallInfoSptr& CResourceGroup::OutboundSipCallInfo()
{
   return m_inboundSipCallInfo;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string CResourceGroup::MsmlConnectionTag()
//
// Description: Access the MSML connection tag
//
// Return: const std::string
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string CResourceGroup::MsmlConnectionTag()
{
   return m_msmlConnectionTag;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CResourceGroup::MsmlConnectionTag(const std::string msmlConnectionTag)
//
// Description: Set the MSML connection tag
//
// Return: void
//
// Parameters: const std::string a_msmlConnectionTag
//
///////////////////////////////////////////////////////////////////////////////
void CResourceGroup::MsmlConnectionTag( const std::string a_msmlConnectionTag)
{
   m_msmlConnectionTag = a_msmlConnectionTag;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnCallDisconnected(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a SIP resource Call Disconnected event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnCallDisconnected( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnCallDisconnected");
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimRejectCall(const int a_code)
//
// Description: Reject an offered inbound call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const int a_code
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimRejectCall( const int a_code)
{
   LogDebug("PrimRejectCall");
   m_inboundSipCall->Reject( a_code);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimMakeAvailable()
//
// Description: Make the Resource Group availablew for dialog processing by 
// establishing a connection with the MSML server and answering the inbound 
// call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimMakeAvailable()
{
   LogDebug("PrimMakeAvailable");

   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo());
   m_outboundSipCallInfo->To( "sip:"+ CConfigOptions::Instance()->MsmlServerAddress());
   m_outboundSipCallInfo->From( "sip:"+ CConfigOptions::Instance()->AppServerAddress());
   m_outboundSipCallInfo->OfferSdp( m_inboundSipCall->SipCallInfo()->OfferSdp());

   m_outboundSipCall->MakeCall( m_outboundSipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnCallAlerting(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle an outbound call alerting event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnCallAlerting( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnCallAlerting");
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnCallConnected(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle an outbound call connected event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnCallConnected( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnCallConnected");
   const std::string& l_sipTo = a_sipCallInfo->To();
   MsmlConnectionTag(l_sipTo.substr( l_sipTo.find("tag=") + 4));

   m_inboundSipCallInfo->AnswerSdp( a_sipCallInfo->AnswerSdp());
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimAcceptCall()
//
// Description: Accept an inbound call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimAcceptCall()
{
   LogDebug("PrimAcceptCall");
   m_inboundSipCall->Accept();;
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnCallAccepted()
//
// Description: Handle an inbound call accepted event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnCallAccepted()
{
   LogDebug("PrimOnCallAccepted");
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimAnswerCall(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Answer the inbound call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimAnswerCall( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimAnswerCall");
   VideoAvailable( a_sipCallInfo->VideoAvailableInAnswerSdp());
   m_inboundSipCall->Answer( a_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnCallAnswered(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle an inbound call answered event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnCallAnswered( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnCallAnswered");
   return 0;
}



///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnAvailable()
//
// Description: The resource group is now available for processing dialogs
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnAvailable()
{
   LogDebug("PrimOnAvailable");
   CResourceGroupSptr l_resourceGroup(SharedPtr());
   NotifyObservers( RESOURCEGROUP_GROUP_AVAILABLE, l_resourceGroup);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnInfoMessagePassThru(const ASipResourceSptr &a_sipResource)
//
// Description: Handle an INFO message that is not involvced with a dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnInfoMessagePassThru( const ASipResourceSptr& a_sipResource)
{
   LogDebug("PrimOnInfoMessagePassThru");
   m_infoMessageSipCallInfo = a_sipResource->SipCallInfo();
   m_infoMessageSource = a_sipResource;
   if ( a_sipResource == InboundSipResource())
   {
      m_infoMessageTarget = OutboundSipResource();
   }
   else
   {
      m_infoMessageTarget = InboundSipResource();
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimSendInfoMessagePassThru(const ASipResourceSptr &a_sipResource)
//
// Description: Send an INFO message that is not involved with a dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimSendInfoMessagePassThru( const ASipResourceSptr& a_sipResource)
{
   LogDebug("PrimSendInfoMessagePassThru");
   m_infoMessageTarget->SendInfoMessage( m_infoMessageSipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnInfoMessageResponsePassThru(const ASipResourceSptr &a_sipResource)
//
// Description: Handle an INFO message response that is not involved with a 
// dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnInfoMessageResponsePassThru( const ASipResourceSptr& a_sipResource)
{
   LogDebug("PrimOnInfoMessageResponsePassThru");
   m_infoMessageSipCallInfo->ResponseType( a_sipResource->SipCallInfo()->ResponseType());
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimSendInfoMessageResponsePassThru(const ASipResourceSptr &a_sipResource)
//
// Description: Send an INFO message response that is not involved with a 
// dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimSendInfoMessageResponsePassThru( const ASipResourceSptr& a_sipResource)
{
   LogDebug("PrimSendInfoMessageResponsePassThru");
   m_infoMessageSipCallInfo->ResponseType( IP_MSGTYPE_SIP_INFO_OK);
   m_infoMessageSource->SendInfoMessageResponse( m_infoMessageSipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnSendInfoMessageResponsePassThru(const ASipResourceSptr &a_sipResource)
//
// Description: Handle a send INFO message response completion event for an 
// INFO message that is not involved with a dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnSendInfoMessageResponsePassThru( const ASipResourceSptr& a_sipResource)
{
   LogDebug("PrimOnSendInfoMessageResponsePassThru");
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimStartDialog(const ADialogSptr &a_dialog)
//
// Description: Send an INFO message to start a dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ADialogSptr &a_dialog
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimStartDialog( const ADialogSptr& a_dialog)
{
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo());
   l_sipCallInfo->MimeType( a_dialog->ContentType());
   l_sipCallInfo->MimeData( a_dialog->Content());
   m_outboundSipCall->SendInfoMessage( l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnStartDialog(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a start dialog completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnStartDialog( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnStartDialog");
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnDialogResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a MSML server response for a dialog start
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnDialogResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnDialogResponse");

 // TODO:   There may be an HMP bug on Linux because the 200 OK message 
 //         in Ethereal has the correct data but the GC event doesnt.  
 //         Works OK on Windows.
 //         There is an INFO message for setting video attribs that
 //         arrives immediately after the 200 OK.


   CMsmlResponseSptr l_responseData( new CMsmlResponse( a_sipCallInfo->MimeData()));

 #ifdef _WIN32

   if ( l_responseData->ResponseCode() == "200")

#else

   if ( a_sipCallInfo->ResponseCode() == 200)

#endif
   {
      LogDebug("PrimOnDialogResponse", "started");
      NotifyObservers( RESOURCEGROUP_DIALOG_STARTED, l_responseData);
   }
   else
   {
      LogDebug("PrimOnDialogResponse", "failed");
      NotifyObservers( RESOURCEGROUP_DIALOG_FAILED, l_responseData);
      return -1;
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnDialogEvent(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a dialog event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnDialogEvent( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnDialogEvent");
   if ( a_sipCallInfo->IsDialogExit())
   {
      return 0;
   }
   return 1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimSendDialogEventResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Send a dialog event INFO message response
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimSendDialogEventResponse");
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo());
   l_sipCallInfo->ResponseType( IP_MSGTYPE_SIP_INFO_OK);
   m_outboundSipCall->SendInfoMessageResponse( l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnSendDialogEventResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle send dialog event response completion
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnSendDialogEventResponse");

   CMsmlEventSptr l_event( new CMsmlEvent( a_sipCallInfo->MimeData()));
   if ( a_sipCallInfo->IsDialogExit())
   {
      CMsmlResponseSptr l_response( new CMsmlResponse( a_sipCallInfo->MimeData()));
      const std::string& l_status = l_event->ParmValue( "dialog.exit.status");
      if ( !l_status.empty() && l_status != "200")
      {
         NotifyObservers( RESOURCEGROUP_DIALOG_FAILED, l_response);
      }
      else
      {
         NotifyObservers( RESOURCEGROUP_DIALOG_COMPLETE, l_response);
      }
   }
   else
   {
      NotifyObservers( RESOURCEGROUP_DIALOG_EVENT, l_event);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimSendMediaCommand(const ADialogSptr &a_mediaCommand)
//
// Description: Send an INFO message to issue a command
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const ADialogSptr &a_mediaCommand
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimSendMediaCommand( const ADialogSptr& a_mediaCommand)
{
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo());
   l_sipCallInfo->MimeType( a_mediaCommand->ContentType());
   l_sipCallInfo->MimeData( a_mediaCommand->Content());
   m_outboundSipCall->SendInfoMessage( l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnMediaCommandSent(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a media command sent event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnMediaCommandSent( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnMediaCommandSent");
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnMediaCommandResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Handle a MSML server response for a command
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnMediaCommandResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimOnMediaCommandResponse");

 // TODO:   There may be an HMP bug on Linux because the 200 OK message 
 //         in Ethereal has the correct data but the GC event doesnt.  
 //         Works OK on Windows.
 //         There is an INFO message for setting video attribs that
 //         arrives immediately after the 200 OK.


   CMsmlResponseSptr l_responseData( new CMsmlResponse( a_sipCallInfo->MimeData()));

 #ifdef _WIN32

//   std::string l_response = a_sipCallInfo->MimeData();
//   std::string l_responseCode;
//   const std::string l_responseCodeLabel = "result response=\"";
//   unsigned int l_seperatorPos = l_response.find(l_responseCodeLabel);
//   if ( l_seperatorPos != l_response.npos)
//   {
//      l_responseCode = l_response.substr( l_seperatorPos + l_responseCodeLabel.size(), 3);
//   }

   if ( l_responseData->ResponseCode() == "200")

#else

   if ( a_sipCallInfo->ResponseCode() == 200)

#endif
   {
      LogDebug("PrimOnMediaCommandResponse", "started");
      NotifyObservers( RESOURCEGROUP_MEDIA_COMMAND_COMPLETE, l_responseData);
   }
   else
   {
      LogDebug("PrimOnMediaCommandResponse", "failed");
      NotifyObservers( RESOURCEGROUP_MEDIA_COMMAND_FAILED, l_responseData);
      return -1;
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimReset()
//
// Description: Drop both calls
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimReset()
{
   LogDebug("PrimReset");
   InboundSipResource()->DropCall();
   OutboundSipResource()->DropCall();
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnInboundCallReleased()
//
// Description: Unregister for events from inbound call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnInboundCallReleased()
{
   LogDebug("PrimOnInboundCallReleased");
   m_inboundSipCall->Unregister( this);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnOutboundCallReleased()
//
// Description: Unregister for events from inbound call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnOutboundCallReleased()
{
   LogDebug("PrimOnOutboundCallReleased");
   m_outboundSipCall->Unregister( this);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimOnReset()
//
// Description: Handle reset completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimOnReset()
{
   LogDebug("PrimOnReset");
   CResourceGroupSptr l_resourceGroup(SharedPtr());
   NotifyObservers( RESOURCEGROUP_GROUP_RESET, l_resourceGroup);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CResourceGroup::PrimDisconnect()
//
// Description: Disconnect the inbound call - the outbound call will be 
// disconnected when the Resource Group is reset
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CResourceGroup::PrimDisconnect()
{
   LogDebug("PrimDisconnect");
   m_inboundSipCall->Disconnect();
   return 0;
}

