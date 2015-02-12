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
// File Name: CSipResourceManager.h
//
// Description: CSipResourceManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CSipResourceManager_h
#define CSipResourceManager_h

#include "TypeDefs.h"
#include "ASipResourceManager.h"
#include "Singleton.h"

#include <map>
#include <set>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipResourceManager
//
// Description: The SIP Resource Manager is responsible for opening/closing SIP
// Resource objects, enabling inbound calls and detecting offered calls.
//
///////////////////////////////////////////////////////////////////////////////
class CSipResourceManager : public ASipResourceManager, public Singleton<CSipResourceManager>
{
   friend class Singleton<CSipResourceManager>;

public:
   virtual ~CSipResourceManager();

   const char* ClassName();
   CSrlEventManagerSptr SrlEventManager();
   bool SipResourcesPending();

   ASipResourceSptr AllocateSipResource();
   int AllocateSipResource( ASipResourceSptr a_sipResource);
   int DeallocateSipResource( ASipResourceSptr a_sipResource);

private:
   CSipResourceManager();
   CSipResourceManager( CTaskProcessorSptr a_taskProcessor);

   CSrlEventManagerSptr m_srlEventManager;

   CSipBoardResourceSptr m_sipBoardResource;

   std::map< long, ASipResourceSptr > m_sipResources;
   std::set< ASipResourceSptr > m_pendingSipResources;
   std::set< ASipResourceSptr > m_unallocatedSipResources;
   std::set< ASipResourceSptr > m_allocatedSipResources;

   int PrimStartSrlEventManager();
   int PrimOnSrlEventManagerStarted( int a_result);
   int PrimOpenSipBoardResource();
   int PrimOnSipBoardResourceOpened( const ASipBoardResourceSptr& a_sipBoardResource);
   int PrimOpenSipResources();
   int PrimOnSipResourceOpened( const ASipResourceSptr& a_sipResource);
   int PrimOnStarted( int a_result);
   int PrimEnableInboundCalls();
   int PrimOnCallOffered( const ASipResourceSptr& a_sipResource);
   int PrimOnCallDisconnected( const ASipResourceSptr& a_sipResource);
   int PrimCloseSipResources();
   int PrimOnSipResourceClosed( const ASipResourceSptr& a_sipResource);
   int PrimCloseSipBoardResource();
   int PrimOnSipBoardResourceClosed( const ASipBoardResourceSptr& a_sipBoardResource);
   int PrimStopSrlEventManager();
   int PrimOnSrlEventManagerStopped( int a_result);
   int PrimOnStopped( int a_result);
};

#endif
