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
// File Name: GlobalCallManagerStates.h
//
// Description: GlobalCall Manager state class declarations
//
///////////////////////////////////////////////////////////////////////////////
#ifndef GlobalCallManagerStates_h
#define GlobalCallManagerStates_h

#include "TypeDefs.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::AGlobalCallManagerState
//
// Description: The abstract GlobalCall Manager State class and all concrete 
// subclasses comprise a State Pattern implementation of the GlobalCall Manager
// state machine.  
//
// The abstract GlobalCall Manager state declares all functions supported by 
// the state machine and implements them as an error.
//
///////////////////////////////////////////////////////////////////////////////
class AGlobalCallManagerState
{
public:
   virtual const char* StateDesc() = 0;
   virtual int Start( AGlobalCallManager& a_globalCallManager);
   virtual int Stop( AGlobalCallManager& a_globalCallManager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CGlobalCallManagerStoppedState
//
// Description: GlobalCall Manager stopped state
//
///////////////////////////////////////////////////////////////////////////////
class CGlobalCallManagerStoppedState : public AGlobalCallManagerState
{
public:
   const char* StateDesc();
   virtual int Start( AGlobalCallManager& a_globalCallManager);
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CGlobalCallManagerStartedState
//
// Description: GlobalCall Manager started state
//
///////////////////////////////////////////////////////////////////////////////
class CGlobalCallManagerStartedState : public AGlobalCallManagerState
{
public:
   const char* StateDesc();
   virtual int Stop( AGlobalCallManager& a_globalCallManager);
};

#endif

