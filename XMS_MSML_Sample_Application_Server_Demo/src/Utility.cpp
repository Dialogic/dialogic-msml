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
// File Name: Utility.cpp
//
// Description: Implementation of Utility functions
//
///////////////////////////////////////////////////////////////////////////////
#include "Utility.h"
#include "CConfigOptions.h"

#include <signal.h>

#ifdef _WIN32

#include <windows.h>

#else

#include <unistd.h>
#include <pthread.h>

#endif

///////////////////////////////////////////////////////////////////////////////
// Function: void ::MsSleep(unsigned int a_millisecs)
//
// Description: Operating System independent sleep function
//
// Return: void
//
// Parameters: unsigned int a_millisecs
//
///////////////////////////////////////////////////////////////////////////////
void MsSleep( unsigned int a_millisecs) 
{                       

#ifdef _WIN32

   Sleep( a_millisecs);     

#else

   usleep( a_millisecs * 1000);     

#endif
}

///////////////////////////////////////////////////////////////////////////////
// Function: unsigned long ::ThreadID()
//
// Description: Operating System independent thread ID accessor
//
// Return: unsigned long
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
unsigned long ThreadID()
{
#ifdef _WIN32
   return GetCurrentThreadId();
#else
   return pthread_self();
#endif

}

/* Gobal */
bool g_ctrlCIntercepted = false;

#ifdef _WIN32

///////////////////////////////////////////////////////////////////////////////
// Function: void ::GotCtrlC(int)
//
// Description: Operating System independent Ctrl-C handler
//
// Return: void
//
// Parameters: int
//
///////////////////////////////////////////////////////////////////////////////
void GotCtrlC( int)

#else

void GotCtrlC( int )

#endif

{
   g_ctrlCIntercepted = true; 
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ::EnableCtrlCHandler(void)
//
// Description: 
//
// Return: void
//
// Parameters: void
//
///////////////////////////////////////////////////////////////////////////////
void EnableCtrlCHandler( void)
{

#ifdef _WIN32

   signal( SIGINT, (void (__cdecl*)(int)) GotCtrlC);
   signal( SIGTERM, (void (__cdecl*)(int)) GotCtrlC);

#else

   signal( SIGHUP,  GotCtrlC);
   signal( SIGQUIT, GotCtrlC);
   signal( SIGINT, GotCtrlC);
   signal( SIGTERM, GotCtrlC);

#endif
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ::MakeMailboxUri(std::string &a_mailboxFilePath, const std::string &a_mailboxName, bool a_videoIsActive)
//
// Description: Operating System independent Mailbox URI composer
//
// Return: void
//
// Parameters: std::string &a_mailboxUri
//             const std::string &a_mailboxName
//             bool a_videoIsActive
//
///////////////////////////////////////////////////////////////////////////////
void MakeMailboxUri( std::string& a_mailboxUri, 
                     const std::string& a_mailboxName, 
                     bool a_videoIsActive)
{

#ifdef _WIN32

   a_mailboxUri = CConfigOptions::Instance()->MediaPathUri() + "\\Mailbox_" + a_mailboxName;

#else

   a_mailboxUri = CConfigOptions::Instance()->MediaPathUri() + "/Mailbox_" + a_mailboxName;

#endif

   if ( a_videoIsActive)
   {
      a_mailboxUri += ".vid";
   }
   else
   {
      a_mailboxUri += ".wav";
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ::MakeScriptUri(std::string &a_scriptUri, const std::string &a_scritpName)
//
// Description: Operating System independent script URIcomposer
//
// Return: void
//
// Parameters: std::string &a_scriptUri
//             const std::string &a_scriptName
//
///////////////////////////////////////////////////////////////////////////////
void MakeScriptUri(  std::string& a_scriptUri, 
                     const std::string& a_scriptName)
{
   a_scriptUri = CConfigOptions::Instance()->ScriptPathUri() + "/" + a_scriptName;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void ::MakeMediaFilePath( std::string& l_fileUri)
//
// Description: Make the given URI into a file path
//
// Return: void
//
// Parameters: std::string &a_fileUri
//
///////////////////////////////////////////////////////////////////////////////
void MakeMediaFilePath( std::string& l_fileUri)
{
   const std::string fileDescriptor("file://");
   if ( l_fileUri.find(fileDescriptor) != std::string::npos)
   {
      l_fileUri = CConfigOptions::Instance()->MediaPathFileUriMapping() + l_fileUri.substr(fileDescriptor.size());
   }
}

