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
// File Name: AHttpRequest.h
//
// Description: AHttpRequest class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef AHttpRequest_h
#define AHttpRequest_h

#include "TypeDefs.h"

#include <string>
#include <map>

#include <curl/curl.h>

///////////////////////////////////////////////////////////////////////////////
// Class: ::AHttpRequest
//
// Description: Abstract class is responsible for wrapping an HTTP request.
//
///////////////////////////////////////////////////////////////////////////////
class AHttpRequest
{
public:
   AHttpRequest( const std::string& a_url, ATaskSptr& a_taskSptr, ATaskHandler* a_taskHandler);
   virtual ~AHttpRequest();

   const std::string& Url();
   CURL* CurlHandle();

   int HttpResponse();
   void HttpResponse( int a_httpResponse);

   virtual void OnCompleted( int a_httpResponse) = 0;

   const std::string& RequestType();

protected:
   ATaskHandler* TaskHandler();
   ATaskSptr& CompletionTask();
   std::string m_requestType;

private:
   std::string m_url;
   CURL* m_curlHandle;
   ATaskSptr m_completionTask;
   ATaskHandler* m_taskHandler;
   int m_httpResponse;

   AHttpRequest();
};

#endif
