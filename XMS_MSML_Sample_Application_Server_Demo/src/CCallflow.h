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
// File Name: CCallflow.h
//
// Description: 
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCallflow_h
#define CCallflow_h

#include <boost/enable_shared_from_this.hpp>

#include "TypeDefs.h"
#include "ACallflow.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflow
//
// Description: 
//
///////////////////////////////////////////////////////////////////////////////
class CCallflow : public ACallflow, public boost::enable_shared_from_this<CCallflow>
{
public:
   CCallflow( CTaskProcessorSptr taskProcessor, AResourceGroupSptr a_resourceGroup);
   virtual ~CCallflow();

   CCallflowSptr SharedPtr();

   const char* ClassName();

   bool HasResourceGroup( AResourceGroupSptr a_resourceGroup);
   AResourceGroupSptr ResourceGroup();

private:
   CCallflow();

   AResourceGroupSptr m_resourceGroup;

   int PrimStart();
   int PrimReset();
   int PrimDisconnect();
   int PrimOnDialogFailed( const CMsmlResponseSptr& a_responseData);
   int PrimOnDialogEvent( const CMsmlEventSptr& a_event);
   int PrimOnDialogComplete( const CMsmlResponseSptr& a_response);

   int PrimMainMenu();
   int PrimVMailMenu();
   int PrimAnnounceDisconnect();
   int PrimFeatureUnavailable();
   int PrimNotImplemented();
   int PrimInvalidMenuInput();

   int PrimGetMailbox();
   int PrimVMailRecordStart( const std::string& a_mailbox);
   int PrimVMailRecord( const std::string& a_mailbox);
   int PrimVMailRecordOptions();
   int PrimVMailRecordSave();
   int PrimVMailRecordPlay( const std::string& a_mailbox);
   int PrimVMailRecordCancel( const std::string& a_mailbox);

   int PrimVMailPlay( const std::string& a_mailbox);
   int PrimVMailPlayOptions();
   int PrimVMailPlayDelete( const std::string& a_mailbox);

   int PrimInvalidMailbox();
   int PrimEmptyMailbox();

   int PrimConferenceMenu();
   int PrimGetConferenceId();
   int PrimInvalidConferenceId();
   int PrimConferenceIdDoesNotExist();
   int PrimConferenceIdAlreadyExists();
   int PrimCreateConference( const std::string& a_conferenceId);
   int PrimOnCreateConference( const CMsmlResponseSptr& a_response);
   int PrimJoinConference( const std::string& a_conferenceId);
   int PrimOnJoinConference( const CMsmlResponseSptr& a_response);
   int PrimLeaveConference( const std::string& a_conferenceId);

   int PrimModifyConference(const std::string& a_conferenceId, int a_action);
   int PrimOnModifyConference( const CMsmlResponseSptr& a_response);
   int PrimCollectDtmfs();
   int PrimModifyStream(const std::string& a_conferenceId);
   int PrimOnModifyStream(const CMsmlResponseSptr& a_response);

   void StartDialog( const std::string& a_script);
   void CheckMailbox( const std::string& a_mailbox, bool a_videoIsActive);
   void DeleteMessage( const std::string& a_mailbox);

   int PrimOnMessageDeleted( int a_result);

};
#endif
