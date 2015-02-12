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
// File Name: CSipResource.cpp
//
// Description: CSipResource class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

#include "TypeDefs.h"
#include "CSipResource.h"
#include "CConfigOptions.h"
#include "CSrlEventManager.h"
#include "CMetaEvent.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CSipResource::CSipResource(CTaskProcessorSptr a_taskProcessor, const std::string &a_deviceName)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//             const std::string &a_deviceName
//
///////////////////////////////////////////////////////////////////////////////
CSipResource::CSipResource( CTaskProcessorSptr a_taskProcessor, const std::string& a_deviceName) 
   : ASipResource( a_taskProcessor)
   , m_deviceName( a_deviceName)
   , m_srlDeviceHandle( -1)
   , m_crn(-1)
   , m_sipCallInfo( new CSipCallInfo())
{
   Name( a_deviceName);
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipResource::~CSipResource()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CSipResource::~CSipResource()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CSipResource::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CSipResource::ClassName()
{
   return "CSipResource";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipResourceSptr CSipResource::SharedPtr()
//
// Description: Obtain a shared pointer for this object
//
// Return: CSipResourceSptr 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CSipResourceSptr CSipResource::SharedPtr()
{
   return shared_from_this();
}

///////////////////////////////////////////////////////////////////////////////
// Function: CSipCallInfoSptr& ::SipCallInfo()
//
// Description: Access the SIP call info
//
// Return: CSipCallInfoSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CSipCallInfoSptr& CSipResource::SipCallInfo()
{
   return m_sipCallInfo;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOpen(const CSrlEventManagerSptr &a_srlEventManager)
//
// Description: Register for events from the SRL Event Manager and open the device
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSrlEventManagerSptr &a_srlEventManager
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOpen( const CSrlEventManagerSptr& a_srlEventManager)
{
   LogDebug("PrimOpen");

   m_srlEventManager = a_srlEventManager;

   ATaskSptr l_onOpenedTask( new CTask1<CMetaEventSptr>(  
                                    boost::bind( &CSipResource::OnOpened, this, _1),
                                                 "CSipResource::OnOpened"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onOpenedTask, GCEV_OPENEX);

   ATaskSptr l_onSetConfigDataTask( new CTask1<CMetaEventSptr>(  
                                    boost::bind( &CSipResource::OnSetConfigData, this, _1),
                                                 "CSipResource::OnSetConfigData"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onSetConfigDataTask, GCEV_SETCONFIGDATA);

   ATaskSptr l_onUnblockedTask( new CTask1<CMetaEventSptr>(  
                                       boost::bind( &CSipResource::OnUnblocked, this, _1),
                                                     "CSipResource::OnUnblocked"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onUnblockedTask, GCEV_UNBLOCKED);

   ATaskSptr l_onOfferedTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnOffered, this, _1),
                                                  "CSipResource::OnOffered"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onOfferedTask, GCEV_OFFERED);

   ATaskSptr l_onReqModifyCallTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnReqModifyCall, this, _1),
                                                  "CSipResource::OnReqModifyCall"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onReqModifyCallTask, GCEV_REQ_MODIFY_CALL);

   ATaskSptr l_onAcceptedTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnAccepted, this, _1),
                                                  "CSipResource::OnAccepted"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onAcceptedTask, GCEV_ACCEPT);

   ATaskSptr l_onAnsweredTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnAnswered, this, _1),
                                                  "CSipResource::OnAnswered"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onAnsweredTask, GCEV_ANSWERED);

   ATaskSptr l_onAckTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnAck, this, _1),
                                                  "CSipResource::OnAck"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onAckTask, GCEV_SIP_ACK);

   ATaskSptr l_onDisconnectTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnDisconnect, this, _1),
                                                  "CSipResource::OnDisconnect"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onDisconnectTask, GCEV_DISCONNECTED);

   ATaskSptr l_onCallDroppedTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnCallDropped, this, _1),
                                                  "CSipResource::OnCallDropped"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onCallDroppedTask, GCEV_DROPCALL);

   ATaskSptr l_onCallReleasedTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnCallReleased, this, _1),
                                                  "CSipResource::OnCallReleased"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onCallReleasedTask, GCEV_RELEASECALL);

   ATaskSptr l_onDialingTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnDialing, this, _1),
                                                  "CSipResource::OnDialing"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onDialingTask, GCEV_DIALING);

   ATaskSptr l_onAlertingTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnAlerting, this, _1),
                                                  "CSipResource::OnAlerting"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onAlertingTask, GCEV_ALERTING);

   ATaskSptr l_onConnectedTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnConnected, this, _1),
                                                  "CSipResource::OnConnected"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onConnectedTask, GCEV_CONNECTED);

   ATaskSptr l_on200OkTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::On200Ok, this, _1),
                                                  "CSipResource::On200Ok"));
   a_srlEventManager->RegisterForEventDispatch( this, l_on200OkTask, GCEV_SIP_200OK);

   ATaskSptr l_onAckOkTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnAckOk, this, _1),
                                                  "CSipResource::OnAckOk"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onAckOkTask, GCEV_SIP_ACK_OK);

   ATaskSptr l_onInfoMessageTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnInfoMessage, this, _1),
                                                  "CSipResource::OnInfoMessage"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onInfoMessageTask, GCEV_CALLINFO);

   ATaskSptr l_onExtensionTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnExtension, this, _1),
                                                  "CSipResource::OnExtension"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onExtensionTask, GCEV_EXTENSION);

   ATaskSptr l_onExtensionCompleteTask( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnExtensionComplete, this, _1),
                                                  "CSipResource::OnExtensionComplete"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onExtensionCompleteTask, GCEV_EXTENSIONCMPLT);

   ATaskSptr l_onTaskFail( new CTask1<CMetaEventSptr>(  
                                     boost::bind( &CSipResource::OnTaskFail, this, _1),
                                                  "CSipResource::OnTaskFail"));
   a_srlEventManager->RegisterForEventDispatch( this, l_onTaskFail, GCEV_TASKFAIL);


   std::string l_gcDeviceName = ":P_SIP:N_" + Name();
   if (  gc_OpenEx(  &m_srlDeviceHandle, 
                     const_cast<char*> (l_gcDeviceName.c_str()), 
                     EV_ASYNC, 
                     (void *) this) != GC_SUCCESS)
   {
      LogGcError( "gc_OpenEx Handle", m_srlDeviceHandle);
      return -1;
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnOpened(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle the device open completion event - set device 
// configuration data
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnOpened( const CMetaEventSptr& a_metaEvent)
{ 
   LogDebug("PrimOnOpened");

   GC_PARM_BLKP l_gcParmBlk = 0;
   long l_requestid;
   
   if ( gc_util_insert_parm_val( &l_gcParmBlk,
                                 GCSET_CALLEVENT_MSK,
                                 GCACT_ADDMSK,
                                 sizeof(unsigned long),
                                 GCEV_DIALING) != GC_SUCCESS)
   {
      LogGcError( "gc_util_insert_parm_val:GCEV_DIALING", m_srlDeviceHandle);
      return -1;
   }

   if ( gc_util_insert_parm_val( &l_gcParmBlk,
                                 GCSET_CALLEVENT_MSK,
                                 GCACT_ADDMSK,
                                 sizeof(unsigned long),
                                 GCEV_EXTENSION) != GC_SUCCESS)
   {
      LogGcError( "gc_util_insert_parm_val:GCEV_EXTENSION", m_srlDeviceHandle);
      return -1;
   }

   if ( gc_util_insert_parm_val( &l_gcParmBlk,
                                 GCSET_CALLEVENT_MSK,
                                 GCACT_ADDMSK,
                                 sizeof(unsigned long),
                                 GCEV_EXTENSIONCMPLT) < 0)
   {
      LogGcError( "gc_util_insert_parm_val:GCEV_EXTENSIONCMPLT", m_srlDeviceHandle);
      return -1;
   }

   if ( gc_util_insert_parm_val( &l_gcParmBlk,
                                 GCSET_CALLEVENT_MSK,
                                 GCACT_ADDMSK,
                                 sizeof(unsigned long),
                                 GCMSK_SIP_ACK) != GC_SUCCESS)
   {
      LogGcError( "gc_util_insert_parm_val:GCMSK_SIP_ACK", m_srlDeviceHandle);
      return -1;
   }

   if ( gc_util_insert_parm_val( &l_gcParmBlk,
                                 GCSET_CALLEVENT_MSK,
                                 GCACT_ADDMSK,
                                 sizeof(unsigned long),
                                 GCMSK_200_OK) != GC_SUCCESS)
   {
      LogGcError( "gc_util_insert_parm_val:GCMSK_200_OK", m_srlDeviceHandle);
      return -1;
   }

   if ( gc_SetConfigData( GCTGT_GCLIB_CHAN,
                          m_srlDeviceHandle,
                          l_gcParmBlk,
                          0,
                          GCUPDATE_IMMEDIATE,
                          &l_requestid,
                          EV_ASYNC) != GC_SUCCESS)
   {
      LogGcError( "gc_SetConfigData:GCMSK_200_OK", m_srlDeviceHandle);
      return -1;
   }

   gc_util_delete_parm_blk( l_gcParmBlk); 

//   NotifyObservers( SIP_RESOURCE_OPENED, SharedPtr());

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnSetConfigData(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle set configuration data completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnSetConfigData( const CMetaEventSptr& a_metaEvent)
{ 
   LogDebug("PrimOnSetConfigData");
   return 0;
}
///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnUnblocked(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle device unblocked event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnUnblocked( const CMetaEventSptr& a_metaEvent)
{ 
   LogDebug("PrimOnUnblocked");
   CSipResourceSptr l_sipResource( SharedPtr());
   NotifyObservers( SIP_RESOURCE_UNBLOCKED, l_sipResource);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimEnableInboundCalls()
//
// Description: Make the device available for inbound calls
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimEnableInboundCalls()
{ 
   LogDebug("PrimEnableInboundCalls");

   if ( gc_WaitCall( m_srlDeviceHandle, 0, 0, -1, EV_ASYNC) != GC_SUCCESS)
   {
      LogGcError( "gc_WaitCall", m_srlDeviceHandle);
      return -1;
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnBlocked()
//
// Description: Handle unblocked event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnBlocked()
{ 
   LogDebug("PrimOnBlocked");
   CSipResourceSptr l_sipResource( SharedPtr());
   NotifyObservers( SIP_RESOURCE_BLOCKED, l_sipResource);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimClose()
//
// Description: Close the devoice
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimClose()
{ 
   LogDebug("PrimClose");

   if ( gc_Close( m_srlDeviceHandle) != GC_SUCCESS)
   {
      LogGcError( "gc_Close", m_srlDeviceHandle);
      return -1;
   }

   OnClosed();

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnClosed()
//
// Description: Handle device closed completion event - unregister for SRL 
// event Manager event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnClosed()
{ 
   LogDebug("PrimOnClosed");
   m_srlEventManager->Unregister(this);
   CSipResourceSptr l_sipResource( SharedPtr());
   NotifyObservers( SIP_RESOURCE_CLOSED, l_sipResource);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnOffered(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle call offered event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnOffered( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnOffered");
   m_crn = a_metaEvent->Crn();
   GetSipCallInfo( a_metaEvent);
   CSipResourceSptr l_sipResource( SharedPtr());
   NotifyObservers( SIP_RESOURCE_OFFERED_RESOURCE, l_sipResource);
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
   NotifyObservers( SIP_RESOURCE_OFFERED_MESSAGE, l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnReqModifyCall(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle Modify Call Request
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnReqModifyCall( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnReqModifyCall");
   m_crn = a_metaEvent->Crn();
   GetSipCallInfo( a_metaEvent);
   NotifyObservers( SIP_RESOURCE_REQ_MODIFY_CALL);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimReject(const int a_code)
//
// Description: Reject an offered call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const int a_code
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimReject( const int a_code)
{
   LogDebug("PrimReject");
   //TODO: implement & test
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimAccept()
//
// Description: Accept an offered call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimAccept()
{
   LogDebug("PrimAccept");

   if ( gc_AcceptCall( m_crn, 0, EV_ASYNC) != GC_SUCCESS)
   {
      LogGcError( "gc_WaitCall", m_srlDeviceHandle);
      return -1;
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnAccepted(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle accecpt offerd call completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnAccepted( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnAccepted");
   NotifyObservers( SIP_RESOURCE_ACCEPTED);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimAnswer(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Answer an inbound call - set user info
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimAnswer( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimAnswer");

   GC_PARM_BLKP l_gcParmBlk = 0;

   if ( gc_util_insert_parm_ref_ex( &l_gcParmBlk,
                                    IPSET_SDP,
                                    IPPARM_SDP_ANSWER,
                                    strlen( a_sipCallInfo->AnswerSdp().c_str()),
                                    const_cast<char*>( a_sipCallInfo->AnswerSdp().c_str())) != GC_SUCCESS )
   {
      LogGcError( "gc_util_insert_parm_ref_ex", m_srlDeviceHandle);
      return -1;
   }

   if ( gc_SetUserInfo( GCTGT_GCLIB_CRN, 
                        m_crn, 
                        l_gcParmBlk, 
                        GC_NEXT_OUTBOUND_MSG) != GC_SUCCESS )
   {
      LogGcError( "gc_SetUserInfo", m_srlDeviceHandle);
      return -1;
   }
   gc_util_delete_parm_blk( l_gcParmBlk);

   if ( gc_AnswerCall( m_crn, 0, EV_ASYNC) != GC_SUCCESS)
   {
      LogGcError( "gc_AnswerCall", m_srlDeviceHandle);
      return -1;
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnAnswered(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an answer inbound call completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnAnswered(  const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnAnswered");
   GetSipCallInfo( a_metaEvent);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnAck(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an ACK
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnAck(  const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnAck");
   GetSipCallInfo( a_metaEvent);
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
   NotifyObservers( SIP_RESOURCE_ANSWERED_MESSAGE, l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnDisconnect(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a call disconnected event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnDisconnect(  const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnDisconnect");
   CSipResourceSptr l_sipResource( SharedPtr());
   NotifyObservers( SIP_RESOURCE_DISCONNECTED_RESOURCE, l_sipResource);
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
   NotifyObservers( SIP_RESOURCE_DISCONNECTED_MESSAGE, l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimDropCall()
//
// Description: Drop the call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimDropCall()
{

   LogDebug("PrimDropCall");
   if ( gc_DropCall( m_crn, GC_NORMAL_CLEARING, EV_ASYNC) != GC_SUCCESS)
   {
      LogGcError( "gc_DropCall", m_srlDeviceHandle);
      return -1;
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnCallDropped(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a drop call completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnCallDropped( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnCallDropped");
   NotifyObservers( SIP_RESOURCE_CALL_DROPPED);
   ReleaseCall();
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimReleaseCall()
//
// Description: Release the call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimReleaseCall()
{
   LogDebug("PrimReleaseCall");
   if ( gc_ReleaseCallEx( m_crn, EV_ASYNC) != GC_SUCCESS)
   {
      LogGcError( "gc_ReleaseCall", m_srlDeviceHandle);
      return -1;
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnCallReleased(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle release call completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnCallReleased( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnCallReleased");
   NotifyObservers( SIP_RESOURCE_CALL_RELEASED);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimMakeCall(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Set the user info and make an outbound call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimMakeCall( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimMakeCall");

   {
      GC_PARM_BLKP l_parmblk = 0;

      if ( gc_util_insert_parm_ref_ex( &l_parmblk,
                                  IPSET_SDP,
                                  IPPARM_SDP_OFFER,
                                  strlen( a_sipCallInfo->OfferSdp().c_str()),
                                  const_cast<char*>( a_sipCallInfo->OfferSdp().c_str())) != GC_SUCCESS )
      {
         LogGcError( "gc_util_insert_parm_ref_ex", m_srlDeviceHandle);
      }

      if ( gc_SetUserInfo( GCTGT_GCLIB_CHAN, m_srlDeviceHandle, l_parmblk, GC_SINGLECALL) != GC_SUCCESS)
      {
         LogGcError( "gc_SetUserInfo", m_srlDeviceHandle);
      }

      gc_util_delete_parm_blk( l_parmblk);
   }

   GC_MAKECALL_BLK l_gcMakeCallBlock;
   GCLIB_MAKECALL_BLK l_gclibMakeCallBlock = {0};
   l_gcMakeCallBlock.cclib = 0;
   l_gcMakeCallBlock.gclib = &l_gclibMakeCallBlock;
   GC_PARM_BLK* l_parmBlock = 0;

   gc_util_insert_parm_val( &l_parmBlock,
                            IPSET_PROTOCOL,
                            IPPARM_PROTOCOL_BITMASK,
                            sizeof(char),
                            IP_PROTOCOL_SIP);

   strcpy( l_gcMakeCallBlock.gclib->destination.address, a_sipCallInfo->To().c_str());
   l_gcMakeCallBlock.gclib->destination.address_type = GCADDRTYPE_TRANSPARENT;

   sprintf( l_gcMakeCallBlock.gclib->origination.address, a_sipCallInfo->From().c_str());
   l_gcMakeCallBlock.gclib->origination.address_type = GCADDRTYPE_TRANSPARENT;

   if (gc_MakeCall( m_srlDeviceHandle, &m_crn, 0, &l_gcMakeCallBlock, 60, EV_ASYNC) != GC_SUCCESS)
   {
      LogGcError( "gc_MakeCall", m_srlDeviceHandle);
   }

   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
   NotifyObservers( SIP_RESOURCE_MAKING_CALL, l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnDialing(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle "dialing" event after making am outbound call
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnDialing( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnDialing");
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
   NotifyObservers( SIP_RESOURCE_DIALING, l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnAlerting(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an outbound alerting event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnAlerting( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnAlerting");
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
   NotifyObservers( SIP_RESOURCE_ALERTING, l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnConnected(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an outbound call connected event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnConnected( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnConnected");
   GetSipCallInfo( a_metaEvent);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOn200Ok(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an outbound call 200 OK event - send an ACK
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOn200Ok( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOn200Ok");
   GetSipCallInfo( a_metaEvent);
  	if ( gc_SipAck( m_crn, 0, EV_ASYNC) != GC_SUCCESS) 
	{
		LogGcError( "gc_SipAck", m_srlDeviceHandle);
	}
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnAckOk(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a send ACK completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnAckOk( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnAckOk");
   GetSipCallInfo( a_metaEvent);
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
   NotifyObservers( SIP_RESOURCE_CONNECTED, l_sipCallInfo);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnInfoMessage(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an incoming SIP INFO message
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnInfoMessage( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnInfoMessage");
	GetSipCallInfo( a_metaEvent);
   if (SipCallInfo()->IsMsml())
   {
      LogDebug("PrimOnInfoMessage", "SIP_RESOURCE_MSML_RECEIVED");
      CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
      NotifyObservers( SIP_RESOURCE_MSML_RECEIVED, l_sipCallInfo);
   }
   else
   {
      LogDebug("PrimOnInfoMessage", "SIP_RESOURCE_INFO_RECEIVED");
      CSipResourceSptr l_sipResource( SharedPtr());
      NotifyObservers( SIP_RESOURCE_INFO_RECEIVED, l_sipResource);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimSendInfoMessageResponse(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Send a SIP INFO message response
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimSendInfoMessageResponse( const CSipCallInfoSptr& a_sipCallInfo)
{
   switch ( a_sipCallInfo->ResponseType())
   {
   case IP_MSGTYPE_SIP_INFO_OK:
      LogDebug("PrimSendInfoMessageResponse", "IP_MSGTYPE_SIP_INFO_OK");
      break;
   case IP_MSGTYPE_SIP_INFO_FAILED:
      LogDebug("PrimSendInfoMessageResponse", "IP_MSGTYPE_SIP_INFO_FAILED");
      break;
   default:
      LogDebug("PrimSendInfoMessageResponse", AsHexString( a_sipCallInfo->ResponseCode()));
   }

	GC_PARM_BLKP l_parmBlock = 0;
	GC_PARM_BLKP l_returnParmBlock = 0;

	if ( gc_util_insert_parm_val( &l_parmBlock,
                                 IPSET_MSG_SIP,
                                 IPPARM_MSGTYPE,
                                 sizeof(int) ,
                                 a_sipCallInfo->ResponseType()) != GC_SUCCESS)
   {
      LogGcError( "gc_util_insert_parm_val(IPSET_MSG_SIP,IPPARM_MSGTYPE)", m_srlDeviceHandle);
      return -1;
   }

	if ( gc_SetUserInfo(	GCTGT_GCLIB_CRN, m_crn, l_parmBlock, GC_SINGLECALL) != GC_SUCCESS)
	{
		LogGcError( "gc_SetUserInfo", m_srlDeviceHandle);
      return -1;
	}

	if ( gc_Extension(   GCTGT_GCLIB_CRN,
                        m_crn,
                        IPEXTID_SENDMSG,
                        l_parmBlock,
                        &l_returnParmBlock,
                        EV_ASYNC) != GC_SUCCESS)
	{
		LogGcError( "gc_Extension(IPEXTID_SENDMSG)", m_srlDeviceHandle);
      return -1;
	}

	gc_util_delete_parm_blk( l_parmBlock);

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnSendInfoMessageResponse(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a send SIP INFO message response completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnSendInfoMessageResponse( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnSendInfoMessageResponse");
   GetSipCallInfo( a_metaEvent);
   if (SipCallInfo()->IsMsml())
   {
      CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
      NotifyObservers( SIP_RESOURCE_MSML_RESPONSE_SENT, l_sipCallInfo);
   }
   else
   {
      CSipResourceSptr l_sipResource( SharedPtr());
      NotifyObservers( SIP_RESOURCE_INFO_RESPONSE_SENT, l_sipResource);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimSendInfoMessage(const CSipCallInfoSptr &a_sipCallInfo)
//
// Description: Send a SIP INFO message
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CSipCallInfoSptr &a_sipCallInfo
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimSendInfoMessage( const CSipCallInfoSptr& a_sipCallInfo)
{
   LogDebug("PrimSendInfoMessage", "\n" + a_sipCallInfo->MimeData());
   SipCallInfo()->MimeType( a_sipCallInfo->MimeType());
   SipCallInfo()->MimeData( a_sipCallInfo->MimeData());

   GC_PARM_BLKP l_parmBlock = 0;
   GC_PARM_BLKP l_mimeParmBlock = 0;
   GC_PARM_BLKP l_returnParmBlock = 0;

   // build GC_PARM_BLK for MIME
   if ( gc_util_insert_parm_ref_ex( &l_mimeParmBlock,
								            IPSET_MIME,
								            IPPARM_MIME_PART_TYPE,
								            a_sipCallInfo->MimeType().size() + 1,
								            const_cast<char*>(a_sipCallInfo->MimeType().c_str())) != GC_SUCCESS)
   {
		LogGcError( "gc_util_insert_parm_ref_ex(IPPARM_MIME_PART_TYPE)", m_srlDeviceHandle);
   }

   if ( gc_util_insert_parm_val( &l_mimeParmBlock,
								         IPSET_MIME,
                                 IPPARM_MIME_PART_BODY_SIZE,
                                 sizeof(unsigned long),
                                 a_sipCallInfo->MimeData().size()) != GC_SUCCESS)
   {
      LogGcError( "gc_util_insert_parm_ref_ex(IPPARM_MIME_PART_BODY_SIZE)", m_srlDeviceHandle);
   }

   if ( gc_util_insert_parm_val( &l_mimeParmBlock,
                                 IPSET_MIME,
                                 IPPARM_MIME_PART_BODY,
                                 sizeof(unsigned long),
                                 (unsigned long) a_sipCallInfo->MimeData().c_str()) != GC_SUCCESS)
   {
      LogGcError( "gc_util_insert_parm_ref_ex(IPPARM_MIME_PART_BODY)", m_srlDeviceHandle);
   }

   // Build GC_PARM_BLK for INFO message
   if ( gc_util_insert_parm_val(	&l_parmBlock,
                                 IPSET_MSG_SIP,
                                 IPPARM_MSGTYPE,
                                 sizeof(int),
                                 IP_MSGTYPE_SIP_INFO) != GC_SUCCESS)
   {
      LogGcError( "gc_util_insert_parm_ref_ex(IP_MSGTYPE_SIP_INFO)", m_srlDeviceHandle);
   }

   if ( gc_util_insert_parm_val(	&l_parmBlock,
                                 IPSET_MIME,
                                 IPPARM_MIME_PART,
                                 sizeof(unsigned long),
                                 (unsigned long)l_mimeParmBlock) != GC_SUCCESS)
   {
      LogGcError( "gc_util_insert_parm_ref_ex(IPPARM_MIME_PART)", m_srlDeviceHandle);
   }

	if (gc_SetUserInfo(  GCTGT_GCLIB_CRN,
                        m_crn,
                        l_parmBlock,
                        GC_SINGLECALL) != GC_SUCCESS)
	{
      LogGcError( "gc_SetUserInfo", m_srlDeviceHandle);
	}

   if ( gc_Extension(   GCTGT_GCLIB_CRN,
                        m_crn,
                        IPEXTID_SENDMSG,
                        l_parmBlock,
                        &l_returnParmBlock,
                        EV_ASYNC) != GC_SUCCESS)

   {
      LogGcError( "gc_Extension(IPEXTID_SENDMSG)", m_srlDeviceHandle);
   }

   gc_util_delete_parm_blk( l_parmBlock);
   gc_util_delete_parm_blk( l_mimeParmBlock);

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnSendInfoMessage(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a send SIP INFO message completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnSendInfoMessage( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnSendInfoMessage");
   GetSipCallInfo( a_metaEvent);
   CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
   if ( SipCallInfo()->IsMsml())
   {
      NotifyObservers( SIP_RESOURCE_MSML_SENT, l_sipCallInfo);
   }
   else
   {
      NotifyObservers( SIP_RESOURCE_INFO_SENT, l_sipCallInfo);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnInfoMessageResponse(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle an incoming SIP INFO message response
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnInfoMessageResponse( const CMetaEventSptr& a_metaEvent)
{
   GetSipCallInfo( a_metaEvent);

	GC_PARM_BLKP l_parmBlock = (GC_PARM_BLK*)( a_metaEvent->MetaEvent()->extevtdatap);
   GC_PARM_DATAP l_parm = gc_util_find_parm( l_parmBlock, IPSET_MSG_SIP, IPPARM_MSGTYPE );
   if ( l_parm)
   {
      m_sipCallInfo->ResponseType( (int)(*(l_parm->value_buf)));
   }
   else
   {
      m_sipCallInfo->ResponseType( -1);
   }

   l_parm = gc_util_find_parm( l_parmBlock, IPSET_MSG_SIP, IPPARM_MSG_SIP_RESPONSE_CODE);
   if ( l_parm)
   {
      m_sipCallInfo->ResponseCode((int)(*(l_parm->value_buf)));
   }
   else
   {
      m_sipCallInfo->ResponseCode( -1);
   }

   std::string l_temp = AsString( m_sipCallInfo->ResponseType()) + ":" + AsString(m_sipCallInfo->ResponseCode());
   LogDebug("PrimOnInfoMessageResponse", l_temp);

   if ( SipCallInfo()->IsMsml())
   {
      CSipCallInfoSptr l_sipCallInfo( new CSipCallInfo( *SipCallInfo()));
      NotifyObservers( SIP_RESOURCE_MSML_RESPONSE, l_sipCallInfo);
   }
   else
   {
      CSipResourceSptr l_sipResource( SharedPtr());
      NotifyObservers( SIP_RESOURCE_INFO_RESPONSE, l_sipResource);
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimOnTaskFail(const CMetaEventSptr &a_metaEvent)
//
// Description: Handle a GlobalCall task fail event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimOnTaskFail( const CMetaEventSptr& a_metaEvent)
{
   LogDebug("PrimOnTaskFail");
   NotifyObservers( SIP_RESOURCE_TASKFAIL);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CSipResource::PrimDisconnect()
//
// Description: Handle a call disconnected event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CSipResource::PrimDisconnect()
{
   LogDebug("PrimDisconnect");
   CSipResourceSptr l_sipResource( SharedPtr());
   NotifyObservers( SIP_RESOURCE_DISCONNECTED_RESOURCE, l_sipResource);
   return 0;
}


///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResource::LogGcError(const char *a_method, int a_deviceHandle)
//
// Description: Log a GlobalCall error
//
// Return: void
//
// Parameters: const char *a_method
//             int a_deviceHandle
//
///////////////////////////////////////////////////////////////////////////////
void CSipResource::LogGcError( const char* a_method, int a_deviceHandle)
{
   GC_INFO l_gcErrorInfo;
   if ( gc_ErrorInfo( &l_gcErrorInfo) != GC_SUCCESS)
   {
      Logger()->Log( LOG_LEVEL_ERROR, *this, a_method, " gc_ErrorInfo() failed, unable to retrieve error info");
   }
   else
   {
      std::ostringstream l_stream;
      l_stream <<    ATDV_NAMEP( a_deviceHandle)
         << "\n\tGC error="
         << "\n\tgcValue  : 0x" << std::hex << l_gcErrorInfo.gcValue
         << "\n\tgcMsg    : " << l_gcErrorInfo.gcMsg
         << "\n\tccLibId  : " << std::dec << l_gcErrorInfo.ccLibId
         << "\n\tccLibName: " << l_gcErrorInfo.ccLibName
         << "\n\tccValue  : 0x" << std::hex << l_gcErrorInfo.ccValue
         << "\n\tccMsg    : " << l_gcErrorInfo.ccMsg
         << "\n\tinfo     : " << l_gcErrorInfo.additionalInfo;
      const std::string& l_msg = l_stream.str();
      Logger()->Log( LOG_LEVEL_ERROR, *this, a_method, l_msg);
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResource::GetSipCallInfo(const CMetaEventSptr &a_metaEvent)
//
// Description: Get SIP call header and content data
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResource::GetSipCallInfo( const CMetaEventSptr& a_metaEvent)
{
   GC_PARM_BLK* l_parmBlock = static_cast<GC_PARM_BLK*>( a_metaEvent->MetaEvent()->extevtdatap);
   GetSipCallInfo( l_parmBlock, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResource::GetSipCallInfoExt(const CMetaEventSptr &a_metaEvent)
//
// Description: Get SIP call header and content data from an Extension event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResource::GetSipCallInfoExt( const CMetaEventSptr& a_metaEvent)
{
	EXTENSIONEVTBLK *l_extensionBlock = static_cast<EXTENSIONEVTBLK*>( a_metaEvent->MetaEvent()->extevtdatap);
	GC_PARM_BLK *l_parmBlock = &l_extensionBlock->parmblk;
   GetSipCallInfo( l_parmBlock, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipResource::GetSipCallInfo(GC_PARM_BLK *a_parmBlock, const CMetaEventSptr &a_metaEvent)
//
// Description: Get SIP call header and content data
//
// Return: void
//
// Parameters: GC_PARM_BLK *a_parmBlock
//             const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CSipResource::GetSipCallInfo( GC_PARM_BLK* a_parmBlock, const CMetaEventSptr& a_metaEvent)
{
   GC_PARM_DATA_EXT l_parm;
   INIT_GC_PARM_DATA_EXT( &l_parm);

   while ( ( gc_util_next_parm_ex( a_parmBlock, &l_parm)) == GC_SUCCESS)
   {
      switch ( l_parm.set_ID)
      {
         case IPSET_SIP_MSGINFO:
            switch ( l_parm.parm_ID)
            {
               case IPPARM_SIP_HDR:
                  {
                     char* l_parmData = new char[l_parm.data_size+1];
                     strncpy( l_parmData,(char*)l_parm.pData, l_parm.data_size);
                     l_parmData[l_parm.data_size]='\0';
                     if ( strstr( l_parmData, "Call-ID:"))
                     {
                        m_sipCallInfo->CallId( &l_parmData[strlen("Call-ID:")]);
                        Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - Call-ID", m_sipCallInfo->CallId());
                     }
                     else if ( strstr( l_parmData, "To:"))
                     {
                        m_sipCallInfo->To( &l_parmData[strlen("To:")]);
                        Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - To", m_sipCallInfo->To());
                     }
                     else if ( strstr( l_parmData, "From:"))
                     {
                        m_sipCallInfo->From( &l_parmData[strlen("From:")]);
                        Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - From", m_sipCallInfo->From());
                     }
                     else
                     {
                        Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - unknown header", l_parmData);
                     }
                     delete[] l_parmData;
                  }
                  break;
            }
            break;

         case IPSET_SDP:
            switch ( l_parm.parm_ID)
            {
               case IPPARM_SDP_OFFER:
                  {
                     char* l_parmData = new char[l_parm.data_size+1];
                     strncpy( l_parmData,(char*)l_parm.pData, l_parm.data_size);
                     l_parmData[l_parm.data_size]='\0';
                     m_sipCallInfo->OfferSdp( l_parmData);
                     std::string l_temp = "\n" + m_sipCallInfo->OfferSdp();
                     Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - offer sdp", l_temp);
                     delete[] l_parmData;
                  }
                  break;

               case IPPARM_SDP_ANSWER:
                  {
                     char* l_parmData = new char[l_parm.data_size+1];
                     strncpy( l_parmData,(char*)l_parm.pData, l_parm.data_size);
                     l_parmData[l_parm.data_size]='\0';
                     m_sipCallInfo->AnswerSdp( l_parmData);
                     std::string l_temp = "\n" + m_sipCallInfo->AnswerSdp();
                     Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - answer sdp", l_temp);
                     delete[] l_parmData;
                  }
                  break;
            }
            break;

         case IPSET_MIME:
				{
               GC_PARM_BLK* l_mimeParmBlock = (GC_PARM_BLK*)(*(unsigned int*)( l_parm.pData));
               GC_PARM_DATA_EXT l_mimeParm;
               INIT_GC_PARM_DATA_EXT( &l_mimeParm);
					unsigned long l_mimeSize = 0;
					while ( gc_util_next_parm_ex( l_mimeParmBlock, &l_mimeParm) == GC_SUCCESS)
					{
						switch ( l_mimeParm.parm_ID)
						{
						case IPPARM_MIME_PART_TYPE:
                     {
							   char* l_mimeType = new char[l_mimeParm.data_size+1];
							   memcpy( l_mimeType, l_mimeParm.pData, l_mimeParm.data_size);
							   l_mimeType[ l_mimeParm.data_size] = '\0';
                        m_sipCallInfo->MimeType( l_mimeType);
                        Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - MIME type", m_sipCallInfo->MimeType());
                        delete[] l_mimeType;
                     }
							break;

						case IPPARM_MIME_PART_BODY_SIZE:
                     l_mimeSize = *(unsigned long*)( l_mimeParm.pData);
                     Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - MIME size", l_mimeSize);
							break;

						case IPPARM_MIME_PART_BODY:
                     if ( l_mimeSize > 0)
                     {
							   char* l_mimeData = new char[l_mimeSize+1];
							   memcpy( l_mimeData, (char*)(*(unsigned long*)(l_mimeParm.pData)), l_mimeSize);
							   l_mimeData[ l_mimeSize] = '\0';
                        m_sipCallInfo->MimeData( l_mimeData);
                        std::string l_temp = "\n" + m_sipCallInfo->MimeData();
                        Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - MIME data", l_temp);
                     }
							break;

						default:
                     Logger()->Log( LOG_LEVEL_DEBUG, *this, "GetSipCallInfo - IPSET_MIME", l_mimeParm.parm_ID);
							break;
						}
               }
            }
            break;
      }
   }
}

