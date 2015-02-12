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
// File Name: CallflowStates.cpp
//
// Description: Implementation of the Callflow state classes
//
///////////////////////////////////////////////////////////////////////////////
#include "CallflowStates.h"
#include "ACallflow.h"
#include "CMsmlEvent.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::Start(ACallflow &a_callflow)
//
// Description: Start command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::Start( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "Start");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::Reset(ACallflow &a_callflow)
//
// Description: Reset command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::Reset( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "Reset");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::Disconnect(ACallflow &a_callflow)
//
// Description: Disconnect command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::Disconnect( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "Disconnect");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::OnDialogFailed(ACallflow &a_callflow, const CMsmlResponseSptr& a_responseData)
//
// Description: OnDialogFailed event is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//              const CMsmlResponseSptr& a_responseData
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::OnDialogFailed( ACallflow& a_callflow, const CMsmlResponseSptr& a_responseData)
{
   LogInvalidStateForEvent( a_callflow, "OnDialogFailed");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::OnDialogEvent(ACallflow &a_callflow, const CMsmlEventSptr &a_event)
//
// Description: OnDialogEvent event is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlEventSptr &a_event
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::OnDialogEvent( ACallflow& a_callflow, const CMsmlEventSptr& a_event)
{
   LogInvalidStateForEvent( a_callflow, "OnDialogEvent");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: OnDialogComplete event is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   LogInvalidStateForEvent( a_callflow, "OnDialogComplete");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::MainMenu(ACallflow &a_callflow)
//
// Description: MainMenu command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::MainMenu( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "MainMenu");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailMenu(ACallflow &a_callflow)
//
// Description: VMailMenu command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailMenu( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "VMailMenu");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailRecordGetMailbox(ACallflow &a_callflow)
//
// Description: VMailRecordGetMailbox command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailRecordGetMailbox( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "VMailRecordGetMailbox");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailRecord(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: VMailRecord command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailRecord( ACallflow& a_callflow, const std::string& a_mailbox)
{
   LogInvalidStateForCommand( a_callflow, "VMailRecord");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailRecordStart(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: VMailRecordStart command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailRecordStart( ACallflow& a_callflow, const std::string& a_mailbox)
{
   LogInvalidStateForCommand( a_callflow, "VMailRecordStart");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailRecordOptions(ACallflow &a_callflow)
//
// Description: VMailRecordOptions command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailRecordOptions( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "VMailRecordOptions");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailRecordSave(ACallflow &a_callflow)
//
// Description: VMailRecordSave command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailRecordSave( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "VMailRecordSave");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailRecordPlay(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: VMailRecordPlay command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailRecordPlay( ACallflow& a_callflow, const std::string& a_mailbox)
{
   LogInvalidStateForCommand( a_callflow, "VMailRecordPlay");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailRecordCancel(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: VMailRecordCancel command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailRecordCancel( ACallflow& a_callflow, const std::string& a_mailbox)
{
   LogInvalidStateForCommand( a_callflow, "VMailRecordCancel");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailPlayGetMailbox(ACallflow &a_callflow)
//
// Description: VMailPlayGetMailbox command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailPlayGetMailbox( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "VMailPlayGetMailbox");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailPlayMailboxEmpty(ACallflow &a_callflow)
//
// Description: VMailPlayMailboxEmpty command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailPlayMailboxEmpty( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "VMailPlayMailboxEmpty");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailPlay(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: VMailPlay command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailPlay( ACallflow& a_callflow, const std::string& a_mailbox)
{
   LogInvalidStateForCommand( a_callflow, "VMailPlay");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailPlayOptions(ACallflow &a_callflow)
//
// Description: VMailPlayOptions command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailPlayOptions( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "VMailPlayOptions");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::VMailPlayDelete(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: VMailPlayDelete command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::VMailPlayDelete( ACallflow& a_callflow, const std::string& a_mailbox)
{
   LogInvalidStateForCommand( a_callflow, "VMailPlayDelete");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::AnnounceDisconnect(ACallflow &a_callflow)
//
// Description: AnnounceDisconnect command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::AnnounceDisconnect( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "AnnounceDisconnect");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::FeatureUnavailable(ACallflow &a_callflow)
//
// Description: FeatureUnavailable command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::FeatureUnavailable( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "FeatureUnavailable");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::NotImplemented(ACallflow &a_callflow)
//
// Description: NotImplemented command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::NotImplemented( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "NotImplemented");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::InvalidMenuInput(ACallflow &a_callflow)
//
// Description: InvalidMenuInput command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::InvalidMenuInput( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "InvalidMenuInput");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::InvalidMailbox(ACallflow &a_callflow)
//
// Description: InvalidMailbox command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::InvalidMailbox( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "InvalidMailbox");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::EmptyMailbox(ACallflow &a_callflow)
//
// Description: EmptyMailbox command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::EmptyMailbox( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "EmptyMailbox");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::ConferenceMenu(ACallflow &a_callflow)
//
// Description: ConferenceMenu command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::ConferenceMenu( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "ConferenceMenu");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::ConferenceCreateGetConferenceId(ACallflow &a_callflow)
//
// Description: ConferenceCreateGetConferenceId command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::ConferenceCreateGetConferenceId( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "ConferenceCreateGetConferenceId");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::ConferenceJoinGetConferenceId(ACallflow &a_callflow)
//
// Description: ConferenceJoinGetConferenceId command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::ConferenceJoinGetConferenceId( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "ConferenceJoinGetConferenceId");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::InvalidConferenceId(ACallflow &a_callflow)
//
// Description: InvalidConferenceId command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::InvalidConferenceId( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "InvalidConferenceId");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::ConferenceIdAlreadyExists(ACallflow &a_callflow)
//
// Description: ConferenceIdAlreadyExists command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::ConferenceIdAlreadyExists( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "ConferenceIdAlreadyExists");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::ConferenceIdDoesNotExist(ACallflow &a_callflow)
//
// Description: ConferenceIdDoesNotExist command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::ConferenceIdDoesNotExist( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "ConferenceIdDoesNotExist");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::CreateConference(ACallflow &a_callflow, const std::string& a_conferenceId)
//
// Description: CreateConference command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::CreateConference( ACallflow& a_callflow, const std::string& a_conferenceId)
{
   LogInvalidStateForCommand( a_callflow, "CreateConference");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::JoinConference(ACallflow &a_callflow, const std::string& a_conferenceId)
//
// Description: JoinConference command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::JoinConference( ACallflow& a_callflow, const std::string& a_conferenceId)
{
   LogInvalidStateForCommand( a_callflow, "JoinConference");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::ModifyConference(ACallflow &a_callflow, const std::string& a_conferenceId, int a_action)
//
// Description: ModifyConference command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::ModifyConference( ACallflow& a_callflow, const std::string& a_conferenceId, int a_action)
{
   LogInvalidStateForCommand( a_callflow, "ModifyConference");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::ModifyStream(ACallflow &a_callflow, const std::string& a_conferenceId)
//
// Description: ModifyStream command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::ModifyStream( ACallflow& a_callflow, const std::string& a_conferenceId)
{
   LogInvalidStateForCommand( a_callflow, "ModifyStream");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::CollectDtmfs(ACallflow &a_callflow)
//
// Description: CollectDtmfs command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::CollectDtmfs( ACallflow& a_callflow)
{
   LogInvalidStateForCommand( a_callflow, "CollectDtmfs");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::LeaveConference( ACallflow& a_callflow, const std::string& a_conferenceId)
//
// Description: LeaveConference command is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::LeaveConference( ACallflow& a_callflow, const std::string& a_conferenceId)
{
   LogInvalidStateForCommand( a_callflow, "LeaveConference");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::OnCheckMailBoxComplete( ACallflow& a_callflow)
//
// Description: OnCheckMailBoxComplete event is invalid in this state
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::OnCheckMailboxComplete( ACallflow& a_callflow, int a_result)
{
   LogInvalidStateForEvent( a_callflow, "OnCheckMailboxComplete");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::OnMessageDeleted( ACallflow& a_callflow, int a_result)
//
// Description: OnMessageDeleted event is invalid in this state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::OnMessageDeleted( ACallflow& a_callflow, int a_result)
{
   LogInvalidStateForEvent( a_callflow, "MessageDeleted");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::LogInvalidStateForCommand(ACallflow &a_callflow, const char *a_command)
//
// Description: Log an error for a command issued in an invalid state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const char *a_command
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::LogInvalidStateForCommand( ACallflow& a_callflow, const char* a_command)
{
   a_callflow.LogError( a_command, "Invalid state for command");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowState::LogInvalidStateForEvent(ACallflow &a_callflow, const char *a_event)
//
// Description: Log an error for an event received in an invalid state
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const char *a_event
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowState::LogInvalidStateForEvent( ACallflow& a_callflow, const char* a_event)
{
   a_callflow.LogError( a_event, "Invalid state for event");
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowInitializedState::Reset(ACallflow &a_callflow)
//
// Description: Reset the Callflow
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowInitializedState::Reset( ACallflow& a_callflow)
{
   a_callflow.PrimReset();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowInitializedState::Disconnect(ACallflow &a_callflow)
//
// Description: Disconnect the Resource Group calls
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowInitializedState::Disconnect( ACallflow& a_callflow)
{
   a_callflow.PrimDisconnect();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowIdleState::Start(ACallflow &a_callflow)
//
// Description: Start the Callflow
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowIdleState::Start( ACallflow& a_callflow)
{
   a_callflow.SetStateToMainMenu();
   a_callflow.PrimMainMenu();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowDialogState::OnDialogFailed(ACallflow &a_callflow, const CMsmlResponseSptr& a_responseData)
//
// Description: Handle a DialogFailed event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_responseData
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowDialogState::OnDialogFailed( ACallflow& a_callflow, const CMsmlResponseSptr& a_responseData)
{
   a_callflow.SetStateToFailed();
   a_callflow.PrimOnDialogFailed( a_responseData);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowDialogState::OnDialogEvent(ACallflow &a_callflow, const CMsmlEventSptr &a_event)
//
// Description: Handle a Dialog Event event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlEventSptr &a_event
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowDialogState::OnDialogEvent( ACallflow& a_callflow, const CMsmlEventSptr& a_event)
{
   a_callflow.PrimOnDialogEvent( a_event);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowFailedState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowFailedState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   a_callflow.PrimOnDialogComplete( a_response);
   a_callflow.Disconnect();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowAnnounceDisconnectState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowAnnounceDisconnectState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   a_callflow.PrimOnDialogComplete( a_response);
   a_callflow.Disconnect();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowFeatureUnavailableState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowFeatureUnavailableState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.MainMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowNotImplementedState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowNotImplementedState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.MainMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowMainMenuAvailableState::MainMenu(ACallflow &a_callflow)
//
// Description: Start the MainMenu dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowMainMenuAvailableState::MainMenu( ACallflow& a_callflow)
{
   a_callflow.SetStateToMainMenu();
   a_callflow.PrimMainMenu();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowConferenceMenuAvailableState::ConferenceMenu( ACallflow& a_callflow);
//
// Description: Start the ConferenceMenu dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowConferenceMenuAvailableState::ConferenceMenu( ACallflow& a_callflow)
{
   a_callflow.SetStateToConferenceMenu();
   a_callflow.PrimConferenceMenu();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflowVMailMenuAvailableState::VMailMenu(ACallflow &a_callflow)
//
// Description: Start the Voice/Video Mail menu
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void ACallflowVMailMenuAvailableState::VMailMenu( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailMenu();
   a_callflow.PrimVMailMenu();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowMainMenuState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowMainMenuState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      if ( a_callflow.LastMenuSelection() == "1")    //Voice Mail
      {
         a_callflow.VideoActive( false);
         a_callflow.VMailMenu();
      }
      else if ( a_callflow.LastMenuSelection() == "2") //Video Mail
      {
         if ( a_callflow.VideoAvailable())
         {
            a_callflow.VideoActive( true);
            a_callflow.VMailMenu();
         }
         else
         {
            a_callflow.FeatureUnavailable();
         }
      }
      else if ( a_callflow.LastMenuSelection() == "3") //Audio Conferencing
      {
         a_callflow.VideoActive(false);
         a_callflow.ConferenceMenu();
      }
      else if ( a_callflow.LastMenuSelection() == "4") //Multimedia Conferencing
      {
         a_callflow.VideoActive(true);
         if ( a_callflow.VideoAvailable())
         {
            a_callflow.VideoActive( true);
            a_callflow.ConferenceMenu();
         }
         else
         {
            a_callflow.FeatureUnavailable();
         }
      }
      else if ( a_callflow.LastMenuSelection() == "*")
      {
         a_callflow.AnnounceDisconnect();
      }
      else
      {
         a_callflow.InvalidMenuInput();
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowMainMenuState::VMailMenu(ACallflow &a_callflow)
//
// Description: Start the voice/video mail menu dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowMainMenuState::VMailMenu( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailMenu();
   a_callflow.PrimVMailMenu();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowMainMenuState::ConferenceMenu(ACallflow &a_callflow)
//
// Description: Start the converence menu dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowMainMenuState::ConferenceMenu( ACallflow& a_callflow)
{
   a_callflow.SetStateToConferenceMenu();
   a_callflow.PrimConferenceMenu();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowMainMenuState::AnnounceDisconnect(ACallflow &a_callflow)
//
// Description: Start the AnnounceDisconnect dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowMainMenuState::AnnounceDisconnect( ACallflow& a_callflow)
{
   a_callflow.SetStateToAnnounceDisconnect();
   a_callflow.PrimAnnounceDisconnect();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowMainMenuState::FeatureUnavailable(ACallflow &a_callflow)
//
// Description: Start the FeatureUnavailable dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowMainMenuState::FeatureUnavailable( ACallflow& a_callflow)
{
   a_callflow.SetStateToFeatureUnavailable();
   a_callflow.PrimFeatureUnavailable();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowMainMenuState::NotImplemented(ACallflow &a_callflow)
//
// Description: Start the NotImplemented dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowMainMenuState::NotImplemented( ACallflow& a_callflow)
{
   a_callflow.SetStateToNotImplemented();
   a_callflow.PrimNotImplemented();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowMainMenuState::InvalidMenuInput(ACallflow &a_callflow)
//
// Description: Start the InvalidMenuInput dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowMainMenuState::InvalidMenuInput( ACallflow& a_callflow)
{
   a_callflow.SetStateToMainMenuInvalidInput();
   a_callflow.PrimInvalidMenuInput();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowMainMenuInvalidInputState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowMainMenuInvalidInputState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.MainMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailMenuState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailMenuState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      if ( a_callflow.LastMenuSelection() == "1")
      {
         a_callflow.VMailRecordGetMailbox();
      }
      else if ( a_callflow.LastMenuSelection() == "2")
      {
         a_callflow.VMailPlayGetMailbox();
      }
      else if ( a_callflow.LastMenuSelection() == "*")
      {
         a_callflow.MainMenu();
      }
      else
      {
         a_callflow.InvalidMenuInput();
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailMenuState::VMailRecordGetMailbox(ACallflow &a_callflow)
//
// Description: Start the GetMailbox dialog for message record
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailMenuState::VMailRecordGetMailbox( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailRecordGetMailbox();
   a_callflow.PrimGetMailbox();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailMenuState::VMailPlayGetMailbox(ACallflow &a_callflow)
//
// Description: Start the GetMailbox dialog for message play
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailMenuState::VMailPlayGetMailbox( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailPlayGetMailbox();
   a_callflow.PrimGetMailbox();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailMenuState::InvalidMenuInput(ACallflow &a_callflow)
//
// Description: Start the InvalidMenuInput dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailMenuState::InvalidMenuInput( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailMenuInvalidInput();
   a_callflow.PrimInvalidMenuInput();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailMenuInvalidInputState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailMenuInvalidInputState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.VMailMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordGetMailboxState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordGetMailboxState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.LastMenuSelectionIncludesAsterisk())
   {
      a_callflow.VMailMenu();
   }
   else if ( a_callflow.IsValidMailbox( a_callflow.LastMenuSelection()))
   {
      a_callflow.VMailRecordStart( a_callflow.LastMenuSelection());
   }
   else
   {
      a_callflow.InvalidMailbox();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordGetMailboxState::VMailRecordStart(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Play the "Start Message Record" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordGetMailboxState::VMailRecordStart( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.Mailbox( a_mailbox);
   a_callflow.SetStateToVMailRecordStart();
   a_callflow.PrimVMailRecordStart( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordGetMailboxState::InvalidMailbox(ACallflow &a_callflow)
//
// Description: Start the InvalidMailbox dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordGetMailboxState::InvalidMailbox( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailRecordInvalidMailbox();
   a_callflow.PrimInvalidMailbox();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordInvalidMailboxState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordInvalidMailboxState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   a_callflow.VMailRecordGetMailbox();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordInvalidMailboxState::VMailRecordGetMailbox(ACallflow &a_callflow)
//
// Description: Start the GetMailbox dialog for message record
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordInvalidMailboxState::VMailRecordGetMailbox( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailRecordGetMailbox();
   a_callflow.PrimGetMailbox();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordStartState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordStartState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.LastMenuSelection() == "2")
   {
      a_callflow.VMailRecord( a_callflow.Mailbox());
   }
   else if ( a_callflow.LastMenuSelection() == "*")
   {
      a_callflow.VMailMenu();
   }
   else
   {
      a_callflow.InvalidMenuInput();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordStartState::VMailRecord(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Start the "message record" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordStartState::VMailRecord( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.SetStateToVMailRecord();
   a_callflow.PrimVMailRecord( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordStartState::InvalidMenuInput(ACallflow &a_callflow)
//
// Description: Start the InvalidMenuInput dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordStartState::InvalidMenuInput( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailRecordStartInvalidInput();
   a_callflow.PrimInvalidMenuInput();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordStartInvalidInputState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordStartInvalidInputState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   a_callflow.VMailRecordStart( a_callflow.Mailbox());
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordStartInvalidInputState::VMailRecordStart(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Start the "start message record" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordStartInvalidInputState::VMailRecordStart( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.SetStateToVMailRecordStart();
   a_callflow.PrimVMailRecordStart( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.LastMenuSelection() == "*")
   {
      a_callflow.VMailRecordCancel( a_callflow.Mailbox());
   }
   else
   {
      a_callflow.VMailRecordOptions();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordState::VMailRecordOptions(ACallflow &a_callflow)
//
// Description: Start the "message record options" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordState::VMailRecordOptions( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailRecordOptions();
   a_callflow.PrimVMailRecordOptions();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordState::VMailRecordCancel(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Start the "cancel message record" process
//                1. delete the message
//                2. Play the "message deleted" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordState::VMailRecordCancel( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.SetStateToVMailRecordCancel();
   a_callflow.PrimVMailRecordCancel( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordOptionsState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordOptionsState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.LastMenuSelection() == "2")
   {
      a_callflow.VMailRecordStart( a_callflow.Mailbox());
   }
   else if ( a_callflow.LastMenuSelection() == "3")
   {
      a_callflow.VMailRecordSave();
   }
   else if ( a_callflow.LastMenuSelection() == "4")
   {
      a_callflow.VMailRecordPlay( a_callflow.Mailbox());
   }
   else if ( a_callflow.LastMenuSelection() == "*")
   {
      a_callflow.VMailRecordCancel( a_callflow.Mailbox());
   }
   else
   {
      a_callflow.InvalidMenuInput();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordOptionsState::VMailRecordStart(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Start the " start message record" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordOptionsState::VMailRecordStart( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.SetStateToVMailRecordStart();
   a_callflow.PrimVMailRecordStart( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordOptionsState::VMailRecordSave(ACallflow &a_callflow)
//
// Description: Start the "save recorded message" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordOptionsState::VMailRecordSave( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailRecordSave();
   a_callflow.PrimVMailRecordSave();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordOptionsState::VMailRecordPlay(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Start the "play recorded message" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordOptionsState::VMailRecordPlay( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.SetStateToVMailRecordPlay();
   a_callflow.PrimVMailRecordPlay( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordOptionsState::VMailRecordCancel(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Start the "cancel record" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordOptionsState::VMailRecordCancel( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.SetStateToVMailRecordCancel();
   a_callflow.PrimVMailRecordCancel( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordOptionsState::InvalidMenuInput(ACallflow &a_callflow)
//
// Description: Start the InvcalidMenuInput dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordOptionsState::InvalidMenuInput( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailRecordOptionsInvalidInput();
   a_callflow.PrimInvalidMenuInput();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordOptionsInvalidInputState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordOptionsInvalidInputState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.VMailRecordOptions();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordOptionsInvalidInputState::VMailRecordOptions(ACallflow &a_callflow)
//
// Description: Start the "recorded message options" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordOptionsInvalidInputState::VMailRecordOptions( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailRecordOptions();
   a_callflow.PrimVMailRecordOptions();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordSaveState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordSaveState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.VMailMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordPlayState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordPlayState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.VMailRecordOptions();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordPlayState::VMailRecordOptions(ACallflow &a_callflow)
//
// Description: Start the "recorded mesasage options" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordPlayState::VMailRecordOptions( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailRecordOptions();
   a_callflow.PrimVMailRecordOptions();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordCancelState::OnMessageDeleted(ACallflow &a_callflow, int a_result)
//
// Description: Start the "cancel message record" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordCancelState::OnMessageDeleted( ACallflow& a_callflow, int a_result)
{
   a_callflow.PrimOnMessageDeleted( a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailRecordCancelState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailRecordCancelState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.VMailMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayGetMailboxState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayGetMailboxState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.LastMenuSelectionIncludesAsterisk())
   {
      a_callflow.VMailMenu();
   }
   else if ( ! a_callflow.IsValidMailbox( a_callflow.LastMenuSelection()))
   {
      a_callflow.InvalidMailbox();
   }
   else
   {
      a_callflow.CheckMailbox( a_callflow.LastMenuSelection(), a_callflow.VideoActive());
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayGetMailboxState::OnCheckMailboxComplete( ACallflow& a_callflow, int a_result);
//
// Description: Handle the result of checking the mailbox for a message
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayGetMailboxState::OnCheckMailboxComplete( ACallflow& a_callflow, int a_result)
{
   if ( a_result == 200)
   {
      a_callflow.VMailPlay( a_callflow.LastMenuSelection());
   }
   else
   {
      a_callflow.EmptyMailbox();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayGetMailboxState::VMailPlay(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Start the "play a mailbox message" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayGetMailboxState::VMailPlay( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.SetStateToVMailPlay();
   a_callflow.Mailbox( a_mailbox);
   a_callflow.PrimVMailPlay( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayGetMailboxState::InvalidMailbox(ACallflow &a_callflow)
//
// Description: Start the InvalidMenuInput dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayGetMailboxState::InvalidMailbox( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailPlayInvalidMailbox();
   a_callflow.PrimInvalidMailbox();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayGetMailboxState::EmptyMailbox(ACallflow &a_callflow)
//
// Description: Start the "mailbox is empty" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayGetMailboxState::EmptyMailbox( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailPlayMailboxEmpty();
   a_callflow.PrimEmptyMailbox();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   a_callflow.VMailPlayOptions();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayState::VMailPlayOptions(ACallflow &a_callflow)
//
// Description: Start the "played message options" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayState::VMailPlayOptions( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailPlayOptions();
   a_callflow.PrimVMailPlayOptions();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayMailboxEmptyState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayMailboxEmptyState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   a_callflow.VMailMenu();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayInvalidMailboxState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayInvalidMailboxState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   a_callflow.VMailPlayGetMailbox();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayInvalidMailboxState::VMailPlayGetMailbox(ACallflow &a_callflow)
//
// Description: Start the "GetMailbox for play" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayInvalidMailboxState::VMailPlayGetMailbox( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailPlayGetMailbox();
   a_callflow.PrimGetMailbox();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayOptionsState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayOptionsState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.LastMenuSelection() == "1")
   {
      a_callflow.VMailPlay( a_callflow.Mailbox());
   }
   else if ( a_callflow.LastMenuSelection() == "2")
   {
      a_callflow.VMailPlayDelete( a_callflow.Mailbox());
   }
   else if ( a_callflow.LastMenuSelection() == "*")
   {
      a_callflow.VMailMenu();
   }
   else
   {
      a_callflow.InvalidMenuInput();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayOptionsState::InvalidMenuInput(ACallflow &a_callflow)
//
// Description: Start the InvalidMenuInput dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayOptionsState::InvalidMenuInput( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailPlayOptionsInvalidInput();
   a_callflow.PrimInvalidMenuInput();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayOptionsInvalidInputState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayOptionsInvalidInputState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.VMailPlayOptions();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayOptionsInvalidInputState::VMailPlayOptions(ACallflow &a_callflow)
//
// Description: Start the "played message options" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayOptionsInvalidInputState::VMailPlayOptions( ACallflow& a_callflow)
{
   a_callflow.SetStateToVMailPlayOptions();
   a_callflow.PrimVMailPlayOptions();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayOptionsState::VMailPlay(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Start the "play mailbox message" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayOptionsState::VMailPlay( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.SetStateToVMailPlay();
   a_callflow.PrimVMailPlay( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayOptionsState::VMailPlayDelete(ACallflow &a_callflow, const std::string &a_mailbox)
//
// Description: Start the "delete played message" dialog
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayOptionsState::VMailPlayDelete( ACallflow& a_callflow, const std::string& a_mailbox)
{
   a_callflow.SetStateToVMailPlayDelete();
   a_callflow.PrimVMailPlayDelete( a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayDeleteState::OnMessageDeleted(ACallflow &a_callflow, int a_result)
//
// Description: Handle the message deleted event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             int a_result
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayDeleteState::OnMessageDeleted( ACallflow& a_callflow, int a_result)
{
   a_callflow.PrimOnMessageDeleted( a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowVMailPlayDeleteState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowVMailPlayDeleteState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   a_callflow.VMailMenu();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceMenuState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceMenuState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      if ( a_callflow.LastMenuSelection() == "1")
      {
         a_callflow.ConferenceCreateGetConferenceId();
      }
      else if ( a_callflow.LastMenuSelection() == "2")
      {
         a_callflow.ConferenceJoinGetConferenceId();      
      }
      else if ( a_callflow.LastMenuSelection() == "*")
      {
         a_callflow.MainMenu();
      }
      else
      {
         a_callflow.InvalidMenuInput();
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceMenuState::ConferenceCreateGetConferenceId(ACallflow &a_callflow)
//
// Description: Start a dialog to get the Conference ID for creating a conference
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceMenuState::ConferenceCreateGetConferenceId( ACallflow& a_callflow)
{
   a_callflow.SetStateToConferenceCreateGetId();
   a_callflow.PrimGetConferenceId();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceMenuState::ConferenceJoinGetConferenceId(ACallflow &a_callflow)
//
// Description: Start a dialogi to get the conference ID for joining a conference
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceMenuState::ConferenceJoinGetConferenceId( ACallflow& a_callflow)
{
   a_callflow.SetStateToConferenceJoinGetId();
   a_callflow.PrimGetConferenceId();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceMenuState::InvalidMenuInput(ACallflow &a_callflow)
//
// Description: Start an invalid menu input dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceMenuState::InvalidMenuInput( ACallflow& a_callflow)
{
   a_callflow.SetStateToConferenceMenuInvalidInput();
   a_callflow.PrimInvalidMenuInput();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceMenuInvalidInputState::OnDialogComplete(ACallflow &a_callflow,const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for an invalid menu input dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow
//            const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceMenuInvalidInputState::OnDialogComplete( ACallflow& a_callflow,const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.ConferenceMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceCreateGetIdState::OnDialogComplete(ACallflow &a_callflow,const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for the get conference ID dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//            const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceCreateGetIdState::OnDialogComplete( ACallflow& a_callflow,const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.LastMenuSelectionIncludesAsterisk())
   {
      a_callflow.ConferenceMenu();
   }
   else if ( ! a_callflow.IsValidConferenceId( a_callflow.LastMenuSelection()))
   {
      a_callflow.InvalidConferenceId();
   }
   else if ( a_callflow.ConferenceIdExists( a_callflow.LastMenuSelection()))
   {
      a_callflow.ConferenceIdAlreadyExists();
   }
   else
   {
      a_callflow.CreateConference( a_callflow.LastMenuSelection());
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceCreateGetIdState::CreateConference(ACallflow &a_callflow, const std::string &a_conferenceId)
//
// Description: Start a create conference dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceCreateGetIdState::CreateConference( ACallflow& a_callflow, const std::string& a_conferenceId)
{
   a_callflow.ConferenceId( a_conferenceId);
   a_callflow.SetStateToConferenceCreating();
   a_callflow.PrimCreateConference( a_conferenceId);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceCreateGetIdState::InvalidConferenceId(ACallflow &a_callflow)
//
// Description: Start an invalid conference ID dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceCreateGetIdState::InvalidConferenceId( ACallflow& a_callflow)
{
   a_callflow.SetStateToConferenceCreateInvalidId();
   a_callflow.PrimInvalidConferenceId();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceCreateGetIdState::ConferenceIdExists(ACallflow &a_callflow)
//
// Description: Start a conference ID exists dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceCreateGetIdState::ConferenceIdAlreadyExists( ACallflow& a_callflow)
{
   a_callflow.SetStateToConferenceCreateIdExists();
   a_callflow.PrimConferenceIdAlreadyExists();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceCreateInvalidIdState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for the invalid conference ID dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceCreateInvalidIdState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.ConferenceMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceCreateIdExistsState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for the create conference ID already exists dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceCreateIdExistsState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.ConferenceMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceCreatingState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for the create conference dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceCreatingState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnCreateConference( a_response) == 0)
   {
      a_callflow.JoinConference( a_callflow.ConferenceId());
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceCreatingState::JoinConference(ACallflow &a_callflow, const std::string &a_conferenceId)
//
// Description: Start a join conference dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceCreatingState::JoinConference( ACallflow& a_callflow, const std::string& a_conferenceId)
{
   a_callflow.SetStateToConferenceJoining();
   a_callflow.PrimJoinConference( a_conferenceId);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceJoinGetIdState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for the get conference ID dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceJoinGetIdState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.LastMenuSelectionIncludesAsterisk())
   {
      a_callflow.ConferenceMenu();
   }
   else if ( ! a_callflow.IsValidConferenceId( a_callflow.LastMenuSelection()))
   {
      a_callflow.InvalidConferenceId();
   }
   else if ( !a_callflow.ConferenceIdExists( a_callflow.LastMenuSelection()) )
   {
      a_callflow.ConferenceIdDoesNotExist();
   }
   else
   {
      a_callflow.JoinConference( a_callflow.LastMenuSelection());
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceJoinGetIdState::JoinConference(ACallflow &a_callflow, const std::string &a_conferenceId)
//
// Description: Start a join conference dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceJoinGetIdState::JoinConference( ACallflow& a_callflow, const std::string& a_conferenceId)
{
   a_callflow.ConferenceId( a_conferenceId);
   a_callflow.SetStateToConferenceJoining();
   a_callflow.PrimJoinConference( a_conferenceId);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceJoinGetIdState::InvalidConferenceId(ACallflow &a_callflow)
//
// Description: Start a get conference ID dialog for joining a conference
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceJoinGetIdState::InvalidConferenceId( ACallflow& a_callflow)
{
   a_callflow.SetStateToConferenceJoinInvalidId();
   a_callflow.PrimInvalidConferenceId();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceJoinGetIdState::ConferenceIdDoesNotExist(ACallflow &a_callflow)
//
// Description: Start a conference ID doesn't exist dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceJoinGetIdState::ConferenceIdDoesNotExist( ACallflow& a_callflow)
{
   a_callflow.SetStateToConferenceJoinIdDoesNotExist();
   a_callflow.PrimConferenceIdDoesNotExist();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceJoinInvalidIdState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for the invalid conference ID dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceJoinInvalidIdState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.ConferenceMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceJoinIdDoesNotExistState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for the conference doesn't exist dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceJoinIdDoesNotExistState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnDialogComplete( a_response) == 0)
   {
      a_callflow.ConferenceMenu();
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceJoiningState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for the join conference dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceJoiningState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   if ( a_callflow.PrimOnJoinConference( a_response) == 0)
   {
      a_callflow.SetStateToConferenceActive();
      a_callflow.CollectDtmfs();
   }
   else
   {
      // TODO handle error condition
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceActiveState::CollectDtmfs(ACallflow &a_callflow)
//
// Description: Start a CollectDtmf dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceActiveState::CollectDtmfs( ACallflow& a_callflow)
{
   a_callflow.PrimCollectDtmfs();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceActiveState::ModifyConference(ACallflow &a_callflow, const std::string &a_conferenceId)
//
// Description: Start a Modify conference dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceActiveState::ModifyConference( ACallflow& a_callflow, const std::string& a_conferenceId, int a_action)
{
   a_callflow.PrimModifyConference(a_conferenceId, a_action);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceActiveState::ModifyStream(ACallflow &a_callflow, const std::string &a_conferenceId)
//
// Description: Start a Modify Stream dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceActiveState::ModifyStream( ACallflow& a_callflow, const std::string& a_conferenceId)
{
   a_callflow.PrimModifyStream(a_conferenceId);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceActiveState::OnDialogEvent( ACallflow& a_callflow, const CMsmlEventSptr& a_event)
//
// Description: Handle a Dialog event
//
// Return: void
//
// Parameters: ACallflow &a_callflow
//             , const CMsmlEventSptr& a_event
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceActiveState::OnDialogEvent( ACallflow& a_callflow, const CMsmlEventSptr& a_event)
{
   if ( a_callflow.PrimOnDialogEvent(a_event) == 0)
   {
      if ( a_callflow.LastMenuSelection() == "*")
      {
         //Modify Conference to dtmf selection
         a_callflow.LogDebug("Received '*', CycleLayout", a_callflow.ConferenceId());
         a_callflow.CycleLayouts(a_callflow.ConferenceId());
      } 
	  else if ( a_callflow.LastMenuSelection() == "#")
      {
         //Rotate Conference Layout dtmf selection
         a_callflow.LogDebug("Received '#', RotateParties", a_callflow.ConferenceId());
         a_callflow.RotateParties(a_callflow.ConferenceId());
      }
   }
   
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceActiveState::OnDialogComplete(ACallflow &a_callflow, const CMsmlResponseSptr& a_response)
//
// Description: Handle a DialogComplete event for the join conference dialog
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//             const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceActiveState::OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response)
{
   a_callflow.PrimOnDialogComplete( a_response);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CCallflowConferenceActiveState::Disconnect( ACallflow& a_callflow)
//
// Description: Handle a disconnect event
//
// Return: void 
//
// Parameters: ACallflow &a_callflow 
//
///////////////////////////////////////////////////////////////////////////////
void CCallflowConferenceActiveState::Disconnect( ACallflow& a_callflow)
{
   a_callflow.PrimLeaveConference( a_callflow.ConferenceId());
   ACallflowInitializedState::Disconnect( a_callflow);
}

