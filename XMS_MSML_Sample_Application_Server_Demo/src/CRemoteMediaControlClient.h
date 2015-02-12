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
// File Name: CRemoteMediaControlClient.h
//
// Description: CRemoteMediaControlClient class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CRemoteMediaControlClient_h
#define CRemoteMediaControlClient_h

#include "TypeDefs.h"
#include "ARemoteMediaControlClient.h"

#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CRemoteMediaControlClient
//
// Description: The Remote Media Client is responsible for starting the 
// application logger, task processor and resource manger.
//
///////////////////////////////////////////////////////////////////////////////
class CRemoteMediaControlClient : public ARemoteMediaControlClient
{
public:
   CRemoteMediaControlClient();
   virtual ~CRemoteMediaControlClient();

   const char* ClassName();

   CResourceManagerSptr& ResourceManager();
   CHttpManagerSptr& HttpManager();

   void TestHttp();

private:
   CResourceManagerSptr m_resourceManager;
   CGlobalCallManagerSptr m_gcManager;
   CHttpManagerSptr m_httpManager;

   int PrimStart();
   int PrimOnManagersStarted( int a_result);
   int PrimOnStartup( int a_result);
   int PrimStop();
   int PrimOnManagersStopped( int a_result);
};

#endif
