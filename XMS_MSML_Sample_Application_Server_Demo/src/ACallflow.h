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
// File Name: ACallflow.h
//
// Description: ACallflow class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ACallflow_h
#define ACallflow_h

#include "TypeDefs.h"
#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "CallflowStates.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::ACallflow
//
// Description: The abstract callflow class implements the public interface and 
// state machine for Callflow object.  Callflow objects are responsible for
// the business logic processing of a call.
//
///////////////////////////////////////////////////////////////////////////////
class ACallflow : public ATaskHandler, public AObserverSubject
{
   friend class ACallflowState;
   friend class ACallflowInitializedState;
   friend class CCallflowIdleState;
   friend class CCallflowFailedState;
   friend class ACallflowDialogState;
   friend class CCallflowMainMenuState;
   friend class ACallflowMainMenuAvailableState;
   friend class ACallflowVMailMenuAvailableState;
   friend class CCallflowMainMenuInvalidInputState;
   friend class CCallflowVMailMenuState;
   friend class CCallflowVMailMenuInvalidInputState;
   friend class CCallflowAnnounceDisconnectState;
   friend class CCallflowFeatureUnavailableState;
   friend class CCallflowNotImplementedState;

   friend class CCallflowVMailRecordGetMailboxState;
   friend class CCallflowVMailRecordInvalidMailboxState;
   friend class CCallflowVMailRecordStartState; 
   friend class CCallflowVMailRecordStartInvalidInputState; 
   friend class CCallflowVMailRecordState; 
   friend class CCallflowVMailRecordOptionsState;
   friend class CCallflowVMailRecordOptionsInvalidInputState;
   friend class CCallflowVMailRecordSaveState;
   friend class CCallflowVMailRecordPlayState;
   friend class CCallflowVMailRecordCancelState;

   friend class CCallflowVMailPlayGetMailboxState;
   friend class CCallflowVMailPlayMailboxEmptyState;
   friend class CCallflowVMailPlayState; 
   friend class CCallflowVMailPlayOptionsState;
   friend class CCallflowVMailPlayDeleteState;
   friend class CCallflowVMailPlayOptionsInvalidInputState;
   friend class CCallflowVMailPlayInvalidMailboxState;

   friend class ACallflowConferenceMenuAvailableState;
   friend class CCallflowConferenceMenuState;
   friend class CCallflowConferenceMenuInvalidInputState;
   friend class CCallflowConferenceCreateGetIdState;
   friend class CCallflowConferenceCreateInvalidIdState;
   friend class CCallflowConferenceCreateIdExistsState;
   friend class CCallflowConferenceCreatingState;
   friend class CCallflowConferenceJoinGetIdState;
   friend class CCallflowConferenceJoinInvalidIdState;
   friend class CCallflowConferenceJoinIdDoesNotExistState;
   friend class CCallflowConferenceJoiningState;
   friend class CCallflowConferenceActiveState;

public:
   ACallflow( CTaskProcessorSptr a_taskProcessor);
   virtual ~ACallflow();

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

   virtual bool HasResourceGroup( AResourceGroupSptr a_resourceGroup);

   void Start();
   void Reset();
   void Disconnect();
   void OnDialogFailed( const CMsmlResponseSptr& a_responseData);
   void OnDialogEvent( const CMsmlEventSptr& a_event);
   void OnDialogComplete( const CMsmlResponseSptr& a_response);

   void MainMenu();
   void VMailMenu();
   void AnnounceDisconnect();
   void FeatureUnavailable();
   void NotImplemented();
   void InvalidMenuInput();

   void VMailRecordGetMailbox();
   void VMailRecordStart( const std::string& a_mailbox);
   void VMailRecord( const std::string& a_mailbox);
   void VMailRecordOptions();
   void VMailRecordSave();
   void VMailRecordPlay( const std::string& a_mailbox);
   void VMailRecordCancel( const std::string& a_mailbox);

   void VMailPlayGetMailbox();
   void VMailPlay( const std::string& a_mailbox);
   void VMailPlayOptions();
   void VMailPlayDelete( const std::string& a_mailbox);

   void InvalidMailbox();
   void EmptyMailbox();

   void ConferenceMenu();
   void ConferenceCreateGetConferenceId();
   void ConferenceJoinGetConferenceId();
   void InvalidConferenceId();
   void ConferenceIdDoesNotExist();
   void ConferenceIdAlreadyExists();
   void CreateConference( const std::string& a_conferenceId);
   void JoinConference( const std::string& a_conferenceId);
   void LeaveConference( const std::string& a_conferenceId);

   void ModifyConference( const std::string& a_conferenceId);
   void CycleLayouts( const std::string& a_conferenceId);
   void RotateParties( const std::string& a_conferenceId);
   void ModifyStream( const std::string& a_conferenceId);
   void CollectDtmfs();

   const std::string& ConferenceId();

   void OnCheckMailboxComplete(int a_result);
   void OnMessageDeleted(int a_result);

protected:
   virtual int PrimReset() = 0;
   virtual int PrimDisconnect() = 0;
   virtual int PrimOnDialogFailed( const CMsmlResponseSptr& a_responseData) = 0;
   virtual int PrimOnDialogEvent( const CMsmlEventSptr& a_event) = 0;
   virtual int PrimOnDialogComplete( const CMsmlResponseSptr& a_response) = 0;

   virtual int PrimMainMenu() = 0;
   virtual int PrimVMailMenu() = 0;
   virtual int PrimAnnounceDisconnect() = 0;
   virtual int PrimFeatureUnavailable() = 0;
   virtual int PrimNotImplemented() = 0;
   virtual int PrimInvalidMenuInput() = 0;

   virtual int PrimGetMailbox() = 0;
   virtual int PrimInvalidMailbox() = 0;
   virtual int PrimEmptyMailbox() = 0;

   virtual int PrimVMailRecordStart( const std::string& a_mailbox) = 0;
   virtual int PrimVMailRecord( const std::string& a_mailbox) = 0;
   virtual int PrimVMailRecordOptions() = 0;
   virtual int PrimVMailRecordSave() = 0;
   virtual int PrimVMailRecordPlay( const std::string& a_mailbox) = 0;
   virtual int PrimVMailRecordCancel( const std::string& a_mailbox) = 0;

   virtual int PrimVMailPlay( const std::string& a_mailbox) = 0;
   virtual int PrimVMailPlayOptions() = 0;
   virtual int PrimVMailPlayDelete( const std::string& a_mailbox) = 0;

   virtual int PrimConferenceMenu() = 0;
   virtual int PrimGetConferenceId() = 0;
   virtual int PrimInvalidConferenceId() = 0;
   virtual int PrimConferenceIdDoesNotExist() = 0;
   virtual int PrimConferenceIdAlreadyExists() = 0;
   virtual int PrimCreateConference( const std::string& a_conferenceId) = 0;
   virtual int PrimOnCreateConference( const CMsmlResponseSptr& a_response) = 0;
   virtual int PrimJoinConference( const std::string& a_conferenceId) = 0;
   virtual int PrimOnJoinConference( const CMsmlResponseSptr& a_response) = 0;
   virtual int PrimLeaveConference( const std::string& a_conferenceId) = 0;

   virtual int PrimModifyConference( const std::string& a_conferenceId, int a_action) = 0;
   virtual int PrimOnModifyConference( const CMsmlResponseSptr& a_response) = 0;
   virtual int PrimModifyStream( const std::string& a_conferenceId) = 0;
   virtual int PrimOnModifyStream( const CMsmlResponseSptr& a_response) = 0;
   virtual int PrimCollectDtmfs() = 0;

   virtual int PrimOnMessageDeleted( int a_result) = 0;

   void LastMenuSelection( const std::string& a_menuSelection);
   bool VideoAvailable();
   void VideoAvailable( const bool a_videoAvailable);
   bool VideoActive();
   void VideoActive( const bool a_videoActive);

   virtual void CheckMailbox( const std::string& a_mailbox, bool a_videoIsActive) = 0;
   virtual void DeleteMessage( const std::string& a_mailbox) = 0;

private:
   void BasicStart();
   void BasicReset();
   void BasicDisconnect();
   void BasicOnDialogFailed( const CMsmlResponseSptr& a_responseData);
   void BasicOnDialogEvent( const CMsmlEventSptr& a_event);
   void BasicOnDialogComplete( const CMsmlResponseSptr& a_response);

   void BasicMainMenu();
   void BasicVMailMenu();
   void BasicAnnounceDisconnect();
   void BasicFeatureUnavailable();
   void BasicNotImplemented();
   void BasicInvalidMenuInput();

   void BasicVMailRecordGetMailbox();
   void BasicVMailRecordStart( const std::string& a_mailbox);
   void BasicVMailRecord( const std::string& a_mailbox);
   void BasicVMailRecordOptions();
   void BasicVMailRecordSave();
   void BasicVMailRecordPlay( const std::string& a_mailbox);
   void BasicVMailRecordCancel( const std::string& a_mailbox);

   void BasicVMailPlayGetMailbox();
   void BasicVMailPlay( const std::string& a_mailbox);
   void BasicVMailPlayOptions();
   void BasicVMailPlayDelete( const std::string& a_mailbox);

   void BasicInvalidMailbox();
   void BasicEmptyMailbox();

   void BasicConferenceMenu();
   void BasicConferenceCreateGetConferenceId();
   void BasicConferenceJoinGetConferenceId();
   void BasicInvalidConferenceId();
   void BasicConferenceIdDoesNotExist();
   void BasicConferenceIdAlreadyExists();
   void BasicCreateConference( const std::string& a_conferenceId);
   void BasicJoinConference( const std::string& a_conferenceId);
   void BasicLeaveConference( const std::string& a_conferenceId);

   void BasicModifyConference( const std::string& a_conferenceId);
   void BasicCycleLayouts( const std::string& a_conferenceId);
   void BasicRotateParties( const std::string& a_conferenceId);
   void BasicModifyStream( const std::string& a_conferenceId);
   void BasicCollectDtmfs();

   void BasicOnCheckMailboxComplete( int a_result);
   void BasicOnMessageDeleted( int a_result);

   void SetStateToIdle();
   void SetStateToFailed();
   void SetStateToMainMenu();
   void SetStateToMainMenuInvalidInput();
   void SetStateToVMailMenu();
   void SetStateToVMailMenuInvalidInput();
   void SetStateToAnnounceDisconnect();
   void SetStateToFeatureUnavailable();
   void SetStateToNotImplemented();

   void SetStateToVMailRecordGetMailbox();
   void SetStateToVMailRecordInvalidMailbox();
   void SetStateToVMailRecordStart();
   void SetStateToVMailRecordStartInvalidInput();
   void SetStateToVMailRecord();
   void SetStateToVMailRecordOptions();
   void SetStateToVMailRecordOptionsInvalidInput();
   void SetStateToVMailRecordSave();
   void SetStateToVMailRecordPlay();
   void SetStateToVMailRecordCancel();

   void SetStateToVMailPlayGetMailbox();
   void SetStateToVMailPlayInvalidMailbox();
   void SetStateToVMailPlayMailboxEmpty();
   void SetStateToVMailPlay();
   void SetStateToVMailPlayOptions();
   void SetStateToVMailPlayOptionsInvalidInput();
   void SetStateToVMailPlayDelete();

   void SetStateToConferenceMenu();
   void SetStateToConferenceMenuInvalidInput();
   void SetStateToConferenceCreateGetId();
   void SetStateToConferenceCreateInvalidId();
   void SetStateToConferenceCreateIdExists();
   void SetStateToConferenceCreating();
   void SetStateToConferenceJoinGetId();
   void SetStateToConferenceJoinInvalidId();
   void SetStateToConferenceJoinIdDoesNotExist();
   void SetStateToConferenceJoining();
   void SetStateToConferenceActive();

   ACallflowState *m_state; 
   static CCallflowIdleState m_idleState; 
   static CCallflowFailedState m_failedState; 
   static CCallflowMainMenuState m_mainMenuState; 
   static CCallflowMainMenuInvalidInputState m_mainMenuInvalidInputState; 
   static CCallflowVMailMenuState m_vMailMenuState; 
   static CCallflowVMailMenuInvalidInputState m_vMailMenuInvalidInputState; 
   static CCallflowAnnounceDisconnectState m_announceDisconnectState; 
   static CCallflowFeatureUnavailableState m_featureUnavailableState; 
   static CCallflowNotImplementedState m_notImplementedState; 

   static CCallflowVMailRecordGetMailboxState m_vMailRecordGetMailboxState; 
   static CCallflowVMailRecordInvalidMailboxState m_vMailRecordInvalidMailboxState;
   static CCallflowVMailRecordStartState m_vMailRecordStartState; 
   static CCallflowVMailRecordStartInvalidInputState m_vMailRecordStartInvalidInputState; 
   static CCallflowVMailRecordState m_vMailRecordState; 
   static CCallflowVMailRecordOptionsState m_vMailRecordOptionsState; 
   static CCallflowVMailRecordOptionsInvalidInputState m_vMailRecordOptionsInvalidInputState; 
   static CCallflowVMailRecordSaveState m_vMailRecordSaveState; 
   static CCallflowVMailRecordPlayState m_vMailRecordPlayState; 
   static CCallflowVMailRecordCancelState m_vMailRecordCancelState; 

   static CCallflowVMailPlayGetMailboxState m_vMailPlayGetMailboxState; 
   static CCallflowVMailPlayInvalidMailboxState m_vMailPlayInvalidMailboxState;
   static CCallflowVMailPlayMailboxEmptyState m_vMailPlayMailboxEmptyState;
   static CCallflowVMailPlayState m_vMailPlayState; 
   static CCallflowVMailPlayOptionsState m_vMailPlayOptionsState; 
   static CCallflowVMailPlayOptionsInvalidInputState m_vMailPlayOptionsInvalidInputState; 
   static CCallflowVMailPlayDeleteState m_vMailPlayDeleteState;

   static CCallflowConferenceMenuState m_conferenceMenuState;
   static CCallflowConferenceMenuInvalidInputState m_conferenceMenuInvalidInputState; 
   static CCallflowConferenceCreateGetIdState m_conferenceCreateGetIdState;
   static CCallflowConferenceCreateInvalidIdState m_conferenceCreateInvalidIdState;
   static CCallflowConferenceCreateIdExistsState m_conferenceCreateIdExistsState;
   static CCallflowConferenceCreatingState m_conferenceCreatingState;
   static CCallflowConferenceJoinGetIdState m_conferenceJoinGetIdState;
   static CCallflowConferenceJoinInvalidIdState m_conferenceJoinInvalidIdState;
   static CCallflowConferenceJoinIdDoesNotExistState m_conferenceJoinIdDoesNotExistState;
   static CCallflowConferenceJoiningState m_conferenceJoiningState;
   static CCallflowConferenceActiveState m_conferenceActiveState;

   const std::string& LastMenuSelection();
   bool LastMenuSelectionIncludesAsterisk();

   const std::string& Mailbox();
   void Mailbox( const std::string& a_mailbox);
   bool IsValidMailbox( const std::string& a_mailbox);
//   bool MailboxIsEmpty( const std::string& a_mailbox, bool a_videoIsActive);

   void ConferenceId( const std::string& a_conferenceId);
   bool IsValidConferenceId( const std::string& a_conferenceId);
   bool ConferenceIdExists( const std::string& a_conferenceId);

   std::string m_lastMenuSelection;
   std::string m_mailbox;
   std::string m_conferenceId;
   bool m_videoAvailable;
   bool m_videoActive;
};

#endif
