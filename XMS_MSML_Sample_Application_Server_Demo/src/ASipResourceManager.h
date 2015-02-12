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
// File Name: ASipResourceManager.h
//
// Description: ASipResourceManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ASipResourceManager_h
#define ASipResourceManager_h

#include "TypeDefs.h"
#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "SipResourceManagerStates.h"

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::EnumSipResourceManagerNotifications
//
// Description: Observer notifications supported by the SIP Resource Manager
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   SIPRESOURCE_MANAGER_STARTED,
   SIPRESOURCE_MANAGER_INBOUNDCALLS_ENABLED,
   SIPRESOURCE_MANAGER_STOPPED,
   SIPRESOURCE_MANAGER_CALL_OFFERED,
   SIPRESOURCE_MANAGER_CALL_DISCONNECTED,
} EnumSipResourceManagerNotifications;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ASipResourceManager
//
// Description: The abstract SIP Resource Manager class implements the public 
// interface and state machine for the concrete SIP Resource Manager.  The SIP
// Resource Manager is responsible for opening/closing SIP Resource objects, 
// enabling inbound calls and detecting offered calls.
//
///////////////////////////////////////////////////////////////////////////////
class ASipResourceManager : public ATaskHandler, public AObserverSubject
{
   friend class ASipResourceManagerState;
   friend class CSipResourceManagerStoppedState;
   friend class CSipResourceManagerStartingSrlEventManagerState;
   friend class CSipResourceManagerOpeningSipBoardResourceState;
   friend class CSipResourceManagerOpeningSipResourcesState;
   friend class CSipResourceManagerStartedState;
   friend class CSipResourceManagerClosingSipResourcesState;
   friend class CSipResourceManagerClosingSipBoardResourceState;
   friend class CSipResourceManagerStoppingSrlEventManagerState;

public:
   virtual ~ASipResourceManager();

   void Start();
   void OnSrlEventManagerStarted( int a_result);
   void OnSipBoardResourceOpened( const ASipBoardResourceSptr& a_sipBoardResource);
   void OnSipResourceOpened( const ASipResourceSptr& a_sipResource);
   void OnStarted( int a_result);
   void EnableInboundCalls();
   void OnCallOffered( const ASipResourceSptr& a_sipResource);
   void OnCallDisconnected( const ASipResourceSptr& a_sipResource);
   void Stop();
   void OnSipResourceClosed( const ASipResourceSptr& a_sipResource);
   void OnSipBoardResourceClosed( const ASipBoardResourceSptr& a_sipBoardResource);
   void OnSrlEventManagerStopped( int a_result);
   void OnStopped( int a_result);

   bool IsStopped();
   bool IsStarted();

   virtual bool SipResourcesPending() = 0;

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

   virtual ASipResourceSptr AllocateSipResource() = 0;
   virtual int AllocateSipResource( ASipResourceSptr a_sipResource) = 0;
   virtual int DeallocateSipResource( ASipResourceSptr a_sipResource) = 0;

protected:
   ASipResourceManager();
   ASipResourceManager( const CTaskProcessorSptr& a_taskProcessor);

   virtual int PrimStartSrlEventManager() = 0;
   virtual int PrimOnSrlEventManagerStarted( int a_result) = 0;
   virtual int PrimOpenSipBoardResource() = 0;
   virtual int PrimOnSipBoardResourceOpened( const ASipBoardResourceSptr& a_sipBoardResource) = 0;
   virtual int PrimOpenSipResources() = 0;
   virtual int PrimOnSipResourceOpened( const ASipResourceSptr& a_sipResource) = 0;
   virtual int PrimOnStarted( int a_result) = 0;
   virtual int PrimEnableInboundCalls() = 0;
   virtual int PrimOnCallOffered( const ASipResourceSptr&  a_sipResource) = 0;
   virtual int PrimOnCallDisconnected( const ASipResourceSptr& a_sipResource) = 0;
   virtual int PrimStopSrlEventManager() = 0;
   virtual int PrimCloseSipResources() = 0;
   virtual int PrimOnSipResourceClosed( const ASipResourceSptr& a_sipResource) = 0;
   virtual int PrimCloseSipBoardResource() = 0;
   virtual int PrimOnSipBoardResourceClosed( const ASipBoardResourceSptr& a_sipBoardResource) = 0;
   virtual int PrimOnSrlEventManagerStopped( int a_result) = 0;
   virtual int PrimOnStopped( int a_result) = 0;

private:
   void BasicStart();
   void BasicOnSrlEventManagerStarted( int a_result);
   void BasicOnSipBoardResourceOpened( const ASipBoardResourceSptr& a_sipBoardResource);
   void BasicOnSipResourceOpened( const ASipResourceSptr& a_sipResource);
   void BasicOnStarted( int a_result);
   void BasicEnableInboundCalls();
   void BasicOnCallOffered( const ASipResourceSptr& a_sipResource);
   void BasicOnCallDisconnected( const ASipResourceSptr& a_sipResource);
   void BasicStop();
   void BasicOnSipResourceClosed( const ASipResourceSptr& a_sipResource);
   void BasicOnSipBoardResourceClosed( const ASipBoardResourceSptr& a_sipBoardResource);
   void BasicOnSrlEventManagerStopped( int a_result);
   void BasicOnStopped( int a_result);

   void SetStateToStopped();
   void SetStateToStartingSrlEventManager();
   void SetStateToOpeningSipBoardResource();
   void SetStateToOpeningSipResources();
   void SetStateToStarted();
   void SetStateToClosingSipResources();
   void SetStateToClosingSipBoardResource();
   void SetStateToStoppingSrlEventManager();

   ASipResourceManagerState* m_state; 
   static CSipResourceManagerStoppedState m_stoppedState; 
   static CSipResourceManagerStartingSrlEventManagerState m_startingSrlEventManagerState; 
   static CSipResourceManagerOpeningSipBoardResourceState m_openingSipBoardResourceState; 
   static CSipResourceManagerOpeningSipResourcesState m_openingSipResourcesState; 
   static CSipResourceManagerStartedState m_startedState; 
   static CSipResourceManagerClosingSipResourcesState m_closingSipResourcesState; 
   static CSipResourceManagerClosingSipBoardResourceState m_closingSipBoardResourceState; 
   static CSipResourceManagerStoppingSrlEventManagerState m_stoppingSrlEventManagerState; 
};

#endif
