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
// File Name: CResourceGroupManager.h
//
// Description: CResourceGroupManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CResourceGroupManager_h
#define CResourceGroupManager_h

#include "TypeDefs.h"
#include "AResourceGroupManager.h"
#include "Singleton.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::CResourceGroupManager
//
// Description: The Resource Group Manager is responsible for managing Resource
// Group objects
//
///////////////////////////////////////////////////////////////////////////////
class CResourceGroupManager : public AResourceGroupManager, public Singleton<CResourceGroupManager>
{
   friend class Singleton<CResourceGroupManager>;

public:
   virtual ~CResourceGroupManager();
   const char* ClassName();

   AResourceGroupSptr FindResourceGroup( ASipResourceSptr a_sipResource);

   CSipResourceManagerSptr SipResourceManager();

private:
   CResourceGroupManager();
   CResourceGroupManager( CTaskProcessorSptr a_taskProcessor);
   
   int PrimStart();
   int PrimOnStarted( int a_result);
   int PrimGetResourceGroup( ASipResourceSptr a_inboundSipResource);
   int PrimOnResourceGroupAvailable( AResourceGroupSptr a_resourceGroup);
   int PrimResetResourceGroup( AResourceGroupSptr a_resourceGroup);
   int PrimOnResourceGroupReset( AResourceGroupSptr a_resourceGroup);
   int PrimStop();
   int PrimOnStopped( int a_result);

   std::list< AResourceGroupSptr > m_resourceGroups;
};

#endif
