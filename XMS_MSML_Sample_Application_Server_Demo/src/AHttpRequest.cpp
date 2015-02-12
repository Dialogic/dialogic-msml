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
// File Name: AHttpRequest.cpp
//
// Description: AHttpRequest class implementation
//
///////////////////////////////////////////////////////////////////////////////

#include "AHttpRequest.h"
#include "CTask.h"
#include "ATaskHandler.h"

///////////////////////////////////////////////////////////////////////////////
// Function: AHttpRequest::AHttpRequest(const std::string &a_info)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: const std::string &a_info
//             ATaskSptr &a_completionTask
//             ATaskHandler *a_taskHandler
//
///////////////////////////////////////////////////////////////////////////////
AHttpRequest::AHttpRequest( const std::string& a_url, ATaskSptr& a_completionTask, ATaskHandler* a_taskHandler)
   :m_curlHandle(0)
   , m_url(a_url)
   , m_completionTask( a_completionTask)
   , m_taskHandler( a_taskHandler)
   , m_httpResponse( 0)
{
   m_requestType = "GET";
   m_curlHandle = curl_easy_init();
   curl_easy_setopt( m_curlHandle, CURLOPT_VERBOSE, 0);
   curl_easy_setopt( m_curlHandle, CURLOPT_NOSIGNAL, 1L);
   curl_easy_setopt( CurlHandle(), CURLOPT_CONNECTTIMEOUT, 5);
   curl_easy_setopt( m_curlHandle, CURLOPT_URL, m_url.c_str());
}

///////////////////////////////////////////////////////////////////////////////
// Function: AHttpRequest::~AHttpRequest()
//
// Description: Destructor
//
// Return: none
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
AHttpRequest::~AHttpRequest()
{
   curl_easy_cleanup( m_curlHandle);
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & AHttpRequest::Url()
//
// Description: Access the URL
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& AHttpRequest::Url()
{
   return m_url;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & AHttpRequest::RequestType()
//
// Description: Access the request type
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& AHttpRequest::RequestType()
{
   return m_requestType;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & AHttpRequest::CurlHandle()
//
// Description: Access the value of the Curl handle
//
// Return: CURL*
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CURL* AHttpRequest::CurlHandle()
{
   return m_curlHandle;
}

///////////////////////////////////////////////////////////////////////////////
// Function: ATaskSptr& AHttpRequest::CompletionTask()
//
// Description: Access the completion task
//
// Return: ATaskSptr&
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ATaskSptr& AHttpRequest::CompletionTask()
{
   return m_completionTask;
}

///////////////////////////////////////////////////////////////////////////////
// Function: ATaskHandler* AHttpRequest::TaskHandler()
//
// Description: Access the task handler tor the completion task
//
// Return: ATaskSptr&
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
ATaskHandler* AHttpRequest::TaskHandler()
{
   return m_taskHandler;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int AHttpRequest::HttpResponse()
//
// Description: Access the HTTP response code
//
// Return: int
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int AHttpRequest::HttpResponse()
{
   return m_httpResponse;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void AHttpRequest::HttpResponse( int a_httpResponse)
//
// Description: Set the HTTP response code
//
// Return: none
//
// Parameters: int a_httpResponse
//
///////////////////////////////////////////////////////////////////////////////
void AHttpRequest::HttpResponse( int a_httpResponse)
{
   m_httpResponse = a_httpResponse;
}
