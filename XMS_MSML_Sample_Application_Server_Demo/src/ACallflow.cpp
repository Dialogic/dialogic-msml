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
// File Name: ACallflow.cpp
//
// Description: ACallflow class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "boost/bind.hpp"

#include "ACallflow.h"
#include "CTask.h"
#include "CTaskProcessor.h"
#include "CConfigOptions.h"
#include "CConferenceManager.h"
#include "CHttpManager.h"
#include "CHttpRequest.h"

#include <fstream>

CCallflowIdleState ACallflow::m_idleState; 
CCallflowFailedState ACallflow::m_failedState; 
CCallflowMainMenuState ACallflow::m_mainMenuState; 
CCallflowMainMenuInvalidInputState ACallflow::m_mainMenuInvalidInputState; 
CCallflowVMailMenuState ACallflow::m_vMailMenuState; 
CCallflowVMailMenuInvalidInputState ACallflow::m_vMailMenuInvalidInputState; 
CCallflowAnnounceDisconnectState ACallflow::m_announceDisconnectState; 
CCallflowFeatureUnavailableState ACallflow::m_featureUnavailableState; 
CCallflowNotImplementedState ACallflow::m_notImplementedState; 

CCallflowVMailRecordGetMailboxState ACallflow::m_vMailRecordGetMailboxState; 
CCallflowVMailRecordInvalidMailboxState ACallflow::m_vMailRecordInvalidMailboxState; 
CCallflowVMailRecordStartState ACallflow::m_vMailRecordStartState; 
CCallflowVMailRecordStartInvalidInputState ACallflow::m_vMailRecordStartInvalidInputState; 
CCallflowVMailRecordState ACallflow::m_vMailRecordState; 
CCallflowVMailRecordOptionsState ACallflow::m_vMailRecordOptionsState; 
CCallflowVMailRecordOptionsInvalidInputState ACallflow::m_vMailRecordOptionsInvalidInputState; 
CCallflowVMailRecordSaveState ACallflow::m_vMailRecordSaveState; 
CCallflowVMailRecordPlayState ACallflow::m_vMailRecordPlayState; 
CCallflowVMailRecordCancelState ACallflow::m_vMailRecordCancelState; 

CCallflowVMailPlayGetMailboxState ACallflow::m_vMailPlayGetMailboxState; 
CCallflowVMailPlayInvalidMailboxState ACallflow::m_vMailPlayInvalidMailboxState; 
CCallflowVMailPlayMailboxEmptyState ACallflow::m_vMailPlayMailboxEmptyState; 
CCallflowVMailPlayState ACallflow::m_vMailPlayState; 
CCallflowVMailPlayOptionsState ACallflow::m_vMailPlayOptionsState; 
CCallflowVMailPlayOptionsInvalidInputState ACallflow::m_vMailPlayOptionsInvalidInputState; 
CCallflowVMailPlayDeleteState ACallflow::m_vMailPlayDeleteState; 

CCallflowConferenceMenuState ACallflow::m_conferenceMenuState;
CCallflowConferenceMenuInvalidInputState ACallflow::m_conferenceMenuInvalidInputState; 
CCallflowConferenceCreateGetIdState ACallflow::m_conferenceCreateGetIdState;
CCallflowConferenceCreateInvalidIdState ACallflow::m_conferenceCreateInvalidIdState;
CCallflowConferenceCreateIdExistsState ACallflow::m_conferenceCreateIdExistsState;
CCallflowConferenceCreatingState ACallflow::m_conferenceCreatingState;
CCallflowConferenceJoinGetIdState ACallflow::m_conferenceJoinGetIdState;
CCallflowConferenceJoinInvalidIdState ACallflow::m_conferenceJoinInvalidIdState;
CCallflowConferenceJoinIdDoesNotExistState ACallflow::m_conferenceJoinIdDoesNotExistState;
CCallflowConferenceJoiningState ACallflow::m_conferenceJoiningState;
CCallflowConferenceActiveState ACallflow::m_conferenceActiveState;

///////////////////////////////////////////////////////////////////////////////
// Function: ACallflow::ACallflow(CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
ACallflow::ACallflow( CTaskProcessorSptr a_taskProcessor)
   : ATaskHandler( a_taskProcessor)
   , m_state( &m_idleState)
   , m_lastMenuSelection("*")
   , m_mailbox("")
   , m_videoAvailable(false)
   , m_videoActive(false)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ACallflow::~ACallflow()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ACallflow::~ACallflow()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* ACallflow::StateDesc()
//
// Description: Access description of the current state
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* ACallflow::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum ACallflow::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum ACallflow::LogObjectType()
{
   return LogObject_Callflow;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflow::HasResourceGroup(AResourceGroupSptr a_resourceGroup)
//
// Description: Test if the Callflow has a Resource Group
//
// Return: bool 
//
// Parameters: AResourceGroupSptr a_resourceGroup 
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflow::HasResourceGroup( AResourceGroupSptr a_resourceGroup)
{
   return false;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::Start()
//
// Description: Queue a task to start Callflow processing
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::Start()
{
   LogDebug( "Start");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicStart, this), 
                                              "ACallflow::BasicStart"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::Reset()
//
// Description: Queue a task to reset the Callflow object
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::Reset()
{
   LogDebug( "Reset");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicReset, this), 
                                              "ACallflow::BasicReset"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::Disconnect()
//
// Description: Queue a task to disconnect the resource group
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::Disconnect()
{
   LogDebug( "Disconnect");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicDisconnect, this), 
                                              "ACallflow::BasicDisconnect"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::OnDialogFailed( const CMsmlResponseSptr& a_responseData)
//
// Description: Queue a task to process a failed dialog
//
// Return: void
//
// Parameters:  const CMsmlResponseSptr& a_responseData
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::OnDialogFailed( const CMsmlResponseSptr& a_responseData)
{
   LogDebug( "OnDialogFailed");
   ATaskSptr l_task( new CTask1<CMsmlResponseSptr>( boost::bind( &ACallflow::BasicOnDialogFailed, this, _1),
                                                                 a_responseData,
                                                                 "ACallflow::BasicOnDialogFailed"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::OnDialogEvent(const CMsmlEventSptr &a_event)
//
// Description: Queue a task to process a dialog event
//
// Return: void
//
// Parameters: const CMsmlEventSptr &a_event
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::OnDialogEvent( const CMsmlEventSptr& a_event)
{
   LogDebug( "OnDialogEvent");
   ATaskSptr l_task( new CTask1<CMsmlEventSptr>( boost::bind( &ACallflow::BasicOnDialogEvent, this, _1), 
                                                a_event,
                                                "ACallflow::BasicOnDialogEvent"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::OnDialogComplete( const CMsmlResponseSptr& a_response)
//
// Description: Queue a task to process a dialog completed event
//
// Return: void
//
// Parameters:  const CMsmlEventSptr& a_event
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::OnDialogComplete( const CMsmlResponseSptr& a_response)
{
   LogDebug( "OnDialogComplete");
   ATaskSptr l_task( new CTask1<CMsmlResponseSptr>( boost::bind( &ACallflow::BasicOnDialogComplete, this, _1),
                                                              a_response,
                                                              "ACallflow::BasicOnDialogComplete"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::MainMenu()
//
// Description: Queue a task to start the main menu dialog
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::MainMenu()
{
   LogDebug( "MainMenu");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicMainMenu, this), 
                                              "ACallflow::BasicMainMenu"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailMenu()
//
// Description: Queue a task to start the voice/video mail menu
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailMenu()
{
   LogDebug( "VMailMenu");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicVMailMenu, this), 
                                              "ACallflow::BasicVMailMenu"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::AnnounceDisconnect()
//
// Description: Queue a task to start a dialog announcing that the call is 
// being disconnected
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::AnnounceDisconnect()
{
   LogDebug( "AnnounceDisconnect");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicAnnounceDisconnect, this), 
                                              "ACallflow::BasicAnnounceDisconnect"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::FeatureUnavailable()
//
// Description: Queue a task to start a dialog announcing that a feature is 
// unavailable
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::FeatureUnavailable()
{
   LogDebug( "FeatureUnavailable");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicFeatureUnavailable, this), 
                                              "ACallflow::BasicFeatureUnavailable"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::NotImplemented()
//
// Description: Queue a task to start a dialog announcing that a feature is 
// not implemented
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::NotImplemented()
{
   LogDebug( "NotImplemented");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicNotImplemented, this), 
                                              "ACallflow::BasicNotImplemented"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::InvalidMenuInput()
//
// Description: Queue a task to start a dialog announcing that menu input is 
// missing, unexpected or invalid 
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::InvalidMenuInput()
{
   LogDebug( "InvalidMenuInput");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicInvalidMenuInput, this), 
                                              "ACallflow::BasicInvalidMenuInput"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailRecordGetMailbox()
//
// Description: Queue a task to start a dialog that collects a mailbox number 
// for recording a message
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailRecordGetMailbox()
{
   LogDebug( "VMailRecordGetMailbox");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicVMailRecordGetMailbox, this), 
                                              "ACallflow::BasicVMailRecordGetMailbox"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailRecordStart(const std::string &a_mailbox)
//
// Description: Queue a task to start a dialog for the message record menu
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailRecordStart( const std::string& a_mailbox)
{
   LogDebug( "VMailRecordStart");
   ATaskSptr l_task( new CTask1<std::string>( boost::bind( &ACallflow::BasicVMailRecordStart, this, _1),
                                              a_mailbox,
                                              "ACallflow::BasicVMailRecordStart"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailRecord(const std::string &a_mailbox)
//
// Description: Queue a task that starts a dialog that records a message
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailRecord( const std::string& a_mailbox)
{
   LogDebug( "VMailRecord");
   ATaskSptr l_task( new CTask1<std::string>( boost::bind( &ACallflow::BasicVMailRecord, this, _1),
                                              a_mailbox,
                                              "ACallflow::BasicVMailRecord"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailRecordOptions()
//
// Description: Queue a task that starts a dialog for an options menu to 
// disposition a message just recorded
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailRecordOptions()
{
   LogDebug( "VMailRecordOptions");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicVMailRecordOptions, this), 
                                              "ACallflow::BasicVMailRecordOptions"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailRecordSave()
//
// Description: Queue a task to start a dialog announcing that a message has 
// been saved
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailRecordSave()
{
   LogDebug( "VMailRecordSave");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicVMailRecordSave, this), 
                                              "ACallflow::BasicVMailRecordSave"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailRecordPlay(const std::string &a_mailbox)
//
// Description: Queue a task to start a dialog that plays a message just recorded
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailRecordPlay( const std::string& a_mailbox)
{
   LogDebug( "VMailRecordPlay");
   ATaskSptr l_task( new CTask1<std::string>( boost::bind( &ACallflow::BasicVMailRecordPlay, this, _1),
                                              a_mailbox,
                                              "ACallflow::BasicVMailRecordPlay"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailRecordCancel(const std::string &a_mailbox)
//
// Description: Queue a task that cancels a message record
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailRecordCancel( const std::string& a_mailbox)
{
   LogDebug( "VMailRecordCancel");
   ATaskSptr l_task( new CTask1<std::string>( boost::bind( &ACallflow::BasicVMailRecordCancel, this, _1),
                                              a_mailbox,
                                              "ACallflow::BasicVMailRecordCancel"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailPlayGetMailbox()
//
// Description: Queue a task to start a dialog that collects a mailbox number 
// for playing a message
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailPlayGetMailbox()
{
   LogDebug( "VMailPlayGetMailbox");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicVMailPlayGetMailbox, this), 
                                              "ACallflow::BasicVMailPlayGetMailbox"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailPlay(const std::string &a_mailbox)
//
// Description: Queue a task that starts a dialog that plays a message
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailPlay( const std::string& a_mailbox)
{
   LogDebug( "VMailPlay");
   ATaskSptr l_task( new CTask1<std::string>( boost::bind( &ACallflow::BasicVMailPlay, this, _1),
                                              a_mailbox,
                                              "ACallflow::BasicVMailPlay"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailPlayOptions()
//
// Description: Queue a task that starts a dialog for an options menu to 
// disposition a message just played
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailPlayOptions()
{
   LogDebug( "VMailPlayOptions");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicVMailPlayOptions, this), 
                                              "ACallflow::BasicVMailPlayOptions"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VMailPlayDelete(const std::string &a_mailbox)
//
// Description: Queue a task that deletes a message just played
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VMailPlayDelete( const std::string& a_mailbox)
{
   LogDebug( "VMailPlayDelete");
   ATaskSptr l_task( new CTask1<std::string>( boost::bind( &ACallflow::BasicVMailPlayDelete, this, _1),
                                              a_mailbox,
                                              "ACallflow::BasicVMailPlayDelete"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::InvalidMailbox()
//
// Description: Queue a task to start a dialog announcing that a malibox number
// just entered is invalid
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::InvalidMailbox()
{
   LogDebug( "InvalidMailbox");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicInvalidMailbox, this), 
                                              "ACallflow::BasicInvalidMailbox"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::EmptyMailbox()
//
// Description: Queue a task to start a dialog announcing that a malibox is 
// empty
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::EmptyMailbox()
{
   LogDebug( "EmptyMailbox");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicEmptyMailbox, this), 
                                              "ACallflow::BasicEmptyMailbox"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::ConferenceMenu()
//
// Description: Queue a task to start the conference menu dialog
// empty
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::ConferenceMenu()
{
   LogDebug( "ConferenceMenu");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicConferenceMenu, this), 
                                              "ACallflow::BasicConferenceMenu"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::ConferenceCreateGetConferenceId()
//
// Description: Queue a task to start the get conference ID dialog
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::ConferenceCreateGetConferenceId()
{
   LogDebug( "ConferenceCreateGetConferenceId");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicConferenceCreateGetConferenceId, this), 
                                              "ACallflow::BasicConferenceCreateGetConferenceId"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::ConferenceJoinGetConferenceId()
//
// Description: Queue a task to start the get conference ID dialog
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::ConferenceJoinGetConferenceId()
{
   LogDebug( "ConferenceJoinGetConferenceId");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicConferenceJoinGetConferenceId, this), 
                                              "ACallflow::BasicConferenceJoinGetConferenceId"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::InvalidConferenceId()
//
// Description: Queue a task to start a dialog to announce that an invalid 
// conference ID was entered
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::InvalidConferenceId()
{
   LogDebug( "InvalidConferenceId");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicInvalidConferenceId, this), 
                                              "ACallflow::BasicInvalidConferenceId"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::ConferenceIdDoesNotExist()
//
// Description: Queue a task to start a dialog to announce that a conference for
// a valid conference ID does not exist
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::ConferenceIdDoesNotExist()
{
   LogDebug( "ConferenceIdDoesNotExist");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicConferenceIdDoesNotExist, this), 
                                              "ACallflow::BasicConferenceIdDoesNotExist"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::ConferenceIdAlreadyExists()
//
// Description: Queue a task to start a dialog to announce that a conference for
// a valid conference ID already exists
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::ConferenceIdAlreadyExists()
{
   LogDebug( "ConferenceIdAlreadyExists");
   ATaskSptr l_task( new CTask0( boost::bind( &ACallflow::BasicConferenceIdAlreadyExists, this), 
                                              "ACallflow::BasicConferenceIdAlreadyExists"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::CreateConference( const std::string& a_conferenceId)
//
// Description: Queue a task that starts a dialog to create a conference
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::CreateConference( const std::string& a_conferenceId)
{
   LogDebug( "CreateConference");
   ATaskSptr l_task( new CTask1< std::string>( boost::bind( &ACallflow::BasicCreateConference, this, _1),
                                                            a_conferenceId,
                                                            "ACallflow::BasicCreateConference"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::JoinConference( const std::string& a_conferenceId)
//
// Description: Queue a task that starts a dialog to join a conference
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::JoinConference( const std::string& a_conferenceId)
{
   LogDebug( "JoinConference");
   ATaskSptr l_task( new CTask1< std::string>( boost::bind( &ACallflow::BasicJoinConference, this, _1),
                                                            a_conferenceId,
                                                            "ACallflow::BasicJoinConference"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::ModifyConference( const std::string& a_conferenceId)
//
// Description: Queue a task that starts a dialog to Modify a conference
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::ModifyConference( const std::string& a_conferenceId)
{
   LogDebug( "ModifyConference");
   ATaskSptr l_task( new CTask1< std::string>( boost::bind( &ACallflow::BasicModifyConference, this, _1),
                                                            a_conferenceId,
                                                            "ACallflow::BasicModifyConference"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::CycleLayouts( const std::string& a_conferenceId)
//
// Description: Queue a task that starts a dialog to Modify a conference and Cycle Layouts
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::CycleLayouts( const std::string& a_conferenceId)
{
   LogDebug( "CycleLayouts");
   ATaskSptr l_task( new CTask1< std::string>( boost::bind( &ACallflow::BasicCycleLayouts, this, _1),
                                                            a_conferenceId,
                                                            "ACallflow::BasicCycleLayouts"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::RotateParties( const std::string& a_conferenceId)
//
// Description: Queue a task that starts a dialog to Modify a conference and Rotate Parties
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::RotateParties( const std::string& a_conferenceId)
{
   LogDebug( "RotateParties");
   ATaskSptr l_task( new CTask1< std::string>( boost::bind( &ACallflow::BasicRotateParties, this, _1),
                                                            a_conferenceId,
                                                            "ACallflow::BasicRotateParties"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::ModifyStream( const std::string& a_conferenceId)
//
// Description: Queue a task that starts a dialog to Modify a conference
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::ModifyStream( const std::string& a_conferenceId)
{
   LogDebug( "ModifyStream");
   ATaskSptr l_task( new CTask1< std::string>( boost::bind( &ACallflow::BasicModifyStream, this, _1),
                                                            a_conferenceId,
                                                            "ACallflow::BasicModifyStream"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::CollectDtmfs()
//
// Description: Queue a task that starts a dialog to CollectDtmfs in a conference
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::CollectDtmfs()
{
   LogDebug( "CollectDtmfs");
   ATaskSptr l_task( new CTask1< std::string>( boost::bind( &ACallflow::BasicCollectDtmfs, this),                 
                                                            "ACallflow::BasicCollectDtmfs"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::LeaveConference( const std::string& a_conferenceId)
//
// Description: Queue a task that starts a dialog to leave a conference
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::LeaveConference( const std::string& a_conferenceId)
{
   LogDebug( "LeaveConference");
   ATaskSptr l_task( new CTask1< std::string>( boost::bind( &ACallflow::BasicLeaveConference, this, _1),
                                                            a_conferenceId,
                                                            "ACallflow::BasicLeaveConference"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::OnCheckMailboxComplete(int a_result)
//
// Description: Queue a task to handle the check mailbox completion event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::OnCheckMailboxComplete(int a_result)
{
   LogDebug( "OnCheckMailboxComplete");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &ACallflow::BasicOnCheckMailboxComplete, this, _1),
                                                            a_result,
                                                            "ACallflow::BasicOnCheckMailboxComplete"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::OnMessageDeleted(int a_result)
//
// Description: Queue a task to handle the delete message event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::OnMessageDeleted(int a_result)
{
   LogDebug( "OnMessageDeleted");
   ATaskSptr l_task( new CTask1<int>( boost::bind( &ACallflow::BasicOnMessageDeleted, this, _1),
                                                            a_result,
                                                            "ACallflow::BasicOnMessageDeleted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicStart()
//
// Description: Delegate the start command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicStart()
{
   m_state->Start( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicReset()
//
// Description: Delegate the reset command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicReset()
{
   m_state->Reset( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicDisconnect()
//
// Description: Delegate the disconnect command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicDisconnect()
{
   m_state->Disconnect( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicOnDialogFailed( const CMsmlResponseSptr& a_responseData)
//
// Description: Delegate the DialogFailed event to the state machine
//
// Return: void
//
// Parameters:  const CMsmlResponseSptr& a_responseData
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicOnDialogFailed( const CMsmlResponseSptr& a_responseData)
{
   m_state->OnDialogFailed( *this, a_responseData);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicOnDialogEvent(const CMsmlEventSptr &a_event)
//
// Description: Delegate the DialogEvent event to the state machine
//
// Return: void
//
// Parameters: const CMsmlEventSptr &a_event
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicOnDialogEvent( const CMsmlEventSptr& a_event)
{
   m_state->OnDialogEvent( *this, a_event);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicOnDialogComplete( const CMsmlResponseSptr& a_response)
//
// Description: Delegate the DialogComplete event to the state machine
//
// Return: void
//
// Parameters:  const CMsmlResponseSptr& a_response
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicOnDialogComplete( const CMsmlResponseSptr& a_response)
{
   m_state->OnDialogComplete( *this, a_response);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicMainMenu()
//
// Description: Delegate the MainMenu command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicMainMenu()
{
   m_state->MainMenu( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailMenu()
//
// Description: Delegate the VMailMenu command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailMenu()
{
   m_state->VMailMenu( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicAnnounceDisconnect()
//
// Description: Delegate the AnnounceDisconnect command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicAnnounceDisconnect()
{
   m_state->AnnounceDisconnect( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicFeatureUnavailable()
//
// Description: Delegate the FeatureUnavailable command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicFeatureUnavailable()
{
   m_state->FeatureUnavailable( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicNotImplemented()
//
// Description: Delegate the not implemented command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicNotImplemented()
{
   m_state->NotImplemented( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicInvalidMenuInput()
//
// Description: Delegate the InvalidMenuInput command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicInvalidMenuInput()
{
   m_state->InvalidMenuInput( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailRecordGetMailbox()
//
// Description: Delegate the VMailRecordGetMailbox command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailRecordGetMailbox()
{
   m_state->VMailRecordGetMailbox( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailRecord(const std::string &a_mailbox)
//
// Description: Delegate the VMailRecord command to the state machine
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailRecord( const std::string& a_mailbox)
{
   m_state->VMailRecord( *this, a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailRecordStart(const std::string &a_mailbox)
//
// Description: Delegate the VMailRecordStart command to the state machine
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailRecordStart( const std::string& a_mailbox)
{
   m_state->VMailRecordStart( *this, a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailRecordOptions()
//
// Description: Delegate the VMailRecord command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailRecordOptions()
{
   m_state->VMailRecordOptions( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailRecordSave()
//
// Description: Delegate the VMailRecordSave command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailRecordSave()
{
   m_state->VMailRecordSave( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailRecordPlay(const std::string &a_mailbox)
//
// Description: Delegate the VMailRecordPlay command to the state machine
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailRecordPlay( const std::string& a_mailbox)
{
   m_state->VMailRecordPlay( *this, a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailRecordCancel(const std::string &a_mailbox)
//
// Description: Delegate the VMailRecordCancel command to the state machine
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailRecordCancel( const std::string& a_mailbox)
{
   m_state->VMailRecordCancel( *this, a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailPlayGetMailbox()
//
// Description: Delegate the VMailPlayGetMailbox command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailPlayGetMailbox()
{
   m_state->VMailPlayGetMailbox( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailPlay(const std::string &a_mailbox)
//
// Description: Delegate the VMailPlay command to the state machine
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailPlay( const std::string& a_mailbox)
{
   m_state->VMailPlay( *this, a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailPlayOptions()
//
// Description: Delegate the VMailPlayOptions command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailPlayOptions()
{
   m_state->VMailPlayOptions( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicVMailPlayDelete(const std::string &a_mailbox)
//
// Description: Delegate the VMailPlayDelete command to the state machine
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicVMailPlayDelete( const std::string& a_mailbox)
{
   m_state->VMailPlayDelete( *this, a_mailbox);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicInvalidMailbox()
//
// Description: Delegate the InvalidMailbox command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicInvalidMailbox()
{
   m_state->InvalidMailbox( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicEmptyMailbox()
//
// Description: Delegate the EmptyMailbox command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicEmptyMailbox()
{
   m_state->EmptyMailbox( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicConferenceMenu()
//
// Description: Delegate the ConferenceMenu command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicConferenceMenu()
{
   m_state->ConferenceMenu( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicConferenceCreateGetConferenceId()
//
// Description: Delegate the Get Conference ID command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicConferenceCreateGetConferenceId()
{
   m_state->ConferenceCreateGetConferenceId( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicConferenceJoinGetConferenceId()
//
// Description: Delegate the Get Conference ID command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicConferenceJoinGetConferenceId()
{
   m_state->ConferenceJoinGetConferenceId( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicInvalidConferenceId()
//
// Description: Delegate the Invalid Conference ID command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicInvalidConferenceId()
{
   m_state->InvalidConferenceId( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicConferenceIdDoesNotExist()
//
// Description: Delegate the Conference ID Does Not Exist command to the state
// machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicConferenceIdDoesNotExist()
{
   m_state->ConferenceIdDoesNotExist( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicConferenceIdAlreadyExists()
//
// Description: Delegate the Conference ID Does Not Exist command to the state
// machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicConferenceIdAlreadyExists()
{
   m_state->ConferenceIdAlreadyExists( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicCreateConference( const std::string& a_conferenceId)
//
// Description: Delegate the Create Conference command to the state machine
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicCreateConference( const std::string& a_conferenceId)
{
   m_state->CreateConference( *this, a_conferenceId);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicJoinConference( const std::string& a_conferenceId)
//
// Description: Delegate the Join Conference command to the state machine
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicJoinConference( const std::string& a_conferenceId)
{
   m_state->JoinConference( *this, a_conferenceId);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicModifyConference( const std::string& a_conferenceId)
//
// Description: Delegate the Modify Conference command to the state machine
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicModifyConference( const std::string& a_conferenceId)
{
   m_state->ModifyConference( *this, a_conferenceId, 0);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicCycleLayouts( const std::string& a_conferenceId)
//
// Description: Delegate the Modify Conference command to the state machine
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicCycleLayouts( const std::string& a_conferenceId)
{
   m_state->ModifyConference( *this, a_conferenceId, 1);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicRotateParties( const std::string& a_conferenceId)
//
// Description: Delegate the Modify Conference command to the state machine
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicRotateParties( const std::string& a_conferenceId)
{
   m_state->ModifyConference( *this, a_conferenceId, 2);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicModifyStream( const std::string& a_conferenceId)
//
// Description: Delegate the Modify Stream command to the state machine
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicModifyStream( const std::string& a_conferenceId)
{
   m_state->ModifyStream( *this, a_conferenceId);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicCollectDtmfs()
//
// Description: Delegate the CollectDtmfs command to the state machine
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicCollectDtmfs()
{
   m_state->CollectDtmfs( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicLeaveConference( const std::string& a_conferenceId)
//
// Description: Delegate the Leave Conference command to the state machine
//
// Return: void
//
// Parameters: const std::string& a_conferenceId
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicLeaveConference( const std::string& a_conferenceId)
{
   m_state->LeaveConference( *this, a_conferenceId);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicOnCheckMailboxComplete( int a_result)
//
// Description: Delegate the check mailboc complete event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicOnCheckMailboxComplete( int a_result)
{
   m_state->OnCheckMailboxComplete( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::BasicOnMessageDeleted( int a_result)
//
// Description: Delegate the On Message Deleted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::BasicOnMessageDeleted( int a_result)
{
   m_state->OnMessageDeleted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & ACallflow::LastMenuSelection()
//
// Description: Access the last menu selection
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& ACallflow::LastMenuSelection()
{
   return m_lastMenuSelection;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflow::LastMenuSelectionIncludesAsterisk()
//
// Description: Test if the last menu selection includes an '*'
//
// Return: bool
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflow::LastMenuSelectionIncludesAsterisk()
{
   return ( m_lastMenuSelection.find("*") != m_lastMenuSelection.npos);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::LastMenuSelection(const std::string &a_menuSelection)
//
// Description: Set the last menu selection
//
// Return: void
//
// Parameters: const std::string &a_menuSelection
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::LastMenuSelection( const std::string& a_menuSelection)
{
   m_lastMenuSelection = a_menuSelection;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & ACallflow::Mailbox()
//
// Description: Access the mailbox number
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& ACallflow::Mailbox()
{
   return m_mailbox;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::Mailbox(const std::string &a_mailbox)
//
// Description: Set the mailbox number
//
// Return: void
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::Mailbox( const std::string& a_mailbox)
{
   m_mailbox = a_mailbox;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflow::IsValidMailbox(const std::string &a_mailbox)
//
// Description: Test if thye mailbox number is valid
//
// Return: bool
//
// Parameters: const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflow::IsValidMailbox( const std::string& a_mailbox)
{
   int l_mailbox = atoi( a_mailbox.c_str());
   if ( ( l_mailbox > 100) && ( l_mailbox < 300))
   {
      return true;
   }
   return false;
}

/*
///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflow::MailboxIsEmpty(const std::string &a_mailbox, bool a_videoIsActive)
//
// Description: Test if the mailbox is empty
//
// Return: bool
//
// Parameters: const std::string &a_mailbox
//             bool a_videoIsActive
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflow::MailboxIsEmpty( const std::string& a_mailbox, bool a_videoIsActive)
{
   std::string l_fileName;
   MakeMailboxPath( l_fileName, CConfigOptions::Instance()->MediaPath(), a_mailbox, a_videoIsActive);
   std::ifstream l_mailboxFile( l_fileName.c_str());
   if ( ! l_mailboxFile)
   {
      return true;
   }
   l_mailboxFile.close();
   return false;
}
*/
///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflow::VideoAvailable()
//
// Description: Test is video is available
//
// Return: bool
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflow::VideoAvailable()
{
   return m_videoAvailable;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VideoAvailable(const bool a_videoAvailable)
//
// Description: Set if video is available
//
// Return: void
//
// Parameters: const bool a_videoAvailable
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VideoAvailable( const bool a_videoAvailable)
{
   m_videoAvailable = a_videoAvailable;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflow::VideoActive()
//
// Description: Test if video is active
//
// Return: bool
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflow::VideoActive()
{
   return m_videoActive;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::VideoActive(const bool a_videoActive)
//
// Description: Set if video is active
//
// Return: void
//
// Parameters: const bool a_videoActive
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::VideoActive( const bool a_videoActive)
{
   m_videoActive = a_videoActive;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string& ACallflow::ConferenceId()
//
// Description: Access the Conference ID
//
// Return: const std::string& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const std::string& ACallflow::ConferenceId()
{
   return m_conferenceId;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ACallflow::ConferenceId(const std::string &a_conferenceId)
//
// Description: Set the Conference ID
//
// Return: void 
//
// Parameters: const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::ConferenceId( const std::string& a_conferenceId)
{
   m_conferenceId = a_conferenceId;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflow::IsValidConferenceId(const std::string &a_conferenceId)
//
// Description: Test if the converence ID is valid
//
// Return: bool 
//
// Parameters: const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflow::IsValidConferenceId( const std::string& a_conferenceId)
{
   int l_conferenceId = atoi( a_conferenceId.c_str());
   if ( ( l_conferenceId> 100) && ( l_conferenceId < 300))
   {
      return true;
   }
   return false;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ACallflow::ConferenceIdExists(const std::string &a_conferenceId)
//
// Description: Test if the conference exists
//
// Return: bool 
//
// Parameters: const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
bool ACallflow::ConferenceIdExists( const std::string& a_conferenceId)
{
   return CConferenceManager::Instance()->ConferenceExists( a_conferenceId);
}

///////////////////////////////////////////////////////////////////////////////
//	Function: State setting functions
//
//	Description: These functions set the current state
//
//	Return: void
//
//	Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ACallflow::SetStateToIdle() { m_state = &m_idleState;}
void ACallflow::SetStateToFailed() { m_state = &m_failedState;}
void ACallflow::SetStateToMainMenu() { m_state = &m_mainMenuState;}
void ACallflow::SetStateToMainMenuInvalidInput() { m_state = &m_mainMenuInvalidInputState;}
void ACallflow::SetStateToVMailMenu() { m_state = &m_vMailMenuState;}
void ACallflow::SetStateToVMailMenuInvalidInput() { m_state = &m_vMailMenuInvalidInputState;}
void ACallflow::SetStateToAnnounceDisconnect() { m_state = &m_announceDisconnectState;}
void ACallflow::SetStateToFeatureUnavailable() { m_state = &m_featureUnavailableState;}
void ACallflow::SetStateToNotImplemented() { m_state = &m_notImplementedState;}

void ACallflow::SetStateToVMailRecordGetMailbox() { m_state = &m_vMailRecordGetMailboxState;}
void ACallflow::SetStateToVMailRecordInvalidMailbox() { m_state = &m_vMailRecordInvalidMailboxState;}
void ACallflow::SetStateToVMailRecordStart() { m_state = &m_vMailRecordStartState;}
void ACallflow::SetStateToVMailRecordStartInvalidInput() { m_state = &m_vMailRecordStartInvalidInputState;}
void ACallflow::SetStateToVMailRecord() { m_state = &m_vMailRecordState;}
void ACallflow::SetStateToVMailRecordOptions() { m_state = &m_vMailRecordOptionsState;}
void ACallflow::SetStateToVMailRecordOptionsInvalidInput() { m_state = &m_vMailRecordOptionsInvalidInputState;}
void ACallflow::SetStateToVMailRecordSave() { m_state = &m_vMailRecordSaveState;}
void ACallflow::SetStateToVMailRecordPlay() { m_state = &m_vMailRecordPlayState;}
void ACallflow::SetStateToVMailRecordCancel() { m_state = &m_vMailRecordCancelState;}

void ACallflow::SetStateToVMailPlayGetMailbox() { m_state = &m_vMailPlayGetMailboxState;}
void ACallflow::SetStateToVMailPlayInvalidMailbox() { m_state = &m_vMailPlayInvalidMailboxState;}
void ACallflow::SetStateToVMailPlayMailboxEmpty() { m_state = &m_vMailPlayMailboxEmptyState;}
void ACallflow::SetStateToVMailPlay() { m_state = &m_vMailPlayState;}
void ACallflow::SetStateToVMailPlayOptions() { m_state = &m_vMailPlayOptionsState;}
void ACallflow::SetStateToVMailPlayOptionsInvalidInput() { m_state = &m_vMailPlayOptionsInvalidInputState;}
void ACallflow::SetStateToVMailPlayDelete() { m_state = &m_vMailPlayDeleteState;}

void ACallflow::SetStateToConferenceMenu() { m_state = &m_conferenceMenuState;}
void ACallflow::SetStateToConferenceMenuInvalidInput() { m_state = &m_conferenceMenuInvalidInputState;}
void ACallflow::SetStateToConferenceCreateGetId() { m_state = &m_conferenceCreateGetIdState;}
void ACallflow::SetStateToConferenceCreateInvalidId() { m_state = &m_conferenceCreateInvalidIdState;}
void ACallflow::SetStateToConferenceCreateIdExists() { m_state = &m_conferenceCreateIdExistsState;}
void ACallflow::SetStateToConferenceCreating() { m_state = &m_conferenceCreatingState;}
void ACallflow::SetStateToConferenceJoinGetId() { m_state = &m_conferenceJoinGetIdState;}
void ACallflow::SetStateToConferenceJoinInvalidId() { m_state = &m_conferenceJoinInvalidIdState;}
void ACallflow::SetStateToConferenceJoinIdDoesNotExist() { m_state = &m_conferenceJoinIdDoesNotExistState;}
void ACallflow::SetStateToConferenceJoining() { m_state = &m_conferenceJoiningState;}
void ACallflow::SetStateToConferenceActive() { m_state = &m_conferenceActiveState;}


