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
// File Name: Utility.h
//
// Description: Utility and Operating System dependent functions
//
///////////////////////////////////////////////////////////////////////////////
#ifndef Utility_h
#define Utility_h

#include <string>

#define SUCCESS 0

template< typename T>
std::string AsString( T a_value);

template< typename T>
std::string AsHexString( T a_value, int a_width = 4);

void MsSleep( unsigned int a_millisecs);
unsigned long ThreadID();

extern bool g_ctrlCIntercepted;
void EnableCtrlCHandler( void);

void MakeMailboxUri( std::string& a_mailboxUri, 
                     const std::string& a_mailboxName, 
                     bool a_videoIsActive);

void MakeScriptUri(  std::string& a_scriptUri, 
                     const std::string& a_scriptName);

void MakeMediaFilePath( std::string& l_fileUri);

#include "Utility_imp.h"

#endif
