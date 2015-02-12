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
// File Name: CHttpManager.h
//
// Description: CHttpManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CHttpManager_h
#define CHttpManager_h

#include <boost/thread/mutex.hpp>
#include <curl/curl.h>

#include "AHttpManager.h"
#include "Singleton.h"

#include "gcip.h"
#include "srllib.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::CHttpManager
//
// Description: The HTTP Manager is a singleton responsible for 
// sasynchronously processing HTTP requests.
//
///////////////////////////////////////////////////////////////////////////////
class CHttpManager : public AHttpManager, public Singleton<CHttpManager>
{
   friend class Singleton<CHttpManager>;

public:
   virtual ~CHttpManager();
   const char* ClassName();

   void HttpRequest( AHttpRequestSptr a_httpRequest);

   void TestHttp();
   void OnTestComplete( int l_httpResponse);

private:
   CHttpManager();
   CHttpManager( CTaskProcessorSptr a_taskProcessor);

   CLoggerSptr m_logger;

   int PrimStart();
   int PrimOnStarted( int a_result);
   int PrimStop();
   int PrimOnStopped( int a_result);

   boost::shared_ptr<boost::thread> m_thread;
   void ProcessHttpRequests();

   boost::mutex m_semaphoreMutex;
   boost::condition m_semaphore;
   CURLM* m_multiHandle;
   boost::mutex m_controlMutex;

   AHttpRequestMap m_pendingRequests;
};

#endif
