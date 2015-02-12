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
// File Name: CRemoteMediaControlClient.cpp
//
// Description: CRemoteMediaControlClient class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#include "CRemoteMediaControlClient.h"
#include "CLogger.h"
#include "CTaskProcessor.h"
#include "Utility.h"
#include "CResourceManager.h"
#include "CConfigOptions.h"
#include "CGlobalCallManager.h"
#include "CHttpManager.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CRemoteMediaControlClient::CRemoteMediaControlClient()
//
// Description: Default constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CRemoteMediaControlClient::CRemoteMediaControlClient()
   : ARemoteMediaControlClient()
   , m_resourceManager( CResourceManager::Instance( TaskProcessor()))
   , m_gcManager( CGlobalCallManager::Instance())
   , m_httpManager( CHttpManager::Instance( TaskProcessor()))
{ 
   Name( "RMC Client");
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CRemoteMediaControlClient::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CRemoteMediaControlClient::ClassName()
{
   return "CRemoteMediaControlClient";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CResourceManagerSptr& CRemoteMediaControlClient::ResourceManager()
//
// Description: Access the Resource Manager
//
// Return: CResourceManagerSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CResourceManagerSptr& CRemoteMediaControlClient::ResourceManager()
{
   return m_resourceManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CHttpManagerSptr& CRemoteMediaControlClient::HttpManager()
//
// Description: Access the HTTP Manager
//
// Return: CHttpManagerSptr& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CHttpManagerSptr& CRemoteMediaControlClient::HttpManager()
{
   return m_httpManager;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CRemoteMediaControlClient::~CRemoteMediaControlClient()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CRemoteMediaControlClient::~CRemoteMediaControlClient()
{ 
   Logger()->Stop();
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRemoteMediaControlClient::PrimStart()
//
// Description: Start a TaskProcessor and Logger, register for ResourceManager 
// events and start the Resource Manager, register for GlobalCallManager events 
// and start the GlobalCallManager
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CRemoteMediaControlClient::PrimStart()
{
   LogLevelEnum* l_logLevels = CConfigOptions::Instance()->LogLevels();
   for ( int i=0; i<LogObject_MaxTypes; i++)
   {
      Logger()->LogLevel( (LogObjectTypeEnum) i, l_logLevels[i]);
   }

   if ( Logger()->Start() != 0)
   {
      std::cout << std::endl << std::endl << "Error starting CLogger." << std::endl << std::endl;
      return -1;
   }

   if ( TaskProcessor()->Start() != 0)
   {
      std::cout << std::endl << std::endl << "Error starting CTaskProcessor." << std::endl << std::endl;
      return -1;
   }

   int l_tryCount(0);
   while ( !Logger()->IsRunning() || !TaskProcessor()->IsRunning())
   {
      MsSleep( 500);
      if ( ++l_tryCount >= 20)
      {
         std::cout << std::endl << std::endl << "Timeout waiting for Logger and Task Processor to start" << std::endl << std::endl;
         return -1;
      }
      if (!Logger()->IsRunning() || !TaskProcessor()->IsRunning())
         Logger()->Log( LOG_LEVEL_ALWAYS, *this, "PrimStart", ".");
   }

   Logger()->Log( LOG_LEVEL_DEBUG, *this, "PrimStart", "Logger and Task processor started");

   ATaskSptr l_resourceManagerStartedTask( new CTask1<int>(
                                             boost::bind( &CRemoteMediaControlClient::OnResourceManagerStarted, this, _1),
                                             "CRemoteMediaControlClient::OnResourceManagerStarted"));
   ResourceManager()->RegisterForNotification(  this, l_resourceManagerStartedTask, RESOURCE_MANAGER_STARTED);

   ATaskSptr l_resourceManagerStoppedTask( new CTask1<int>(
                                             boost::bind( &CRemoteMediaControlClient::OnResourceManagerStopped, this, _1),
                                             "CRemoteMediaControlClient::OnResourceManagerStopped"));
   ResourceManager()->RegisterForNotification(  this, l_resourceManagerStoppedTask, RESOURCE_MANAGER_STOPPED);

   ATaskSptr l_httpManagerStartedTask( new CTask1<int>(
                                             boost::bind( &CRemoteMediaControlClient::OnHttpManagerStarted, this, _1),
                                             "CRemoteMediaControlClient::OnHttpManagerStarted"));
   HttpManager()->RegisterForNotification(  this, l_httpManagerStartedTask, HTTP_MANAGER_STARTED);

   ATaskSptr l_httpManagerStoppedTask( new CTask1<int>(
                                             boost::bind( &CRemoteMediaControlClient::OnHttpManagerStopped, this, _1),
                                             "CRemoteMediaControlClient::OnHttpManagerStopped"));
   HttpManager()->RegisterForNotification(  this, l_httpManagerStoppedTask, HTTP_MANAGER_STOPPED);

   m_gcManager->Start();

   HttpManager()->Start();

   ResourceManager()->Start();

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRemoteMediaControlClient::PrimOnManagersStarted(int a_result)
//
// Description: All managers hacve started
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRemoteMediaControlClient::PrimOnManagersStarted( int a_result)
{
   LogDebugResult( "OnManagersStarted", a_result);

   ATaskSptr l_task( new CTask1<int>( boost::bind( &ARemoteMediaControlClient::OnStartup, this, _1),
                                                   a_result,
                                                   "ARemoteMediaControlClient::OnStartup"));
   TaskProcessor()->QueueTask( l_task);

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRemoteMediaControlClient::PrimOnStartup(int a_result)
//
// Description: Handle started completion event
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRemoteMediaControlClient::PrimOnStartup( int a_result)
{
   std::string l_tempMsg( "Remote Media Control Client started: " + AsString( a_result));
   Logger()->Log( LOG_LEVEL_ALWAYS, *this, "PrimOnStartup", l_tempMsg);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRemoteMediaControlClient::PrimStop()
//
// Description: Stop the ResourceManager and TaskProcessor
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CRemoteMediaControlClient::PrimStop()
{
   Logger()->Log( LOG_LEVEL_ALWAYS, *this, "PrimStop", "Remote Media Control Client stopping");

   int l_tryCount;

   HttpManager()->Stop();
   l_tryCount = 0;
   while ( !HttpManager()->IsStopped())
   {
      MsSleep( 500);

      if ( ++l_tryCount >= 100)
      {
         std::cout << std::endl << std::endl << "Timeout waiting for HTTP Manager to stop" << std::endl << std::endl;
         return -1;
      }
   }

   ResourceManager()->Stop();
   l_tryCount = 0;
   while ( !ResourceManager()->IsStopped())
   {
      MsSleep( 500);

      if ( ++l_tryCount >= 100)
      {
         std::cout << std::endl << std::endl << "Timeout waiting for Resource Manager to stop" << std::endl << std::endl;
         return -1;
      }
   }

   m_gcManager->Stop();

   if ( TaskProcessor()->Stop() != 0)
   {
      std::cout << std::endl << std::endl << "Error stopping CTaskProcessor." << std::endl << std::endl;
   }

   if ( Logger()->Stop() != 0)
   {
      std::cout << std::endl << std::endl << "Error stopping CLogger." << std::endl << std::endl;
      return -1;
   }

   l_tryCount = 0;
   while ( Logger()->IsRunning() || TaskProcessor()->IsRunning())
   {
      MsSleep( 100);

      if ( ++l_tryCount >= 100)
      {
         std::cout << std::endl << std::endl << "Timeout waiting for Logger and TaskProcessor to stop" << std::endl << std::endl;
         return -1;
      }
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CRemoteMediaControlClient::PrimOnManagersStopped(int a_result)
//
// Description: All managers have stopped
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_result
//
///////////////////////////////////////////////////////////////////////////////
int CRemoteMediaControlClient::PrimOnManagersStopped( int a_result)
{
   LogDebugResult( "OnManagersStopped()", a_result);
   return 0;
}


///////////////////////////////////////////////////////////////////////////////
// Function: void CRemoteMediaControlClient::TestHttp()
//
// Description: Test the http manager
//
// Return: none
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void CRemoteMediaControlClient::TestHttp()
{
   HttpManager()->TestHttp();
}

