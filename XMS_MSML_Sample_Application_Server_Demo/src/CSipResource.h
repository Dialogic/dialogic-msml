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
// File Name: CSipResource.h
//
// Description: CSipResource calss declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CSipResource_h
#define CSipResource_h

#include <boost/enable_shared_from_this.hpp>

#include "TypeDefs.h"
#include "ASipResource.h"
#include "CSipCallInfo.h"

#include <string>

#include <gcip.h>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResource
//
// Description: The SIP Resource class is responsible or opening/closing GC SIP
// devices, handling GC device events and making all SIP device GC API calls.
//
///////////////////////////////////////////////////////////////////////////////
class CSipResource : public ASipResource, public boost::enable_shared_from_this<CSipResource>
{
public:
   CSipResource( CTaskProcessorSptr a_taskProcessor, const std::string& a_deviceName);
   virtual ~CSipResource();

   const char* ClassName();

   CSipResourceSptr SharedPtr();

   CSipCallInfoSptr& SipCallInfo();

private:
   CSipResource();

   std::string m_deviceName;
   LINEDEV m_srlDeviceHandle;
   CRN m_crn;

   CSipCallInfoSptr m_sipCallInfo;
   CSrlEventManagerSptr m_srlEventManager;

   int PrimOpen( const CSrlEventManagerSptr& a_srlEventManager);
   int PrimOnOpened( const CMetaEventSptr& a_metaEvent);
   int PrimOnSetConfigData( const CMetaEventSptr& a_metaEvent);
   int PrimOnUnblocked( const CMetaEventSptr& a_metaEvent);
   int PrimEnableInboundCalls();
   int PrimOnBlocked();
   int PrimClose();
   int PrimOnClosed();

   int PrimOnOffered(  const CMetaEventSptr& a_metaEvent);
   int PrimReject( int a_code);
   int PrimAccept();
   int PrimOnReqModifyCall(  const CMetaEventSptr& a_metaEvent);
   int PrimOnAccepted( const CMetaEventSptr& a_metaEvent);
   int PrimAnswer( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnAnswered( const CMetaEventSptr& a_metaEvent);
   int PrimOnAck( const CMetaEventSptr& a_metaEvent);
   int PrimOnDisconnect(  const CMetaEventSptr& a_metaEvent);
   int PrimDropCall();
   int PrimOnCallDropped( const CMetaEventSptr& a_metaEvent);
   int PrimReleaseCall();
   int PrimOnCallReleased( const CMetaEventSptr& a_metaEvent);

   int PrimMakeCall( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnDialing( const CMetaEventSptr& a_metaEvent);
   int PrimOnAlerting( const CMetaEventSptr& a_metaEvent);
   int PrimOnConnected( const CMetaEventSptr& a_metaEvent);
   int PrimOn200Ok( const CMetaEventSptr& a_metaEvent);
   int PrimOnAckOk( const CMetaEventSptr& a_metaEvent);

   int PrimOnInfoMessage( const CMetaEventSptr& a_metaEvent);
   int PrimSendInfoMessageResponse( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnSendInfoMessageResponse( const CMetaEventSptr& a_metaEvent);
   int PrimSendInfoMessage( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnSendInfoMessage( const CMetaEventSptr& a_metaEvent);
   int PrimOnInfoMessageResponse( const CMetaEventSptr& a_metaEvent);

   int PrimOnTaskFail( const CMetaEventSptr& a_metaEvent);

   int PrimDisconnect();

   void LogGcError( const char* a_method, int a_deviceHandle);
   void GetSipCallInfo( const CMetaEventSptr& a_metaEvent);
   void GetSipCallInfoExt( const CMetaEventSptr& a_metaEvent);
   void GetSipCallInfo( GC_PARM_BLK* parmBlock, const CMetaEventSptr& a_metaEvent);
};

#endif

