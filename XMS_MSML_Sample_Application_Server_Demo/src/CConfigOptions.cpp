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
// File Name: CConfigOptions.cpp
//
// Description: CConfigOptions class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CConfigOptions.h"

#include <vector>
#include <string>

///////////////////////////////////////////////////////////////////////////////
// Function: CConfigOptions::CConfigOptions()
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CConfigOptions::CConfigOptions()
      : m_configFileName( DEFAULT_CONFIG_FILE_NAME)
      , m_maxChannels( DEFAULT_MAX_CHANNELS)
      , m_sipPort( DEFAULT_SIP_PORT)
      , m_appServerAddress( DEFAULT_APP_SERVER_ADDRESS)
      , m_msmlServerAddress( DEFAULT_MSML_SERVER_ADDRESS)
      , m_mediaPathUri( DEFAULT_MEDIA_PATH_URI)
      , m_mediaPathFileUriMapping( DEFAULT_MEDIA_PATH_FILE_URI_MAPPING)
      , m_scriptPathUri( DEFAULT_SCRIPT_PATH_URI)
      , m_initialVideoLayout(1)
      , m_allowedLayoutsCount(1)
      , m_rootSize("CIF")
{   
   m_allowedLayoutsCount = 7;
   m_allowedLayouts[0] = 1;
   m_allowedLayouts[1] = 2;
   m_allowedLayouts[2] = 4;
   m_allowedLayouts[3] = 5;
   m_allowedLayouts[4] = 6;
   m_allowedLayouts[5] = 7;
   m_allowedLayouts[6] = 9;

   for ( int i=0; i<LogObject_MaxTypes; i++)
   {
      m_logLevelByType[i] = LOG_LEVEL_INFO;
   }

}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::Usage()
//
// Description: Output program usage to the console
//
// Return: void
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::Usage()
{
   std::cout << "Usage: app_server <options>" << std::endl
             << "options:" << std::endl
             << "    [-h] [?] - display command line help" << std::endl
             << "    [-maxchan:<max channels>] - maximum number of SIP channels, default: 4"  << std::endl
             << "    [-log:<objectType>=<log level> - set logging levels" << std::endl
             << "          <objectType> = [system | main | eventmgr |" << std::endl
             << "                          resource | resourcemgr |" << std::endl
             << "                          resourcegrp | resourcegrpmgr" << std::endl
             << "                          callflow |callflowmgr]" << std::endl
             << "          <log level> = [debug | info | warn | error>]" << std::endl
             << "    [-port:<sip port>] - sip port, default:5060" << std::endl
             << "    [-app:<uri>] - application server SIP address" << std::endl
             << "                 example: 1234@192.168.1.61, default: 1@localhost" << std::endl
             << "    [-msml:<uri>] - MSML Media Server SIP address" << std::endl
             << "                 example: 5678@192.168.1.51:5070, default: 2@media_server" << std::endl
             << "    [-media:<uri>] - uri for media files from the Media Server(file:// or http://)"
             << "                 default: file:///media" << std::endl
             << "    [-mediafilemap:<path> - local path/dirve mapping to replace file:// if used"  << std::endl
             << "    [-scripts:<uri>] - uri for script files(file:// or http://)"
             << "                 default: file:///scripts" << std::endl
             << "    [-rootsize:<size>] - size of the root video conference window"  << std::endl
             << "                 <size> = 	[SQCIF | QCIF | CIF | QVGA | VGA | 720p | 720p_4x3]"  << std::endl
             << "                 default: CIF" << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConfigOptions::Initialize(int a_argc, char *a_argv[])
//
// Description: Initialize the configuration options from command line 
// parameters
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: int a_argc
//             char *a_argv[]
//
///////////////////////////////////////////////////////////////////////////////
int CConfigOptions::Initialize( int a_argc, char* a_argv[])
{
   std::vector< std::string> l_cmdLineArgs;
   for ( int i = 0; i < a_argc; i++)
   {
      if ( a_argv[i][0] == '?')
      {
         Usage();
         return -1;
      }

      if ( a_argv[i][0] == '-')
      {
         std::string l_arg = &a_argv[i][1];
         if ( l_arg == "?" || l_arg == "h")
         {
            Usage();
            return -1;
         }
         if ( !l_arg.empty())
         {
            m_cmdLineOptions.push_back(l_arg);
         }
      }
   }

   // TODO: add config file command line parameter
   std::ifstream l_configFile( m_configFileName.c_str());
   if (l_configFile)
   {
      char l_configItemBuffer[1024];
      while ( l_configFile.getline( l_configItemBuffer, sizeof(l_configItemBuffer)))
      {
         if ( ( l_configItemBuffer[0] >= ' ') && ( l_configItemBuffer[0] != '#')) 
         {
            m_configFileItems.push_back( l_configItemBuffer);
         }
      }
   }

   SetConfigFromItems( m_configFileItems);

   // Override config file options with command line options
   SetConfigFromItems( m_cmdLineOptions);
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::SetConfigFromItems(std::vector<std::string>&a_configItems)
//
// Description: Set the configuration from a vector of configuration item strings
//
// Return: void
//
// Parameters: std::vector<std::string>&a_configItems
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::SetConfigFromItems( std::vector< std::string>& a_configItems)
{
   std::vector< std::string>::iterator l_configItem;
   for ( l_configItem = a_configItems.begin();
         l_configItem != a_configItems.end();
         ++l_configItem)
   {
      std::string l_val;
      std::string l_key;
      std::string& l_item = *l_configItem;
      unsigned int l_seperatorPos = l_item.find(":");
      if ( l_seperatorPos == l_item.npos)
      {
         l_key = l_item.substr();
      }
      else
      {
         l_val= l_item.substr( l_seperatorPos + 1);
         l_key = l_item.substr( 0, l_seperatorPos);
      }

      // clean up whitespace & non printing
      int l_keyFirstValidPos = l_key.find_first_not_of("\t\r\n ");
      int l_keyLastValidPos = l_key.find_last_not_of("\t\r\n ");
      l_key = l_key.substr( l_keyFirstValidPos, l_keyLastValidPos - l_keyFirstValidPos + 1);

      int l_valFirstValidPos = l_val.find_first_not_of("\t\r\n ");
      int l_valLastValidPos = l_val.find_last_not_of("\t\r\n ");
      l_val = l_val.substr( l_valFirstValidPos, l_valLastValidPos - l_valFirstValidPos + 1);

      if ( l_key == "log")
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

         LogObjectTypeEnum l_objType = CLogger::LogObjectTypeFromString( l_objTypeStr);
         LogLevelEnum l_logLevel = CLogger::LogLevelFromString( l_logLevelStr);
         if ( (l_objType != LogObject_Invalid) && (l_logLevel != LOG_LEVEL_INVALID))
         {
            LogLevel( l_objType, l_logLevel);
         }
      }
      else if ( l_key == "maxchan")
      {
         MaxChannels( atoi( l_val.c_str()));
      }
      else if ( l_key== "port")
      {
         SipPort( atoi( l_val.c_str()));
      }
      else if ( l_key == "msml")
      {
         MsmlServerAddress( l_val);
      }
      else if ( l_key == "app")
      {
         AppServerAddress( l_val);
      }
      else if ( l_key == "media")
      {
         MediaPathUri( l_val);
      }
      else if ( l_key == "mediafilemap")
      {
         MediaPathFileUriMapping( l_val);
      }
      else if ( l_key == "scripts")
      {
         ScriptPathUri( l_val);
      }
	  else if ( l_key == "initiallayout")
      {
         InitialVideoLayout( atoi( l_val.c_str()));
      }
	  else if ( l_key == "layouts")
      {
		  std::string l_layouts = l_val;
		  m_allowedLayoutsCount = sscanf(l_layouts.c_str(), "%d,%d,%d,%d,%d,%d,%d",
			                            &m_allowedLayouts[0],
										&m_allowedLayouts[1],
										&m_allowedLayouts[2],
										&m_allowedLayouts[3],
										&m_allowedLayouts[4],
										&m_allowedLayouts[5],
										&m_allowedLayouts[6]
										);
      }
	  else if ( l_key == "rootsize")
      {
      	if ((l_val == "SQCIF")
      		|| (l_val == "QCIF")
      		|| (l_val == "CIF")
      		|| (l_val == "QVGA")
      		|| (l_val == "VGA")
      		|| (l_val == "720p")
      		|| (l_val == "720p_4x3"))
         RootSize( l_val);
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::LogLevel(LogObjectTypeEnum a_objectType, LogLevelEnum a_logLevel)
//
// Description: Set the LogLevel for a LogObjectType
//
// Return: void
//
// Parameters: LogObjectTypeEnum a_objectType
//             LogLevelEnum a_logLevel
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::LogLevel( LogObjectTypeEnum a_objectType, LogLevelEnum a_logLevel)
{
   if ( a_objectType == LogObject_MaxTypes)
   {
      for ( int i=0; i<LogObject_MaxTypes; i++)
      {
         m_logLevelByType[i] = a_logLevel;
      }
   }
   else
   {
      m_logLevelByType[ a_objectType] = a_logLevel;
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConfigOptions::MaxChannels()
//
// Description: Access the maximum number of channels configuration
//
// Return: int
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CConfigOptions::MaxChannels()
{
   return m_maxChannels;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::MaxChannels(int a_maxChannels)
//
// Description: Set the maximum number of channels configuration
//
// Return: void
//
// Parameters: int a_maxChannels
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::MaxChannels(int a_maxChannels)
{
   m_maxChannels = a_maxChannels;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConfigOptions::SipPort()
//
// Description: Access the SIP port configuration
//
// Return: int
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CConfigOptions::SipPort()
{
   return m_sipPort;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::SipPort(int a_sipPort)
//
// Description: Set the SIP port configuration
//
// Return: void
//
// Parameters: int a_sipPort
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::SipPort( int a_sipPort)
{
   m_sipPort = a_sipPort;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CConfigOptions::MsmlServerAddress()
//
// Description: Access the MSML/MOML Server Address configuration
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CConfigOptions::MsmlServerAddress()
{
   return m_msmlServerAddress;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::MsmlServerAddress(const std::string &a_serverAddress)
//
// Description: Set the MSML/MOML Server Address configuration
//
// Return: void
//
// Parameters: const std::string &a_serverAddress
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::MsmlServerAddress( const std::string& a_serverAddress)
{
   m_msmlServerAddress = a_serverAddress;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CConfigOptions::AppServerAddress()
//
// Description: Access the Application Server (this application) address 
// configuration
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CConfigOptions::AppServerAddress()
{
   return m_appServerAddress;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::AppServerAddress(const std::string &a_serverAddress)
//
// Description: Set the Application Server (this application) address 
// configuration
//
// Return: void
//
// Parameters: const std::string &a_serverAddress
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::AppServerAddress( const std::string& a_serverAddress)
{
   m_appServerAddress = a_serverAddress;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CConfigOptions::MediaPathUri()
//
// Description: Access the media path URI configuration
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CConfigOptions::MediaPathUri()
{
   return m_mediaPathUri;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::MediaPathUri(const std::string &a_mediaPathUri)
//
// Description: Set the media path URI configuration
//
// Return: void
//
// Parameters: const std::string &a_mediaPathUri
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::MediaPathUri( const std::string& a_mediaPathUri)
{
   m_mediaPathUri = a_mediaPathUri;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CConfigOptions::MediaPathFileUriMapping()
//
// Description: Access the media path URI drive/path mapping configuration
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CConfigOptions::MediaPathFileUriMapping()
{
   return m_mediaPathFileUriMapping;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::MediaPathFileUriMapping(const std::string &a_mediaPathFileUriMapping)
//
// Description: Set the media path URI drive/path mapping configuration
//
// Return: void
//
// Parameters: const std::string &a_mediaPathFileUriMapping
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::MediaPathFileUriMapping( const std::string& a_mediaPathFileUriMapping)
{
   m_mediaPathFileUriMapping = a_mediaPathFileUriMapping;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CConfigOptions::ScriptPathUri()
//
// Description: Access the script path URI configuration
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CConfigOptions::ScriptPathUri()
{
   return m_scriptPathUri;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::ScriptPathUri(const std::string &a_mediaPathUri)
//
// Description: Set the script path URI configuration
//
// Return: void
//
// Parameters: const std::string &a_scriptPathUri
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::ScriptPathUri( const std::string& a_scriptPathUri)
{
   m_scriptPathUri = a_scriptPathUri;
}

///////////////////////////////////////////////////////////////////////////////
// Function: LogLevelEnum * CConfigOptions::LogLevels()
//
// Description: Access the log levels configuration
//
// Return: LogLevelEnum *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
LogLevelEnum* CConfigOptions::LogLevels()
{
   return m_logLevelByType;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConfigOptions::InitialVideoLayout()
//
// Description: Access the initial video layout of a video conference
//
// Return: int
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CConfigOptions::InitialVideoLayout()
{
   return m_initialVideoLayout;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::AllowedLayoutsCount(int a_allowedLayoutsCount)
//
// Description: Set the initial layout count
//
// Return: void
//
// Parameters: int a_allowedLayoutsCount
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::AllowedLayoutsCount(int a_allowedLayoutsCount)
{
   m_allowedLayoutsCount = a_allowedLayoutsCount;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConfigOptions::AllowedLayoutsCount()
//
// Description: return the layout count
//
// Return: int
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CConfigOptions::AllowedLayoutsCount()
{
   return m_allowedLayoutsCount;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int* CConfigOptions::AllowedLayouts()
//
// Description: Access the video layouts of a video conference
//
// Return: int*
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int* CConfigOptions::AllowedLayouts()
{
	return m_allowedLayouts;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::InitialVideoLayout(int a_initialVideoLayout)
//
// Description: Set the initial video layout of a video conference
//
// Return: void
//
// Parameters: int a_initialVideoLayout
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::InitialVideoLayout(int a_initialVideoLayout)
{
   m_initialVideoLayout = a_initialVideoLayout;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CConfigOptions::RootSize()
//
// Description: Access the RootSize of a Conference
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CConfigOptions::RootSize()
{
   return m_rootSize;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CConfigOptions::RootSize(const std::string &a_rootSize)
//
// Description: Set the Root Frame size output of VidConf
//
// Return: void
//
// Parameters: const std::string &a_rootSize
//
///////////////////////////////////////////////////////////////////////////////
void CConfigOptions::RootSize( const std::string& a_rootSize)
{
   m_rootSize = a_rootSize;
}
