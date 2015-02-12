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
// File Name: CHttpRequest.cpp
//
// Description: CHttpRequest class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "CHttpRequest.h"
#include "CTask.h"
#include "ATaskHandler.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CHttpRequest::CHttpRequest(const std::string &a_info)
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
CHttpRequest::CHttpRequest( const std::string& a_url, ATaskSptr& a_completionTask, ATaskHandler* a_taskHandler)
   : AHttpRequest( a_url, a_completionTask, a_taskHandler)
{
   curl_easy_setopt( CurlHandle(), CURLOPT_PRIVATE, this);
   curl_easy_setopt( CurlHandle(), CURLOPT_HTTPGET, true);
   curl_easy_setopt( CurlHandle(), CURLOPT_WRITEFUNCTION, &CHttpRequest::WriteCallback);
   curl_easy_setopt( CurlHandle(), CURLOPT_WRITEDATA, this);
}

///////////////////////////////////////////////////////////////////////////////
// Function: CHttpRequest::~CHttpRequest()
//
// Description: Destructor
//
// Return: none
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CHttpRequest::~CHttpRequest()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CHttpRequest::WriteCallback( char* a_data, size_t a_size, size_t a_nmemb, void* a_request)
//
// Description: In progress data write callback
//
// Return: int - number of bytes processed
//
// Parameters: char *a_data
//             size_t a_size
//             size_t a_nmemb
//             void *a_request
//
///////////////////////////////////////////////////////////////////////////////
int CHttpRequest::WriteCallback( char* a_data, size_t a_size, size_t a_nmemb, void* a_request)
{
   CHttpRequest* l_request = reinterpret_cast<CHttpRequest*>(a_request);
   assert(l_request);
   // could get data here using a_data, a_size, a_nmemb
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CHttpRequest::OnCompleted( int a_httpResponse)
//
// Description: Handle HTTP response code when request has completed
//
// Return: none
//
// Parameters: int a_httpResponse
//
///////////////////////////////////////////////////////////////////////////////
void CHttpRequest::OnCompleted( int a_httpResponse)
{
   HttpResponse( a_httpResponse);
   CTask1<int>* l_task = dynamic_cast < CTask1<int>* > (CompletionTask().get());
   assert( l_task);
   ATaskSptr l_newTask( new CTask1<int>( l_task->TaskFunc(), a_httpResponse)); 
   TaskHandler()->QueueTask( l_newTask);
}

