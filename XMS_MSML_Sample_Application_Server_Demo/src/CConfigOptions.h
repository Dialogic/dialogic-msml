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
// File Name: CConfigOptions.h
//
// Description: CConfigOptions class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CConfigOptions_h
#define CConfigOptions_h

#include "Singleton.h"
#include "CLogger.h"

#include <string>
#include <vector>

const std::string DEFAULT_CONFIG_FILE_NAME = "app_server.cfg";
const LogLevelEnum DEFAULT_LOG_LEVEL = LOG_LEVEL_DEBUG;
const int DEFAULT_MAX_CHANNELS = 4;
const int DEFAULT_SIP_PORT = 5060;
const std::string DEFAULT_APP_SERVER_ADDRESS = "1@localhost:5060";
const std::string DEFAULT_MSML_SERVER_ADDRESS = "2@media_server:5060";
const std::string DEFAULT_MEDIA_PATH_URI = "file:///media";
const std::string DEFAULT_MEDIA_PATH_FILE_URI_MAPPING = "/xms";
const std::string DEFAULT_SCRIPT_PATH_URI = "file:///scripts";
const int DEFAULT_MAX_ALLOWED_LAYOUT = 7;

///////////////////////////////////////////////////////////////////////////////
// Class: ::CConfigOptions
//
// Description: The singletoin Configuration Options class is responsible for 
// parsing configurations from command line variables and a configuration file,
// and storing the configurations for global use.
//
///////////////////////////////////////////////////////////////////////////////
class CConfigOptions : public Singleton<CConfigOptions>
{
   friend class Singleton< CConfigOptions>;

public:
   virtual ~CConfigOptions() {}

   int Initialize( int a_argc, char* a_argv[]);

   int MaxChannels();
   void MaxChannels( int a_maxChannels);

   int SipPort();
   void SipPort( int a_sipPort);

   const std::string& MsmlServerAddress();
   void MsmlServerAddress( const std::string& a_serverAddress);

   const std::string& AppServerAddress();
   void AppServerAddress( const std::string& a_serverAddress);

   const std::string& MediaPathUri();
   void MediaPathUri( const std::string& a_mediaPathUri);

   const std::string& MediaPathFileUriMapping();
   void MediaPathFileUriMapping( const std::string& a_mediaPathFileUriMapping);

   const std::string& ScriptPathUri();
   void ScriptPathUri( const std::string& a_scriptPathUri);

   LogLevelEnum* LogLevels();
   void LogLevel( LogObjectTypeEnum a_objectType, LogLevelEnum a_logLevel);

   int InitialVideoLayout();
   void InitialVideoLayout( int a_initialVideoLayout);
   int* AllowedLayouts();
   int AllowedLayoutsCount();
   void AllowedLayoutsCount(int a_allowedLayoutsCount);
   const std::string& RootSize();
   void RootSize(const std::string& a_RootSize);

private:
   CConfigOptions();

   std::string m_configFileName;
   int m_maxChannels;
   int m_sipPort;
   std::string m_appServerAddress;
   std::string m_msmlServerAddress;
   std::string m_mediaPathUri;
   std::string m_mediaPathFileUriMapping;
   std::string m_scriptPathUri;

   int m_initialVideoLayout; 
   int m_allowedLayoutsCount; 
   int m_allowedLayouts[DEFAULT_MAX_ALLOWED_LAYOUT];
   std::string m_rootSize;

   std::vector< std::string> m_configFileItems;
   std::vector< std::string> m_cmdLineOptions;

   void Usage();
   void SetConfigFromItems( std::vector< std::string>& a_configItems);
   LogLevelEnum m_logLevelByType[LogObject_MaxTypes];

};

#endif
