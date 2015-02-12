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
// File Name: ASipResourceManager.cpp
//
// Description: ASipResourceManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "ASipResourceManager.h"
#include "CTask.h"
#include "CTaskProcessor.h"
#include "ASipBoardResource.h"
#include "ASipResource.h"

CSipResourceManagerStoppedState ASipResourceManager::m_stoppedState;;
CSipResourceManagerStartingSrlEventManagerState ASipResourceManager::m_startingSrlEventManagerState;
CSipResourceManagerOpeningSipBoardResourceState ASipResourceManager::m_openingSipBoardResourceState; 
CSipResourceManagerOpeningSipResourcesState ASipResourceManager::m_openingSipResourcesState; 
CSipResourceManagerStartedState ASipResourceManager::m_startedState;
CSipResourceManagerClosingSipResourcesState ASipResourceManager::m_closingSipResourcesState; 
CSipResourceManagerClosingSipBoardResourceState ASipResourceManager::m_closingSipBoardResourceState; 
CSipResourceManagerStoppingSrlEventManagerState ASipResourceManager::m_stoppingSrlEventManagerState;

///////////////////////////////////////////////////////////////////////////////
// Function: ASipResourceManager::ASipResourceManager()
//
// Description: Default constructor - should never be called.  Always use the
// initializing constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ASipResourceManager::ASipResourceManager()
{
   assert(0);
}
   
///////////////////////////////////////////////////////////////////////////////
// Function: ASipResourceManager::ASipResourceManager(const CTaskProcessorSptr &a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: const CTaskProcessorSptr &a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
ASipResourceManager::ASipResourceManager( const CTaskProcessorSptr& a_taskProcessor)
   : ATaskHandler( a_taskProcessor)
   , m_state( &m_stoppedState)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: ASipResourceManager::~ASipResourceManager()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
ASipResourceManager::~ASipResourceManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ASipResourceManager::IsStopped()
//
// Description: Test if the Resource Manager is stopped
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ASipResourceManager::IsStopped()
{
   return m_state == &m_stoppedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool ASipResourceManager::IsStarted()
//
// Description: Test if the Resource Manager is started
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool ASipResourceManager::IsStarted()
{
   return m_state == &m_startedState;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* ASipResourceManager::StateDesc()
//
// Description: Access a description of the current state
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* ASipResourceManager::StateDesc()
{
   return m_state->StateDesc();
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogObjectTypeEnum ASipResourceManager::LogObjectType()
//
// Description: Access the LogObjectType
//
// Return: LogObjectTypeEnum 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
LogObjectTypeEnum ASipResourceManager::LogObjectType()
{
   return LogObject_ResourceManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::Start()
//
// Description: Queue a task to start the SIP Resource Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::Start()
{
   LogDebug( "Start");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipResourceManager::BasicStart, this), 
                                              "ASipResourceManager::BasicStart"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnSrlEventManagerStarted(int a_result)
//
// Description: Queue a task to handle an SRL Event Manager started event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnSrlEventManagerStarted( int a_result)
{
   LogDebugResult( "OnSrlEventManagerStarted", a_result);
   ATaskSptr l_task( new CTask1<int>(  boost::bind( &ASipResourceManager::BasicOnSrlEventManagerStarted, this, _1),
                                                    a_result,
                                                    "ASipResourceManager::BasicOnSrlEventManagerStarted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnSipBoardResourceOpened(const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: Queue a task to handle a SIP Board Resource opened event
//
// Return: void
//
// Parameters: const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnSipBoardResourceOpened( const ASipBoardResourceSptr& a_sipBoardResource)
{
   LogDebug( "OnSipBoardResourceOpened", a_sipBoardResource->Name());
   ATaskSptr l_task( new CTask1<ASipBoardResourceSptr> ( 
                        boost::bind( &ASipResourceManager::BasicOnSipBoardResourceOpened, this, _1),
                                     a_sipBoardResource,
                                     "ASipResourceManager::BasicOnSipBoardResourceOpened"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnSipResourceOpened(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle a SIP Resource opened event
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnSipResourceOpened( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnSipResourceOpened", a_sipResource->Name());
   ATaskSptr l_task( new CTask1<ASipResourceSptr> ( 
                        boost::bind( &ASipResourceManager::BasicOnSipResourceOpened, this, _1),
                                     a_sipResource,
                                     "ASipResourceManager::BasicOnSipResourceOpened"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnStarted(int a_result)
//
// Description: Queue a task to handle the SIP Resource Manager started 
// completion event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnStarted( int a_result)
{
   LogDebugResult( "OnStarted", a_result);
   ATaskSptr l_task( new CTask1<int>(  boost::bind( &ASipResourceManager::BasicOnStarted, this, _1),
                                                    a_result,
                                                    "ASipResourceManager::BasicOnStarted"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::EnableInboundCalls()
//
// Description: Queue a task to enable inbound calls on all SIP Resources
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::EnableInboundCalls()
{
   LogDebug( "EnableInboundCalls");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipResourceManager::BasicEnableInboundCalls, this),
                                              "ASipResourceManager::BasicEnableInboundCalls"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnCallOffered(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle a SIP Resource call offered event
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnCallOffered( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnCallOffered", a_sipResource->Name());
   ATaskSptr l_task( new CTask1<ASipResourceSptr> ( 
                        boost::bind( &ASipResourceManager::BasicOnCallOffered, this, _1),
                                     a_sipResource,
                                     "ASipResourceManager::BasicOnCallOffered"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnCallDisconnected(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle a SIP Resource call disconnected event
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnCallDisconnected( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnCallDisconnected", a_sipResource->Name());
   ATaskSptr l_task( new CTask1<ASipResourceSptr> ( 
                        boost::bind( &ASipResourceManager::BasicOnCallDisconnected, this, _1),
                                     a_sipResource,
                                     "ASipResourceManager::BasicOnCallDisconnected"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::Stop()
//
// Description: Queue a task to stop the SIP Resource Manager
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::Stop()
{
   LogDebug( "Stop");
   ATaskSptr l_task( new CTask0( boost::bind( &ASipResourceManager::BasicStop, this),
                                              "ASipResourceManager::BasicStop"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnSipResourceClosed(const ASipResourceSptr &a_sipResource)
//
// Description: Queue a task to handle a SIP Resource closed event
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnSipResourceClosed( const ASipResourceSptr& a_sipResource)
{
   LogDebug( "OnSipResourceClosed", a_sipResource->Name());
   ATaskSptr l_task( new CTask1<ASipResourceSptr> ( 
                        boost::bind( &ASipResourceManager::BasicOnSipResourceClosed, this, _1),
                                     a_sipResource,
                                     "ASipResourceManager::BasicOnSipResourceClosed"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnSipBoardResourceClosed(const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: Queue a task to handle a SIP Board Resource closed event
//
// Return: void
//
// Parameters: const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnSipBoardResourceClosed( const ASipBoardResourceSptr& a_sipBoardResource)
{
   LogDebug( "OnSipBoardResourceClosed", a_sipBoardResource->Name());
   ATaskSptr l_task( new CTask1<ASipBoardResourceSptr> ( 
                        boost::bind( &ASipResourceManager::BasicOnSipBoardResourceClosed, this, _1),
                                     a_sipBoardResource,
                                     "ASipResourceManager::BasicOnSipBoardResourceClosed"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnSrlEventManagerStopped(int a_result)
//
// Description: Queue a task to handle an SRL Event Manager stopped event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnSrlEventManagerStopped( int a_result)
{
   LogDebugResult( "OnSrlEventManagerStopped", a_result);
   ATaskSptr l_task( new CTask1<int>( boost::bind( &ASipResourceManager::BasicOnSrlEventManagerStopped, this, _1),
                                                   a_result,
                                                   "ASipResourceManager::BasicOnSrlEventManagerStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::OnStopped(int a_result)
//
// Description: Queue a task to handle the SIP Resource Manager stopped 
// completion event
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::OnStopped( int a_result)
{
   LogDebugResult( "OnStopped", a_result);
   ATaskSptr l_task( new CTask1<int>( boost::bind( &ASipResourceManager::BasicOnStopped, this, _1),
                                                   a_result,
                                                   "ASipResourceManager::BasicOnStopped"));
   TaskProcessor()->QueueTask( l_task);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicStart()
//
// Description: Delegate the Start command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicStart()
{
   m_state->Start( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnSrlEventManagerStarted(int a_result)
//
// Description: Delegate the OnSrlEventManagerStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnSrlEventManagerStarted( int a_result)
{
   m_state->OnSrlEventManagerStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnSipBoardResourceOpened(const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: Delegate the OnSipBoardResourceOpened event to the state machine
//
// Return: void
//
// Parameters: const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnSipBoardResourceOpened( const ASipBoardResourceSptr& a_sipBoardResource)
{
   m_state->OnSipBoardResourceOpened( *this, a_sipBoardResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnSipResourceOpened(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnSipResourceOpened event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnSipResourceOpened( const ASipResourceSptr& a_sipResource)
{
   m_state->OnSipResourceOpened( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnStarted(int a_result)
//
// Description: Delegate the OnStarted event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnStarted( int a_result)
{
   m_state->OnStarted( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicEnableInboundCalls()
//
// Description: Delegate the EnableInboundCalls command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicEnableInboundCalls()
{
   m_state->EnableInboundCalls( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnCallOffered(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnCallOffered event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnCallOffered( const ASipResourceSptr& a_sipResource)
{
   m_state->OnCallOffered( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnCallDisconnected(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnCallDisconnected event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnCallDisconnected( const ASipResourceSptr& a_sipResource)
{
   m_state->OnCallDisconnected( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicStop()
//
// Description: Delegate the Stop command to the state machine
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicStop()
{
   m_state->Stop( *this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnSipResourceClosed(const ASipResourceSptr &a_sipResource)
//
// Description: Delegate the OnSipResourceClosed event to the state machine
//
// Return: void
//
// Parameters: const ASipResourceSptr &a_sipResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnSipResourceClosed( const ASipResourceSptr& a_sipResource)
{
   m_state->OnSipResourceClosed( *this, a_sipResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnSipBoardResourceClosed(const ASipBoardResourceSptr &a_sipBoardResource)
//
// Description: Delegate the OnSipBoardResourceClosed event to the state machine
//
// Return: void
//
// Parameters: const ASipBoardResourceSptr &a_sipBoardResource
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnSipBoardResourceClosed( const ASipBoardResourceSptr& a_sipBoardResource)
{
   m_state->OnSipBoardResourceClosed( *this, a_sipBoardResource);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnSrlEventManagerStopped(int a_result)
//
// Description: Delegate the OnSrlEventManagerStopped event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnSrlEventManagerStopped( int a_result)
{
   m_state->OnSrlEventManagerStopped( *this, a_result);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ASipResourceManager::BasicOnStopped(int a_result)
//
// Description: Delegate the OnStopped event to the state machine
//
// Return: void
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
void ASipResourceManager::BasicOnStopped( int a_result)
{
   m_state->OnStopped( *this, a_result);
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
void ASipResourceManager::SetStateToStopped() { m_state = &m_stoppedState;}
void ASipResourceManager::SetStateToStartingSrlEventManager() { m_state = &m_startingSrlEventManagerState;}
void ASipResourceManager::SetStateToOpeningSipBoardResource() { m_state = &m_openingSipBoardResourceState;}
void ASipResourceManager::SetStateToOpeningSipResources() { m_state = &m_openingSipResourcesState;}
void ASipResourceManager::SetStateToStarted() { m_state = &m_startedState;}
void ASipResourceManager::SetStateToClosingSipResources() { m_state = &m_closingSipResourcesState;}
void ASipResourceManager::SetStateToClosingSipBoardResource() { m_state = &m_closingSipBoardResourceState;}
void ASipResourceManager::SetStateToStoppingSrlEventManager() { m_state = &m_stoppingSrlEventManagerState;}


