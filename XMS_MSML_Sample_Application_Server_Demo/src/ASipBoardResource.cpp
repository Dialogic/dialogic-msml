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
// File Name: ASipBoardResource.cpp
//
// Description: ASipBoardResource class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "TypeDefs.h"
#include "ASipBoardResource.h"
#include "CTask.h"
#include "CTaskProcessor.h"

CSipBoardResourceClosedState ASipBoardResource::m_closedState;;
CSipBoardResourceOpeningState ASipBoardResource::m_openingState;
CSipBoardResourceOpenedState ASipBoardResource::m_openedState;
CSipBoardResourceClosingState ASipBoardResource::m_closingState;

///////////////////////////////////////////////////////////////////////////////
// Function: ASipBoardResource::ASipBoardResource( CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
ASipBoardResource::ASipBoardResource( CTaskProcessorSptr a_taskProcessor)
   : ATaskHandler( a_taskProcessor)
   , m_state( &m_closedState)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ASipBoardResource::~ASipBoardResource()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ASipBoardResource::~ASipBoardResource()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* ASipBoardResource::StateDesc()
//
// Description: Access a description of the current state
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* ASipBoardResource::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum ASipBoardResource::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum ASipBoardResource::LogObjectType()
{
   return LogObject_Resource;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResource::Open()
//
// Description: Queue a task to open the SIP Board Resource
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResource::Open()
{
   LogDebug( "Open");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipBoardResource::BasicOpen, this), 
                                              "ASipBoardResource::BasicOpen"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResource::OnOpened(const CMetaEventSptr &a_metaEvent)
//
// Description: Queue a task to handle the SIP Board Resource open completion event
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResource::OnOpened( const CMetaEventSptr& a_metaEvent)
{
   LogDebug( "OnOpened");
   ATaskSptr l_task( new CTask1<CMetaEventSptr>( 
                           boost::bind( &ASipBoardResource::BasicOnOpened, this, _1),
                                        a_metaEvent,
                                        "ASipBoardResource::BasicOnOpened"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResource::Close()
//
// Description: Queue a task to close the SIP Board Resource
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResource::Close()
{
   LogDebug( "Close");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipBoardResource::BasicClose, this),
                                              "ASipBoardResource::BasicClose"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResource::OnClosed()
//
// Description: Queue a task to handle the SIP Board Resource close completion event
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResource::OnClosed()
{
   LogDebug( "OnClosed");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipBoardResource::BasicOnClosed, this),
                                              "ASipBoardResource::BasicOnClosed"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResource::BasicOpen()
//
// Description: Delegate the Open command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResource::BasicOpen()
{
   m_state->Open( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResource::BasicOnOpened(const CMetaEventSptr &a_metaEvent)
//
// Description: Delegate the OnOpened event to the state machine
//
// Return: void
//
// Parameters: const CMetaEventSptr &a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResource::BasicOnOpened( const CMetaEventSptr& a_metaEvent)
{
   m_state->OnOpened( *this, a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResource::BasicClose()
//
// Description: Delegate the Close command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResource::BasicClose()
{
   m_state->Close( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipBoardResource::BasicOnClosed()
//
// Description: Delegate the OnClosed event to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipBoardResource::BasicOnClosed()
{
   m_state->OnClosed( *this);
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
void ASipBoardResource::SetStateToClosed() { m_state = &m_closedState;}
void ASipBoardResource::SetStateToOpening() { m_state = &m_openingState;}
void ASipBoardResource::SetStateToOpened() { m_state = &m_openedState;}
void ASipBoardResource::SetStateToClosing() { m_state = &m_closingState;}


