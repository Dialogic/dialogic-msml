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
// File Name: LoggerDefs.h
//
// Description: Log Level and Log Object Type definitions
//
///////////////////////////////////////////////////////////////////////////////
#ifndef LoggerDefs_h
#define LoggerDefs_h

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::LogLevelEnum
//
// Description: Log Levels used for setting the level of a message and the 
// logging threshold for an object
//
///////////////////////////////////////////////////////////////////////////////
typedef enum 
{
   LOG_LEVEL_INVALID = 0,
   LOG_LEVEL_ALWAYS,
   LOG_LEVEL_ERROR,
   LOG_LEVEL_WARNING,
   LOG_LEVEL_INFO,
   LOG_LEVEL_DEBUG,
} LogLevelEnum;

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::LogObjectTypeEnum
//
// Description: Log Object Types that each may have an independent log level 
// threshold settings.
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   LogObject_Invalid = 0,
   LogObject_System,
   LogObject_Resource,
   LogObject_ResourceManager,
   LogObject_ResourceGroup,
   LogObject_ResourceGroupManager,
   LogObject_Callflow,
   LogObject_CallflowManager,
   LogObject_EventManager,
   LogObject_RmcClient,
   LogObject_MaxTypes
} LogObjectTypeEnum;

#endif
