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
// File Name: AGlobalCallManager.h
//
// Description: AGlobalCallManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef AGlobalCallManager_h
#define AGlobalCallManager_h

#include "GlobalCallManagerStates.h"
#include "LoggerDefs.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::AGlobalCallManager
//
// Description: The abstract GlobalCall Manager class implements the public 
// interface and state machine for the concrete GlobalCall Manager class.  
// The GlobalCall Manager is a singleton responsible for starting and stopping 
// GlobalCall and discovering available GC resopurces.
//
///////////////////////////////////////////////////////////////////////////////
class AGlobalCallManager
{
   friend class AGlobalCallManagerState;
   friend class CGlobalCallManagerStoppedState;
   friend class CGlobalCallManagerStartedState;

public:
   virtual ~AGlobalCallManager();

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

   int Start();
   int Stop();

protected:
   AGlobalCallManager();

   virtual int PrimStart() = 0;
   virtual int PrimStop() = 0;

private:
   void SetStateToStarted();
   void SetStateToStopped();

   AGlobalCallManagerState* m_state;
   static CGlobalCallManagerStoppedState m_stoppedState;
   static CGlobalCallManagerStartedState m_startedState;
};

#endif

