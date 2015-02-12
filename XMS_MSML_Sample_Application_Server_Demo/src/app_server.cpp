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
// File Name: app_server.cpp
//
// Description: app_server main
//
///////////////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786)

#include <string>
#include <vector>
#include <iostream>

#include "Utility.h"
#include "CConfigOptions.h"
#include "CRemoteMediaControlClient.h"
#include "CLogger.h"

///////////////////////////////////////////////////////////////////////////////
// Function: int ::main(int a_argc, char *a_argv[])
//
// Description: Application main
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_argc
//             char *a_argv[]
//
///////////////////////////////////////////////////////////////////////////////
int main( int a_argc, char* a_argv[])
{
   CConfigOptionsSptr l_config( CConfigOptions::Instance());
   if (l_config->Initialize( a_argc, a_argv) != 0)
   {
      return -1;
   }

   // redirect cerr to file
   // TODO: redirect cerr to CLogger
   std::ofstream l_cerrFile("cerr.txt");
   std::streambuf* l_cerr_buffer = std::cerr.rdbuf();
   std::cerr.rdbuf( l_cerrFile.rdbuf());

   EnableCtrlCHandler();

   boost::shared_ptr< CRemoteMediaControlClient> l_client( new CRemoteMediaControlClient());
   if ( l_client->Start() != 0)
   {
      l_client.reset();
      return 1;
   }

   {
      boost::shared_ptr<CLogger> l_logger( CLogger::Instance());

      while( 1 )
      {
         std::string l_cmdLine;
         int c = getchar();
         while ( c!=10 ) // while not Enter
         {
            if ( g_ctrlCIntercepted)
               break;
            if ( c >= ' ')
               l_cmdLine += c;
            c = getchar();
         }
         if ( g_ctrlCIntercepted)
            break;
         l_logger->Log( LOG_LEVEL_ALWAYS, l_cmdLine);

         std::string l_cmd;
         std::string l_val;
         unsigned int l_seperatorPos = l_cmdLine.find(":");
         if ( l_seperatorPos == l_cmdLine.npos)
         {
            l_cmd = l_cmdLine; 
            // TODO: just get first space delimited cmd
         }
         else
         {
            l_cmd = l_cmdLine.substr( 0, l_cmdLine.find(":"));
            l_val= l_cmdLine.substr( l_cmdLine.find(":") + 1);
            // TODO: clean up leading and trailing whitespace?
         }

         if ( l_cmd == "q" || l_cmd == "quit")
         {
            l_logger->Log( LOG_LEVEL_INFO, "<q>uit command accepted");
            break;            
         }
         else if ( l_cmd == "log")
         {
            std::string l_objTypeStr;
            std::string l_logLevelStr;
            unsigned int l_seperatorPos = l_val.find("=");
            if ( l_seperatorPos == l_val.npos)
            {
               l_objTypeStr = l_val; 
            }
            else
            {
               l_objTypeStr = l_val.substr( 0, l_val.find("="));
               l_logLevelStr= l_val.substr( l_val.find("=") + 1);
            }

            LogObjectTypeEnum l_objType = l_logger->LogObjectTypeFromString( l_objTypeStr);
            LogLevelEnum l_logLevel = l_logger->LogLevelFromString( l_logLevelStr);

            if ( (l_objType != LogObject_Invalid) && (l_logLevel != LOG_LEVEL_INVALID))
            {
               l_logger->LogLevel( l_objType, l_logLevel);
               l_logger->Log( LOG_LEVEL_INFO, "<log:" + l_objTypeStr + "=" + l_logLevelStr + "> command accepted");
            }
            else
            {
               l_logger->Log( LOG_LEVEL_ALWAYS, "error, correct form is log:<objectType>=[debug|warn|info|error]");
            }
         }
         else if (l_cmd == "t")
         {
            l_client->TestHttp();
         }
         else
         {
            l_logger->Log( LOG_LEVEL_ALWAYS, "cmds: <q>uit, log:<objectType>=[debug|warn|info|error]");
         }
      }
   }

   l_client->Stop();

   // undo cerr redirection
   std::cerr << "done." << std::endl;
   std::cerr.rdbuf( l_cerr_buffer);

   return 0;
}
