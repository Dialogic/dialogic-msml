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
// File Name: CResourceGroup.h
//
// Description: CResourceGroup class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CResourceGroup_h
#define CResourceGroup_h

#include <boost/enable_shared_from_this.hpp>

#include "TypeDefs.h"
#include "AResourceGroup.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroup
//
// Description: Resource Groups are responsible for controling and coordinating
// two SIP resources.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroup : public AResourceGroup, public boost::enable_shared_from_this<CResourceGroup>
{
public:
   CResourceGroup( CTaskProcessorSptr a_taskProcessor, 
                   ASipResourceSptr a_inboundSipResource, 
                   ASipResourceSptr a_outboundSipResource);
   virtual ~CResourceGroup();

   CResourceGroupSptr SharedPtr();

   const char* ClassName();

   bool HasSipResource( ASipResourceSptr a_sipResource);
   void OutboundSipResource( ASipResourceSptr a_sipResource);
   ASipResourceSptr& InboundSipResource();
   ASipResourceSptr& OutboundSipResource();

   CSipCallInfoSptr& InboundSipCallInfo();
   CSipCallInfoSptr& OutboundSipCallInfo();

   const std::string MsmlConnectionTag();

private:
   CResourceGroup();

   ASipResourceSptr m_inboundSipCall;
   ASipResourceSptr m_outboundSipCall;

   CSipCallInfoSptr m_inboundSipCallInfo;
   CSipCallInfoSptr m_outboundSipCallInfo;

   ASipResourceSptr m_infoMessageSource;
   ASipResourceSptr m_infoMessageTarget;
   CSipCallInfoSptr m_infoMessageSipCallInfo;

   int PrimMakeAvailable();
   int PrimRejectCall( const int a_code);
   int PrimAcceptCall();
   int PrimOnCallAccepted();
   int PrimAnswerCall( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnCallAnswered( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnCallAlerting( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnCallConnected( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnCallDisconnected( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnAvailable();

   int PrimOnInfoMessagePassThru( const ASipResourceSptr& a_sipResource);
   int PrimSendInfoMessagePassThru( const ASipResourceSptr& a_sipResource);
   int PrimOnInfoMessageResponsePassThru( const ASipResourceSptr& a_sipResource);
   int PrimSendInfoMessageResponsePassThru( const ASipResourceSptr& a_sipResource);
   int PrimOnSendInfoMessageResponsePassThru( const ASipResourceSptr& a_sipResource);

   int PrimStartDialog( const ADialogSptr& a_dialog);
   int PrimOnStartDialog( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnDialogResponse( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnDialogEvent( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnSendDialogEventResponse( const CSipCallInfoSptr& a_sipCallInfo);

   int PrimSendMediaCommand( const ADialogSptr& a_dialog);
   int PrimOnMediaCommandSent( const CSipCallInfoSptr& a_sipCallInfo);
   int PrimOnMediaCommandResponse( const CSipCallInfoSptr& a_sipCallInfo);

   int PrimReset();
   int PrimOnInboundCallReleased();
   int PrimOnOutboundCallReleased();
   int PrimOnReset();

   int PrimDisconnect();

   void MsmlConnectionTag( const std::string a_msmlConnectionTag);
   std::string m_msmlConnectionTag;

};

#endif
