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
// File Name: CCallflow.cpp
//
// Description: CCallflow class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "boost/bind.hpp"

#include "CCallflow.h"
#include "AResourceGroup.h"
#include "CMsmlDialog.h"
#include "CMsmlDialogVoiceMailRecordStart.h"
#include "CMsmlDialogVideoMailRecordStart.h"
#include "CMsmlDialogVoiceMailRecord.h"
#include "CMsmlDialogVideoMailRecord.h"
#include "CMsmlDialogVoiceMailPlay.h"
#include "CMsmlDialogVideoMailPlay.h"
#include "CMsmlCreateConference.h"
#include "CMsmlCreateVideoConference.h"
#include "CMsmlJoinConference.h"
#include "CMsmlJoinVideoConference.h"
#include "CMsmlModifyVideoConference.h"
#include "CMsmlModifyStream.h"
#include "CMsmlEvent.h"
#include "CMsmlCollectDtmfs.h"
#include "CConfigOptions.h"
#include "CConferenceManager.h"
#include "CConference.h"
#include "CMsmlResponse.h"
#include "CHttpManager.h"
#include "CHttpRequest.h"
#include "CHttpDelete.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CCallflow::CCallflow(CTaskProcessorSptr a_taskProcessor, AResourceGroupSptr a_resourceGroup)
//
// Description: Initializing constructor - register for events from the 
// Resource Group
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//             AResourceGroupSptr a_resourceGroup
//
///////////////////////////////////////////////////////////////////////////////
CCallflow::CCallflow( CTaskProcessorSptr a_taskProcessor, AResourceGroupSptr a_resourceGroup) 
   : ACallflow( a_taskProcessor)
   , m_resourceGroup( a_resourceGroup)
{
   Name( a_resourceGroup->Name());

   ATaskSptr l_onDialogFailed( new CTask1<CMsmlResponseSptr>( boost::bind( &CCallflow::OnDialogFailed, this, _1),
                                                                           "CCallflow::OnDialogFailed"));
   m_resourceGroup->RegisterForNotification( this, l_onDialogFailed, RESOURCEGROUP_DIALOG_FAILED);

   ATaskSptr l_onDialogComplete( new CTask1<CMsmlResponseSptr>( boost::bind( &CCallflow::OnDialogComplete, this, _1),
                                                                             "CCallflow::OnDialogComplete"));
   m_resourceGroup->RegisterForNotification( this, l_onDialogComplete, RESOURCEGROUP_DIALOG_COMPLETE);

   ATaskSptr l_onDialogEvent( new CTask1<CMsmlEventSptr>( boost::bind(  &CCallflow::OnDialogEvent, this, _1),
                                                                        "CCallflow::OnDialogEvent"));
   m_resourceGroup->RegisterForNotification( this, l_onDialogEvent, RESOURCEGROUP_DIALOG_EVENT);

   ATaskSptr l_onMediaCommandFailed( new CTask1<CMsmlResponseSptr>( boost::bind( &CCallflow::OnDialogFailed, this, _1),
                                                                                 "CCallflow::OnDialogFailed"));
   m_resourceGroup->RegisterForNotification( this, l_onMediaCommandFailed, RESOURCEGROUP_MEDIA_COMMAND_FAILED);

   ATaskSptr l_onMediaCommandResponse( new CTask1<CMsmlResponseSptr>( boost::bind( &CCallflow::OnDialogComplete, this, _1),
                                                                                   "CCallflow::OnDialogComplete"));
   m_resourceGroup->RegisterForNotification( this, l_onMediaCommandResponse, RESOURCEGROUP_MEDIA_COMMAND_COMPLETE);

   VideoAvailable( m_resourceGroup->VideoAvailable());
}

///////////////////////////////////////////////////////////////////////////////
// Function: CCallflow::~CCallflow()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CCallflow::~CCallflow()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CCallflowSptr CCallflow::SharedPtr()
//
// Description: Obtain a shared pointer for this object
//
// Return: CCallflowSptr 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CCallflowSptr CCallflow::SharedPtr()
{
   return shared_from_this();
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CCallflow::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CCallflow::ClassName() 
{
   return "CCallflow";
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CCallflow::HasResourceGroup(AResourceGroupSptr a_resourceGroup)
//
// Description: Test if object has a Resource Group
//
// Return: bool 
//
// Parameters: AResourceGroupSptr a_resourceGroup 
//
///////////////////////////////////////////////////////////////////////////////
bool CCallflow::HasResourceGroup( AResourceGroupSptr a_resourceGroup)
{
   return a_resourceGroup == m_resourceGroup;
}

///////////////////////////////////////////////////////////////////////////////
// Function: AResourceGroupSptr CCallflow::ResourceGroup()
//
// Description: Access the Resource Group
//
// Return: AResourceGroupSptr 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
AResourceGroupSptr CCallflow::ResourceGroup()
{
   return m_resourceGroup;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimReset()
//
// Description: Reset the callflow by unregistering for events
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimReset()
{
   LogDebug("PrimReset");
   if ( !ConferenceId().empty())
   {
      PrimLeaveConference( ConferenceId());
   }
   m_resourceGroup->Unregister( this);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimDisconnect()
//
// Description: Disconnect the Resource Group calls
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimDisconnect()
{
   LogDebug("PrimDisconnect");
   m_resourceGroup->Disconnect();
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimOnDialogFailed( const CMsmlResponseSptr& a_responseData)
//
// Description: A dialog has failed, start the "Application Error" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters:  const CMsmlResponseSptr& a_responseData
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimOnDialogFailed( const CMsmlResponseSptr& a_responseData)
{
   LogDebug("PrimOnDialogFailed", a_responseData->ResponseCode());

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoAppError.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceAppError.moml");
   }
   StartDialog( l_script);
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimOnDialogEvent(const CMsmlEventSptr &a_event)
//
// Description: A dialog event has been received, get necessary data from the 
// event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const CMsmlEventSptr &a_event
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimOnDialogEvent( const CMsmlEventSptr& a_event)
{
   LogDebug("PrimOnDialogEvent");
   std::map<std::string,std::string>& l_parms = a_event->Parms();
   std::map<std::string,std::string>::iterator l_parm;
   for ( l_parm = l_parms.begin();
         l_parm != l_parms.end();
         ++l_parm)
   {
      LogDebug("PrimOnDialogEvent", l_parm->second);
   }

   if ( a_event->Name() == "done")
   {
      LastMenuSelection( a_event->MatchedDtmf());
   }
   if ( a_event->Name() == "DTMF#_PatternDetected")
   {
	   LogDebug("DTMF#_PatternDetected", a_event->LastDtmf());
	   LastMenuSelection( a_event->LastDtmf());
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimOnDialogComplete( const CMsmlResponseSptr& a_response)
//
// Description: A dialog has completed
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimOnDialogComplete( const CMsmlResponseSptr& a_response)
{
   LogDebug("PrimOnDialogComplete");
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimMainMenu()
//
// Description: Start the "Main Menu" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimMainMenu()
{
   LogDebug("PrimMainMenu");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoMainMenu.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceMainMenu.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailMenu()
//
// Description: Start the "Voice/Video Menu" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailMenu()
{
   LogDebug("PrimVMailMenu");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoMailMenu.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceMailMenu.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimAnnounceDisconnect()
//
// Description: Start the "Announce Disconnect" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimAnnounceDisconnect()
{
   LogDebug("PrimAnnounceDisconnect");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoGoodBye.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceGoodBye.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimFeatureUnavailable()
//
// Description: Start the "Feature Unavailable" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimFeatureUnavailable()
{
   LogDebug("PrimFeatureUnavailable");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoFeatureUnavailable.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceFeatureUnavailable.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimNotImplemented()
//
// Description: Start the "Feature Not Implemented" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimNotImplemented()
{
   LogDebug("PrimNotImplemented");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoNotImplemented.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceNotImplemented.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimInvalidMenuInput()
//
// Description: Start the "Missing, Unexpected or Invalid Menu Input" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimInvalidMenuInput()
{
   LogDebug("PrimInvalidMenuInput");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoInvalidMenuInput.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceInvalidMenuInput.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimGetMailbox()
//
// Description: Start the "Get Mailbox number" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimGetMailbox()
{
   LogDebug("PrimGetMailbox");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoGetMailbox.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceGetMailbox.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailRecord(const std::string &a_mailbox)
//
// Description: Start a Record dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailRecord( const std::string& a_mailbox)
{
   LogDebug("PrimVMailRecord");
   LastMenuSelection("");
   ADialogSptr l_dialog;
   if ( VideoActive())
   {
      l_dialog = ADialogSptr( new CMsmlDialogVideoMailRecord( ResourceGroup()->MsmlConnectionTag(),
                                                              a_mailbox));
   }
   else
   {
      l_dialog = ADialogSptr( new CMsmlDialogVoiceMailRecord( ResourceGroup()->MsmlConnectionTag(),
                                                              a_mailbox));
   }
   ResourceGroup()->StartDialog( l_dialog);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailRecordStart(const std::string &a_mailbox)
//
// Description: Start a "Start Record" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailRecordStart( const std::string& a_mailbox)
{
   LogDebug("PrimVMailRecordStart");
   LastMenuSelection("");
   ADialogSptr l_dialog;
   if ( VideoAvailable())
   {
      l_dialog = ADialogSptr( new CMsmlDialogVideoMailRecordStart( ResourceGroup()->MsmlConnectionTag(),
                                                                   a_mailbox));
   }
   else
   {
      l_dialog = ADialogSptr( new CMsmlDialogVoiceMailRecordStart( ResourceGroup()->MsmlConnectionTag(),
                                                                   a_mailbox));
   }
   ResourceGroup()->StartDialog( l_dialog);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailRecordOptions()
//
// Description: Start a "Recorded Message Oprions Menu" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailRecordOptions()
{
   LogDebug("PrimVMailRecordOptions");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoMailRecordOptions.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceMailRecordOptions.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailRecordSave()
//
// Description: Start the "Message Saved" dialog for a just recorded message
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailRecordSave(){
   LogDebug("PrimVMailRecordSave");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoMailMessageSaved.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceMailMessageSaved.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailRecordPlay(const std::string &a_mailbox)
//
// Description: Start a "Play" dialog for a just recorded message
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailRecordPlay( const std::string& a_mailbox){
   LogDebug("PrimVMailRecordPlay");
   LastMenuSelection("");
   ADialogSptr l_dialog;
   if ( VideoActive())
   {
      l_dialog = ADialogSptr( new CMsmlDialogVideoMailPlay( ResourceGroup()->MsmlConnectionTag(),
                                                              a_mailbox));
   }
   else
   {
      l_dialog = ADialogSptr( new CMsmlDialogVoiceMailPlay( ResourceGroup()->MsmlConnectionTag(),
                                                              a_mailbox));
   }
   ResourceGroup()->StartDialog( l_dialog);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailRecordCancel(const std::string &a_mailbox)
//
// Description: Cancel a record message operation
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailRecordCancel( const std::string& a_mailbox)
{
   LogDebug("PrimVMailRecordCancel");
   LastMenuSelection("");
   DeleteMessage( a_mailbox);
/*
   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoMailMessageDeleted.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceMailMessageDeleted.moml");
   }
   StartDialog( l_script);
*/
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimOnMessageDeleted( int a_result)
//
// Description: Cancel a record message operation
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimOnMessageDeleted( int a_result){
   LogDebug("PrimOnMessageDeleted");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoMailMessageDeleted.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceMailMessageDeleted.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailPlay(const std::string &a_mailbox)
//
// Description: Start a "Play Message" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailPlay( const std::string& a_mailbox)
{
   LogDebug("PrimVMailPlay");
   LastMenuSelection("");
   ADialogSptr l_dialog;
   if ( VideoActive())
   {
      l_dialog = ADialogSptr( new CMsmlDialogVideoMailPlay( ResourceGroup()->MsmlConnectionTag(),
                                                              a_mailbox));
   }
   else
   {
      l_dialog = ADialogSptr( new CMsmlDialogVoiceMailPlay( ResourceGroup()->MsmlConnectionTag(),
                                                              a_mailbox));
   }
   ResourceGroup()->StartDialog( l_dialog);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailPlayOptions()
//
// Description: Start a "Play Message Options Menu" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailPlayOptions()
{
   LogDebug("PrimVMailPlayOptions");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoMailPlayOptions.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceMailPlayOptions.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimVMailPlayDelete(const std::string &a_mailbox)
//
// Description: Delete a played message
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimVMailPlayDelete( const std::string& a_mailbox)
{
   LogDebug("PrimVMailPlayDelete");
   LastMenuSelection("");
   DeleteMessage( a_mailbox);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimInvalidMailbox()
//
// Description: Start an "Invalid Mailbox number" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimInvalidMailbox()
{
   LogDebug("PrimInvalidMailbox");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoInvalidMailbox.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceInvalidMailbox.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimEmptyMailbox()
//
// Description: Start an "Empty Mailbox" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimEmptyMailbox()
{
   LogDebug("PrimEmptyMailbox");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoEmptyMailbox.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceEmptyMailbox.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimConferenceMenu
//
// Description: Start the conference menu
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimConferenceMenu()
{
   LogDebug("PrimConferenceMenu");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoConferenceMenu.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceConferenceMenu.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimGetConferenceId
//
// Description: Start the "Enter a conference ID" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimGetConferenceId()
{
   LogDebug("PrimConferenceMenu");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoGetConferenceId.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceGetConferenceId.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimInvalidConferenceId()
//
// Description: Start the "Invalid conference ID" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimInvalidConferenceId()
{
   LogDebug("PrimInvalidConferenceId");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoInvalidConferenceId.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceInvalidConferenceId.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimConferenceIdAlreadyExists()
//
// Description: Start the "conference ID already exists" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimConferenceIdAlreadyExists()
{
   LogDebug("PrimConferenceIdAlreadyExists");
   LastMenuSelection("");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoConferenceExists.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceConferenceExists.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimConferenceIdDoesNotExist()
//
// Description: Start the "Conference Does not exist" dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimConferenceIdDoesNotExist()
{
   LogDebug("PrimConferenceIdDoesNotExist");

   std::string l_script;
   if ( VideoAvailable())
   {
      MakeScriptUri( l_script, "VideoConferenceDoesNotExist.moml");
   }
   else
   {
      MakeScriptUri( l_script, "VoiceConferenceDoesNotExist.moml");
   }
   StartDialog( l_script);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimCreateConference( const std::string& a_conferenceId);
//
// Description: Start the Create conference dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimCreateConference( const std::string& a_conferenceId)
{
   LogDebug("PrimCreateConference");
   ADialogSptr l_dialog;

   CConfigOptionsSptr l_config( CConfigOptions::Instance());

   if ( VideoAvailable())
   {
	   LogDebug("Calling MsmlCreateVideoConference");
	   l_dialog = ADialogSptr( new CMsmlCreateVideoConference(l_config->InitialVideoLayout(),l_config->RootSize()));
   }
   else
   {
	   LogDebug("Calling MsmlCreateConference");
      l_dialog = ADialogSptr( new CMsmlCreateConference());
   }
   ResourceGroup()->SendMediaCommand( l_dialog);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimOnCreateConference( const CMsmlResponseSptr& a_response)
//
// Description: Handle Create conference completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters:  const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimOnCreateConference( const CMsmlResponseSptr& a_response)
{
   LogDebug("PrimOnCreateConference");

   CConfigOptionsSptr l_config( CConfigOptions::Instance());

   CConferenceSptr l_conference( new CConference( ConferenceId(), a_response->ConferenceId()));
   if ( VideoAvailable())
   {
	   LogDebug("ConfigureVideo Layouts");
	   l_conference->ConfigureVideoLayouts(l_config->AllowedLayoutsCount(),l_config->AllowedLayouts(), l_config->InitialVideoLayout());
   }
   return CConferenceManager::Instance()->AddConference( l_conference);
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimModifyConference( const std::string& a_conferenceId, int a_action);
//
// Description: Start the Modify conference dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimModifyConference( const std::string& a_conferenceId, int a_action)
{
   LogDebug("PrimModifyConference");
   ADialogSptr l_dialog;

   CConfigOptionsSptr l_config( CConfigOptions::Instance());
   CConferenceSptr l_conference = CConferenceManager::Instance()->FindConference( ConferenceId());
   if ( !l_conference)
   {
      return -1;
   }

   int l_layout=l_conference->GetLayout();
   int* l_regionlist = l_conference->GetVisibleRegions();


   if (a_action == 1) //CycleLayout
   {
	  l_layout = l_conference->CycleLayout();
      l_conference->RefreshRegions();
   }
   else if (a_action == 2) //RotateParties
   {
	   l_conference->RotateParties();
   }

   LogDebug("Calling MsmlModifyVideoConference, Layout", AsString(l_layout));
   l_dialog = ADialogSptr( new CMsmlModifyVideoConference(l_conference->ConferenceId(),l_layout, l_regionlist, l_config->RootSize()));

   ResourceGroup()->SendMediaCommand(l_dialog);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimModifyStream( const std::string& a_conferenceId);
//
// Description: Start the Modify Stream dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimModifyStream( const std::string& a_conferenceId)
{
   LogDebug("PrimModifyStream");
   ADialogSptr l_dialog;

   CConfigOptionsSptr l_config( CConfigOptions::Instance());
   CConferenceSptr l_conference = CConferenceManager::Instance()->FindConference( ConferenceId());
   if ( !l_conference)
   {
      return -1;
   }
   
   //JM TODO: use DTMF here
   int l_layout = 1;

   LogDebug("Calling MsmlModifyStream");
   l_dialog = ADialogSptr( new CMsmlModifyStream(l_conference->ConferenceId(), ResourceGroup()->MsmlConnectionTag(), l_layout));

   ResourceGroup()->SendMediaCommand(l_dialog);
   return 0;
}


///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimOnModifyConference( const CMsmlResponseSptr& a_response)
//
// Description: Handle Modify Video conference completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters:  const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimOnModifyConference( const CMsmlResponseSptr& a_response)
{
   LogDebug("PrimOnModifyConference");
   CConferenceSptr l_conference = CConferenceManager::Instance()->FindConference( ConferenceId());
   if (l_conference)
   {
      //return l_conference->AddConferenceLeg( Name());
   }
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimOnModifyStream( const CMsmlResponseSptr& a_response)
//
// Description: Handle Modify Stream completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters:  const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimOnModifyStream( const CMsmlResponseSptr& a_response)
{
   LogDebug("PrimOnModifyStream");
   CConferenceSptr l_conference = CConferenceManager::Instance()->FindConference( ConferenceId());
   if (l_conference)
   {
      //return l_conference->AddConferenceLeg( Name());
   }
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimJoinConference( const std::string& a_conferenceId);
//
// Description: Start the Join conference dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimJoinConference( const std::string& a_conferenceId)
{
   LogDebug("PrimJoinConference");

   CConfigOptionsSptr l_config( CConfigOptions::Instance());
   CConferenceSptr l_conference = CConferenceManager::Instance()->FindConference( ConferenceId());
   if ( !l_conference)
   {
      return -1;
   }

   ADialogSptr l_dialog;

   l_conference->AddConferenceLeg( Name());
   if ( VideoAvailable() && VideoActive())
   {
     //JM Select region and limit to number of regions in initial layout
	   int l_region = l_conference->GetDisplayRegion(Name());
	   l_dialog = ADialogSptr( new CMsmlJoinVideoConference( l_conference->ConferenceId(), ResourceGroup()->MsmlConnectionTag(), l_region));
   }
   else
   {
      l_dialog = ADialogSptr( new CMsmlJoinConference( l_conference->ConferenceId() ,ResourceGroup()->MsmlConnectionTag()));
   }
   ResourceGroup()->SendMediaCommand( l_dialog);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimOnJoinConference( const CMsmlResponseSptr& a_response)
//
// Description: Handle Joinn conference completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters:  const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimOnJoinConference( const CMsmlResponseSptr& a_response)
{
   LogDebug("PrimOnJoinConference");
   CConferenceSptr l_conference = CConferenceManager::Instance()->FindConference( ConferenceId());
   if (l_conference)
   {
	   return 0;
   }
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimCollectDtmfs();
//
// Description: Start the CollectDtmfs dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimCollectDtmfs()
{
   LogDebug("PrimCollectDtmfs");
   ADialogSptr l_dialog;
   if ( VideoAvailable() && VideoActive())
   {
     l_dialog = ADialogSptr( new CMsmlCollectDtmfs(ResourceGroup()->MsmlConnectionTag()));
     ResourceGroup()->StartDialog( l_dialog);
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CCallflow::PrimLeaveConference( const std::string& a_conferenceId)
//
// Description: Start the Leave conference dialog
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
int CCallflow::PrimLeaveConference( const std::string& a_conferenceId)
{
   LogDebug("PrimLeaveConference");
   CConferenceSptr l_conference = CConferenceManager::Instance()->FindConference( a_conferenceId);
   if (l_conference)
   {
      return l_conference->RemoveConferenceLeg( Name());
   }
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflow::StartDialog( const std::string& a_script)
//
// Description: Start an MSML Dialog with a script
//
// Return: none
//
// Parameters: const std::string& a_script
//
///////////////////////////////////////////////////////////////////////////////
void CCallflow::StartDialog( const std::string& a_script)
{
   ADialogSptr l_dialog;
   l_dialog = ADialogSptr( new CMsmlDialog( ResourceGroup()->MsmlConnectionTag(), 
                                            a_script ));
   ResourceGroup()->StartDialog( l_dialog);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflow::DeleteMessage( const std::string& a_mailbox)
//
// Description: Delete a mailbox message
//
// Return: none
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflow::DeleteMessage( const std::string& a_mailbox)
{
   LogDebug( "DeleteMessage");
   std::string l_fileUri;
   MakeMailboxUri( l_fileUri, a_mailbox, VideoActive());

   if ( l_fileUri.find("http://") != std::string::npos)
   {
      ATaskSptr l_completionTask( new CTask1<int>( boost::bind( &CCallflow::OnMessageDeleted, this, _1),                                                            
                                                                "CCallflow::OnMessageDeleted"));
      AHttpRequestSptr l_httpRequest = AHttpRequestSptr( new CHttpDelete( l_fileUri, 
                                                                          l_completionTask, this));
      CHttpManager::Instance()->HttpRequest( l_httpRequest);
   }
   else if ( l_fileUri.find("file://") != std::string::npos)
   {
      MakeMediaFilePath( l_fileUri);
      unlink( l_fileUri.c_str());
      ATaskSptr l_completionTask( new CTask1<int>( boost::bind( &CCallflow::OnMessageDeleted, this, _1),
                                                                200,
                                                                "CCallflow::OnMessageDeleted"));
      QueueTask(l_completionTask);
   }
   else
   {
      LogDebug( "DeleteMessage", "unsupported URI type");
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflow::CheckMailbox(const std::string &a_mailbox, bool a_videoIsActive)
//
// Description: Check if the mailbox is empty
//
// Return: bool
//
// Parameters: const std::string &a_mailbox
//             bool a_videoIsActive
//
///////////////////////////////////////////////////////////////////////////////
void CCallflow::CheckMailbox( const std::string& a_mailbox, bool a_videoIsActive)
{
   LogDebug( "CheckMailbox", a_mailbox);
   std::string l_fileUri;
   MakeMailboxUri( l_fileUri, a_mailbox, VideoActive());

   if ( l_fileUri.find("http://") != std::string::npos)
   {
      LogDebug( "CheckMailbox", l_fileUri);
      ATaskSptr l_completionTask( new CTask1<int>( boost::bind( &CCallflow::OnCheckMailboxComplete, this, _1),                                                            
                                                                "CCallflow::OnCheckMailboxComplete"));
      AHttpRequestSptr l_httpRequest = AHttpRequestSptr( new CHttpRequest( l_fileUri, 
                                                                           l_completionTask, this));
      CHttpManager::Instance()->HttpRequest( l_httpRequest);
   }
   else if ( l_fileUri.find("file://") != std::string::npos)
   {
      MakeMediaFilePath( l_fileUri);
      LogDebug( "CheckMailbox", l_fileUri);
      int l_result(400);
      std::ifstream l_mailboxFile( l_fileUri.c_str());
      if ( l_mailboxFile)
      {
         l_result = 200;
         l_mailboxFile.close();
      }
      ATaskSptr l_completionTask( new CTask1<int>( boost::bind( &CCallflow::OnCheckMailboxComplete, this, _1),
                                                                l_result,
                                                                "CCallflow::OnCheckMailboxComplete"));
      QueueTask(l_completionTask);
   }
   else
   {
      LogDebug( "CheckMailbox", "unsupported URI type");
   }
}


