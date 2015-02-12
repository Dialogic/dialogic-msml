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
// File Name: CallflowStates.h
//
// Description: Callflow state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CallflowStates_h
#define CallflowStates_h

#include "TypeDefs.h"

#include <string>

class ACallflow;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ACallflowState
//
// Description: The abstract Callflow State class and all concrete subclasses 
// comprise a State Pattern implementation of the Callflow state machine.  
//
// The abstract Callflow state declares all functions supported by the state 
// machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class ACallflowState
{
public:
   virtual const char* StateDesc() = 0;
   virtual void Start( ACallflow& a_callflow);
   virtual void Reset( ACallflow& a_callflow);
   virtual void Disconnect( ACallflow& a_callflow);
   virtual void OnDialogFailed( ACallflow& a_callflow, const CMsmlResponseSptr& a_responseData);
   virtual void OnDialogEvent( ACallflow& a_callflow, const CMsmlEventSptr& a_event);
   virtual void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);

   virtual void MainMenu( ACallflow& a_callflow);
   virtual void VMailMenu( ACallflow& a_callflow);

   virtual void VMailRecordGetMailbox( ACallflow& a_callflow);
   virtual void VMailRecordStart( ACallflow& a_callflow, const std::string& a_mailbox);
   virtual void VMailRecord( ACallflow& a_callflow, const std::string& a_mailbox);
   virtual void VMailRecordOptions( ACallflow& a_callflow);
   virtual void VMailRecordSave( ACallflow& a_callflow);
   virtual void VMailRecordPlay( ACallflow& a_callflow, const std::string& a_mailbox);
   virtual void VMailRecordCancel( ACallflow& a_callflow, const std::string& a_mailbox);

   virtual void VMailPlayGetMailbox( ACallflow& a_callflow);
   virtual void VMailPlayMailboxEmpty( ACallflow& a_callflow);
   virtual void VMailPlay( ACallflow& a_callflow, const std::string& a_mailbox);
   virtual void VMailPlayOptions( ACallflow& a_callflow);
   virtual void VMailPlayDelete( ACallflow& a_callflow, const std::string& a_mailbox);

   virtual void AnnounceDisconnect( ACallflow& a_callflow);
   virtual void FeatureUnavailable( ACallflow& a_callflow);
   virtual void NotImplemented( ACallflow& a_callflow);
   virtual void InvalidMenuInput( ACallflow& a_callflow);
   virtual void InvalidMailbox( ACallflow& a_callflow);
   virtual void EmptyMailbox( ACallflow& a_callflow);

   virtual void ConferenceMenu( ACallflow& a_callflow);
   virtual void ConferenceCreateGetConferenceId( ACallflow& a_callflow);
   virtual void ConferenceJoinGetConferenceId( ACallflow& a_callflow);
   virtual void InvalidConferenceId( ACallflow& a_callflow);
   virtual void ConferenceIdDoesNotExist( ACallflow& a_callflow);
   virtual void ConferenceIdAlreadyExists( ACallflow& a_callflow);
   virtual void CreateConference( ACallflow& a_callflow, const std::string& a_conferenceId);
   virtual void JoinConference( ACallflow& a_callflow, const std::string& a_conferenceId);
   virtual void LeaveConference( ACallflow& a_callflow, const std::string& a_conferenceId);

   virtual void ModifyConference( ACallflow& a_callflow, const std::string& a_conferenceId, int a_action);
   virtual void ModifyStream( ACallflow& a_callflow, const std::string& a_conferenceId);
   virtual void CollectDtmfs( ACallflow& a_callflow);

   virtual void OnCheckMailboxComplete( ACallflow& a_callflow, int a_result);
   virtual void OnMessageDeleted( ACallflow& a_callflow, int a_result);

private:
   void LogInvalidStateForCommand( ACallflow& a_callflow, const char* a_command);
   void LogInvalidStateForEvent( ACallflow& a_callflow, const char* a_event);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::ACallflowInitializedState
//
// Description: Callflow initialized state
//
///////////////////////////////////////////////////////////////////////////////
class ACallflowInitializedState : public ACallflowState
{
public:
//   const char* StateDesc() = 0;
   void Reset( ACallflow& a_callflow);
   virtual void Disconnect( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowIdleState
//
// Description: Callflow idle state
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowIdleState : public ACallflowInitializedState
{
public:
   const char* StateDesc() { return "idle"; }
   void Start( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowFailedState
//
// Description: Callflow dialog failed state
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowFailedState : public ACallflowInitializedState
{
public:
   const char* StateDesc() { return "failed"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::ACallflowDialogState
//
// Description: Anstract Callflow dialog executing state
//
///////////////////////////////////////////////////////////////////////////////
class ACallflowDialogState : public ACallflowInitializedState
{
public:
   const char* StateDesc() = 0;
   void OnDialogFailed( ACallflow& a_callflow, const CMsmlResponseSptr& a_responseData);
   void OnDialogEvent( ACallflow& a_callflow, const CMsmlEventSptr& a_event);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowAnnounceDisconnectState
//
// Description: Callflow anouncing disconnect state
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowAnnounceDisconnectState : public ACallflowDialogState
{
public:
   const char* StateDesc() { return "disconnect"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::ACallflowMainMenuAvailableState
//
// Description: Abstract Callflow state for when the main menu is available
//
///////////////////////////////////////////////////////////////////////////////
class ACallflowMainMenuAvailableState : public ACallflowDialogState
{
public:
   virtual const char* StateDesc() = 0;
   void MainMenu( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::ACallflowVMailMenuAvailableState
//
// Description: Abstract Callflow state for when the voice/video menu is available
//
///////////////////////////////////////////////////////////////////////////////
class ACallflowVMailMenuAvailableState : public ACallflowDialogState
{
public:
   virtual const char* StateDesc() = 0;
   void VMailMenu( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::ACallflowConferenceMenuAvailableState
//
// Description: Abstract Callflow state for when the conference menu is available
//
///////////////////////////////////////////////////////////////////////////////
class ACallflowConferenceMenuAvailableState : public ACallflowDialogState
{
public:
   virtual const char* StateDesc() = 0;
   void ConferenceMenu( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowFeatureUnavailableState
//
// Description: Callflow state for when the "{feature unavailable" message is 
// playing
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowFeatureUnavailableState : public ACallflowMainMenuAvailableState
{
public:
   const char* StateDesc() { return "not implemented"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowNotImplementedState
//
// Description: Callflow state for when the "not implemented" message is playing
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowNotImplementedState : public ACallflowMainMenuAvailableState
{
public:
   const char* StateDesc() { return "not implemented"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowMainMenuState
//
// Description: Callflow state for when the main menu dialog is executing
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowMainMenuState : public ACallflowDialogState
{
public:
   const char* StateDesc() { return "main menu"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailMenu( ACallflow& a_callflow);
   void ConferenceMenu( ACallflow& a_callflow);
   void AnnounceDisconnect( ACallflow& a_callflow);
   void FeatureUnavailable( ACallflow& a_callflow);
   void NotImplemented( ACallflow& a_callflow);
   void InvalidMenuInput( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowMainMenuInvalidInputState
//
// Description: Callflow state for when the "missing or unexpected input" 
// message is playing after the main menu dialog
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowMainMenuInvalidInputState : public ACallflowMainMenuAvailableState
{
public:
   const char* StateDesc() { return "main menu invalid input"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailMenuState
//
// Description: Callflow state for when the voice/video menu dialog is 
// executing
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailMenuState : public ACallflowMainMenuAvailableState
{
public:
   const char* StateDesc() { return "vmail menu"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailPlayGetMailbox( ACallflow& a_callflow);
   void VMailRecordGetMailbox( ACallflow& a_callflow);
   void InvalidMenuInput( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailMenuInvalidInputState
//
// Description: Callflow state for when the "missing or unexpected input" 
// message is playing after the voice/video menu dialog
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailMenuInvalidInputState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "invalid input"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordGetMailboxState
//
// Description: Callflow state for when the "get mailbox number" dialog is 
// executing
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordGetMailboxState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "get mailbox"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailRecordStart( ACallflow& a_callflow, const std::string& a_mailbox);
   void InvalidMailbox( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordStartState
//
// Description: Callflow state for when the voice/video "start record" menu 
// dialog is executing
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordStartState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "record start"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailRecord( ACallflow& a_callflow, const std::string& a_mailbox);
   void InvalidMenuInput( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordStartInvalidInputState
//
// Description: Callflow state for when the "missing or unexpected input" 
// message is playing after the voice/video "start record" menu dialog
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordStartInvalidInputState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "record start invalid"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailRecordStart( ACallflow& a_callflow, const std::string& a_mailbox);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordState
//
// Description: Callflow state for when the record message dialog is executing.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "record"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailRecordCancel( ACallflow& a_callflow, const std::string& a_mailbox);
   void VMailRecordOptions( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordOptionsState
//
// Description: Callflow state for when the record options menu dialog is 
// executing.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordOptionsState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "record options"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailRecordStart( ACallflow& a_callflow, const std::string& a_mailbox);
   void VMailRecordSave( ACallflow& a_callflow);
   void VMailRecordPlay( ACallflow& a_callflow, const std::string& a_mailbox);
   void VMailRecordCancel( ACallflow& a_callflow, const std::string& a_mailbox);
   void InvalidMenuInput( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordOptionsInvalidInputState
//
// Description: Callflow state for when the "missing or unexpected input" 
// message is playing after the voice/video record options menu dialog
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordOptionsInvalidInputState : public ACallflowMainMenuAvailableState
{
public:
   const char* StateDesc() { return "record options invalid input"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailRecordOptions( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordInvalidMailboxState
//
// Description: Callflow state for when the "invalid mailbox" message is 
// playing.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordInvalidMailboxState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "invalid mailbox"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailRecordGetMailbox( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordSaveState
//
// Description: Callflow state for when the "message saved" message is playing.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordSaveState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "record save"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordPlayState
//
// Description: Callflow state for when the message is being played after 
// being recoded.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordPlayState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "record play"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailRecordOptions( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailRecordCancelState
//
// Description: Callflow state for when the "message deleted" message is 
// playing after a record.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailRecordCancelState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "record cancel"; }
   void OnMessageDeleted( ACallflow& a_callflow, int a_result);
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailPlayGetMailboxState
//
// Description: Callflow state for when the "get mailbox" dialog is executing
// for a play message operation.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailPlayGetMailboxState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "get mailbox"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void OnCheckMailboxComplete( ACallflow& a_callflow, int a_result);
   void VMailPlay( ACallflow& a_callflow, const std::string& a_mailbox);
   void EmptyMailbox( ACallflow& a_callflow);
   void InvalidMailbox( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailPlayMailboxEmptyState
//
// Description: Callflow state for when the "mailbox empty" message is playing.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailPlayMailboxEmptyState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "mailbox empty"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailPlayInvalidMailboxState
//
// Description: Callflow state for when the "invalid mailbox enterd" message is 
// playing.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailPlayInvalidMailboxState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "invalid mailbox"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailPlayGetMailbox( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailPlayState
//
// Description: Callflow state for when a message is being played
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailPlayState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "play"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailPlayOptions( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailPlayOptionsState
//
// Description: Callflow state for when the record options menu dialog is 
// executing.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailPlayOptionsState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "play options"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailPlay( ACallflow& a_callflow, const std::string& a_mailbox);
   void VMailPlayDelete( ACallflow& a_callflow, const std::string& a_mailbox);
   void InvalidMenuInput( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailPlayOptionsInvalidInputState
//
// Description: Callflow state for when the "missing or unexpected input" 
// message is playing after the voice/video play options menu dialog
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailPlayOptionsInvalidInputState : public ACallflowMainMenuAvailableState
{
public:
   const char* StateDesc() { return "play options invalid input"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void VMailPlayOptions( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowVMailPlayDeleteState
//
// Description: Callflow state for when the "message deleted" message is 
// playing after a play.
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowVMailPlayDeleteState : public ACallflowVMailMenuAvailableState
{
public:
   const char* StateDesc() { return "play delete"; }
   void OnMessageDeleted( ACallflow& a_callflow, int a_result);
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceMenuState
//
// Description: Callflow state for the conference menu dialog
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceMenuState : public ACallflowMainMenuAvailableState
{
public:
   const char* StateDesc() { return "conf menu"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void ConferenceCreateGetConferenceId( ACallflow& a_callflow);
   void ConferenceJoinGetConferenceId( ACallflow& a_callflow);
   void InvalidMenuInput( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceMenuState
//
// Description: Callflow state for when missing or invalid input is detected
// when running the conference menu dialog
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceMenuInvalidInputState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "conf menu invalid input"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceCreateGetIdState
//
// Description: Callflow state for the conference ID dialog when creating a 
// conference
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceCreateGetIdState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "create get ID"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void CreateConference( ACallflow& a_callflow, const std::string& a_conferenceId);
   void InvalidConferenceId( ACallflow& a_callflow);
   void ConferenceIdAlreadyExists( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceCreateInvalidIdState
//
// Description: Callflow state for the invalid conference ID dialog
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceCreateInvalidIdState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "create - invalid ID"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceCreateIdExistsState
//
// Description: Callflow state for the conference ID already exists dialog
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceCreateIdExistsState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "create - ID exists"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceCreatingState
//
// Description: Callflow state for creating a conference
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceCreatingState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "conf create"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void JoinConference( ACallflow& a_callflow, const std::string& a_conferenceId);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceJoinGetIdState
//
// Description: Callflow state for the conference ID dialog when joining a 
// conference
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceJoinGetIdState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "join get ID"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void JoinConference( ACallflow& a_callflow, const std::string& a_conferenceId);
   void InvalidConferenceId( ACallflow& a_callflow);
   void ConferenceIdDoesNotExist( ACallflow& a_callflow);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceCreateGetIdState
//
// Description: Callflow state for the conference ID dialog when joining a 
// conference
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceJoinInvalidIdState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "join invalid ID"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceJoinIdDoesNotExistState
//
// Description: Callflow state for when a conference doesn't exist when joining
// a conference
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceJoinIdDoesNotExistState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "no conf"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceJoiningState
//
// Description: Callflow state for joining a conference
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceJoiningState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "conf join"; }
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowConferenceActiveState
//
// Description: Callflow state for when the call is in an active conference
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowConferenceActiveState : public ACallflowConferenceMenuAvailableState
{
public:
   const char* StateDesc() { return "conf active"; }
   void CollectDtmfs( ACallflow& a_callflow);
   void ModifyConference( ACallflow& a_callflow, const std::string& a_conferenceId,int a_action);
   void ModifyStream( ACallflow& a_callflow, const std::string& a_conferenceId);
   void OnDialogEvent( ACallflow& a_callflow, const CMsmlEventSptr& a_event);
   void OnDialogComplete( ACallflow& a_callflow, const CMsmlResponseSptr& a_response);
   void Disconnect( ACallflow& a_callflow);
};

#endif
