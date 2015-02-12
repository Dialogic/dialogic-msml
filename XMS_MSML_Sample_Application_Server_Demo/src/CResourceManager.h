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
// File Name: CResourceManager.h
//
// Description: CResourceManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CResourceManager_h
#define CResourceManager_h

#include "TypeDefs.h"
#include "AResourceManager.h"

#include <list>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceManager
//
// Description: The Resource Manager is responsible for starting and stopping 
// other managers, obtaining Resource Group and Callflow objects in response 
// to an inbouind call, and freeing resource at the end of a call.
//
///////////////////////////////////////////////////////////////////////////////
class CResourceManager : public AResourceManager, public Singleton<CResourceManager>
{
   friend class Singleton<CResourceManager>;
   friend class CResourceManagerStartingState;

public:
   virtual ~CResourceManager();

   CCallflowManagerSptr& CallflowManager();
   CResourceGroupManagerSptr& ResourceGroupManager();
   CSipResourceManagerSptr& SipResourceManager();

   const char* ClassName();

   void ExceptionTest();

private:
   CResourceManager();
   CResourceManager( CTaskProcessorSptr a_taskProcessor);

   CCallflowManagerSptr m_callflowManager;
   CSipResourceManagerSptr m_sipResourceManager;
   CResourceGroupManagerSptr m_resourceGroupManager;

   int PrimStart();
   int PrimOnCallflowManagerStarted( int a_result);
   int PrimOnResourceGroupManagerStarted( int a_result);
   int PrimOnSipResourceManagerStarted( int a_result);
   int PrimOnStarted( int a_result);
   int PrimOnCallOffered( const ASipResourceSptr& a_sipResource);
   int PrimOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup);
   int PrimOnResourceGroupReset( AResourceGroupSptr a_resourceGroup);
   int PrimOnCallflowAvailable( ACallflowSptr a_callflow);
   int PrimOnCallflowReset( ACallflowSptr a_callflow);
   int PrimOnCallDisconnected( const ASipResourceSptr& a_sipResource);
   int PrimStop();
   int PrimOnCallflowManagerStopped( int a_result);
   int PrimOnResourceGroupManagerStopped( int a_result);
   int PrimOnSipResourceManagerStopped( int a_result);
   int PrimOnStopped( int a_result);

///////////////////////////////////////////////////////////////////////////////
// Class: CResourceManager::CStartedResources
//
// Description: 
//
///////////////////////////////////////////////////////////////////////////////
   class CStartedResources
   {
   public: 
      CStartedResources() : m_callflowManager(false), m_resourceGroupManager(false), m_sipResourceManager(false) {}
      bool CallflowManager() { return m_callflowManager;}
      void CallflowManager( bool flag) { m_callflowManager = flag;}
      bool ResourceGroupManager() { return m_resourceGroupManager;}
      void ResourceGroupManager( bool flag) { m_resourceGroupManager = flag;}
      bool SipResourceManager() { return m_sipResourceManager;}
      void SipResourceManager( bool flag) { m_sipResourceManager = flag;}
      bool AllResourcesStarted() { return m_callflowManager && m_resourceGroupManager && m_sipResourceManager;}
      bool AllResourcesStopped() { return ! (m_callflowManager || m_resourceGroupManager || m_sipResourceManager);}
   private:
      bool m_callflowManager;
      bool m_resourceGroupManager;
      bool m_sipResourceManager;
   } m_startedResources;
};

#endif
