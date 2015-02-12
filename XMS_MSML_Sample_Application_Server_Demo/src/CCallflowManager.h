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
// File Name: CCallflowManager.h
//
// Description: CCallflowManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CCallflowManager_h
#define CCallflowManager_h

#include <list>

#include "TypeDefs.h"
#include "ACallflowManager.h"

class ACallflow;

///////////////////////////////////////////////////////////////////////////////
// Class: ::CCallflowManager
//
// Description: The Callflow Manager is responsible for managing instances of
// Callflow objects
//
///////////////////////////////////////////////////////////////////////////////
class CCallflowManager : public ACallflowManager, public Singleton<CCallflowManager>
{
   friend class Singleton<CCallflowManager>;

public:
   virtual ~CCallflowManager();
   const char* ClassName();

   ACallflowSptr FindCallflow( AResourceGroupSptr a_resourceGroup);

private:
   CCallflowManager();
   CCallflowManager( CTaskProcessorSptr a_taskProcessor);

   int PrimStart();
   int PrimOnStarted( int a_result);
   int PrimGetCallflow( AResourceGroupSptr a_resourceGroup);
   int PrimResetCallflow( ACallflowSptr a_callflow);
   int PrimStop();
   int PrimOnStopped( int a_result);

   std::list< ACallflowSptr > m_callflows;
};

#endif
