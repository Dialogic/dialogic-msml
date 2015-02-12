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
// File Name: CHttpManager.cpp
//
// Description: CHttpManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/bind.hpp>

#include "CHttpManager.h"
#include "CHttpRequest.h"
#include "CHttpDelete.h"
#include "CLogger.h"

#include "CConfigOptions.h"

#ifndef _WIN32
#include "devmapr4.h"
#endif

///////////////////////////////////////////////////////////////////////////////
// Function: CHttpManager::CHttpManager()
//
// Description: Default constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CHttpManager::CHttpManager() 
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CHttpManager::CHttpManager(CTaskProcessorSptr a_taskProcessor)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: CTaskProcessorSptr a_taskProcessor
//
///////////////////////////////////////////////////////////////////////////////
CHttpManager::CHttpManager( CTaskProcessorSptr a_taskProcessor) 
   : AHttpManager( a_taskProcessor)
   , m_logger( CLogger::Instance())
{
   Name( "HTTP Manager");
   curl_global_init(CURL_GLOBAL_ALL);
}
///////////////////////////////////////////////////////////////////////////////
// Function: CHttpManager::~CHttpManager()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CHttpManager::~CHttpManager()
{
   curl_global_cleanup();
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CHttpManager::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CHttpManager::ClassName()
{
   return "CHttpManager";
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CHttpManager::PrimStart()
//
// Description: Start an HTTP request processing thread
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CHttpManager::PrimStart()
{
   m_logger->Log( LOG_LEVEL_DEBUG, *this, "PrimStart");
   m_thread = boost::shared_ptr<boost::thread> ( new boost::thread( boost::bind( &CHttpManager::ProcessHttpRequests, this)));
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CHttpManager::PrimOnStarted()
//
// Description: Handle HTTP Manager started event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//             int - a_result
//
///////////////////////////////////////////////////////////////////////////////
int CHttpManager::PrimOnStarted(int a_result)
{
   LogDebugResult("PrimOnStarted", a_result);
   NotifyObservers( HTTP_MANAGER_STARTED, a_result );
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CHttpManager::PrimStop()
//
// Description: Stop the HTTP processing thread
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CHttpManager::PrimStop()
{
   m_logger->Log( LOG_LEVEL_DEBUG, *this, "PrimStop");
   m_semaphore.notify_one();
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CHttpManager::PrimOnStopped( int a_result)
//
// Description: Handle HTTP Manager stopped event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//             int - a_result
//
///////////////////////////////////////////////////////////////////////////////
int CHttpManager::PrimOnStopped(int a_result)
{
   LogDebugResult("PrimOnStopped", a_result);
   NotifyObservers( HTTP_MANAGER_STOPPED, a_result );
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CHttpManager::ProcessHttpRequests()
//
// Description: Process HTTP requests
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void CHttpManager::ProcessHttpRequests()
{
   boost::mutex::scoped_lock l_semaphoreLock( m_semaphoreMutex);
   m_multiHandle = curl_multi_init();
   OnStarted(0);
   while ( !IsStopping() )
   {
      int l_stillWorking(0);
      m_semaphore.wait( l_semaphoreLock);

      { // scope for lock
         boost::mutex::scoped_lock l_controlLock( m_controlMutex);
         while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform(m_multiHandle, &l_stillWorking))
         {
         }
      }
      CURLMcode l_resM;
      int l_selectRc(0);
      while( l_stillWorking && !IsStopping())
      {    
         fd_set l_fdread;
         fd_set l_fdwrite;
         fd_set l_fdexcep;
         int l_maxfd;
      
         FD_ZERO(&l_fdread);
         FD_ZERO(&l_fdwrite);
         FD_ZERO(&l_fdexcep);
      
         struct timeval l_timeout;
         l_timeout.tv_sec = 1;
         l_timeout.tv_usec = 0;

         // get file descriptors from the transfers
         { // scope for lock
            boost::mutex::scoped_lock l_controlLock( m_controlMutex);
            l_resM = curl_multi_fdset( m_multiHandle, &l_fdread, &l_fdwrite, &l_fdexcep, &l_maxfd);
         }
         if (( l_resM == CURLM_OK) && ( l_maxfd != -1))
         {
            l_selectRc = select( l_maxfd+1, &l_fdread, &l_fdwrite, &l_fdexcep, &l_timeout); 

            switch(l_selectRc)
            {
            case -1:
               // select error - what todo ???
               break;
            case 0: // timeout
            default:
               {
                  boost::mutex::scoped_lock l_controlLock( m_controlMutex);
                  while (CURLM_CALL_MULTI_PERFORM == curl_multi_perform( m_multiHandle, &l_stillWorking))
                  {
                  }
                  CURLMsg* l_msg;
                  int l_msgsLeft;
                  while (( l_msg = curl_multi_info_read( m_multiHandle, &l_msgsLeft)))
                  {
                     if ( l_msg->msg == CURLMSG_DONE)
                     {
                        CURL* l_curl = l_msg->easy_handle;
                        long l_httpResponse(0);
                        char* l_context;
                        CURLcode l_res = curl_easy_getinfo( l_curl, CURLINFO_RESPONSE_CODE, &l_httpResponse);
                        l_res = curl_easy_getinfo( l_curl, CURLINFO_PRIVATE, &l_context);
                        m_logger->Log( LOG_LEVEL_DEBUG, *this, "HTTP Result", l_httpResponse);
//                        if ( l_httpResponse >= 400)
//                        {
//                           const char* msg = curl_easy_strerror( l_msg->data.result);
//                           m_logger->Log( LOG_LEVEL_DEBUG, *this, "CURL msg", msg);
//                        }
                        curl_multi_remove_handle( m_multiHandle, l_curl); 
                        AHttpRequestMap::iterator l_pos = m_pendingRequests.find(l_curl);
                        if (l_pos != m_pendingRequests.end())
                        {
                           l_pos->second->OnCompleted(l_httpResponse);
                           m_pendingRequests.erase(l_pos);
                        }
                     }
                  }
               }
               break;
            }
         }
      }
   }

   curl_multi_cleanup( m_multiHandle);
   OnStopped(0);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CHttpManager::HttpRequest( AHttpRequestSptr a_httpRequest)
//
// Description: Start processijng an HTTP request
//
// Return: void
//
// Parameters: AHttpRequestSptr a_httpRequest
//
///////////////////////////////////////////////////////////////////////////////
void CHttpManager::HttpRequest( AHttpRequestSptr a_httpRequest)
{
   m_logger->Log( LOG_LEVEL_DEBUG, *this, a_httpRequest->RequestType() + ":" + a_httpRequest->Url());
   {
      boost::mutex::scoped_lock l_controlLock( m_controlMutex);
      CURLMcode res = curl_multi_add_handle( m_multiHandle, a_httpRequest->CurlHandle());
      m_pendingRequests[a_httpRequest->CurlHandle()] = a_httpRequest;
   }
   m_semaphore.notify_one();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CHttpManager::TestHttp()
//
// Description: Initiate a test HTTP request
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void CHttpManager::TestHttp()
{
   std::string l_script = CConfigOptions::Instance()->MediaPathUri() + "/GoodBye.wav";
   m_logger->Log( LOG_LEVEL_DEBUG, *this, "TestHttp", l_script);
   ATaskSptr l_completionTask( new CTask1<int>( boost::bind( &CHttpManager::OnTestComplete, this, _1),                                                            
                                                              "CHttpManager::OnTestComplete"));
   AHttpRequestSptr l_httpRequest = AHttpRequestSptr( new CHttpRequest( l_script, 
                                                                        l_completionTask, this));
   HttpRequest( l_httpRequest);
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CHttpManager::OnTestComplete( int l_httpResponse)
//
// Description: Handle test HTTP request completion
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void CHttpManager::OnTestComplete( int l_httpResponse)
{
   m_logger->Log( LOG_LEVEL_DEBUG, *this, "OnTestComplete", l_httpResponse);
}

