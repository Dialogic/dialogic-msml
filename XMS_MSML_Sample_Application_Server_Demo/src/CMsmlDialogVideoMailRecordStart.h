///////////////////////////////////////////////////////////////////////////////
//
// Copyright � 2006-2012 Dialogic Inc. All Rights Reserved.
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
// File Name: CMsmlDialogVideoMailRecordStart.h
//
// Description: CMsmlDialogVideoMailRecordStart class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CMsmlDialogVideoMailRecordStart_h
#define CMsmlDialogVideoMailRecordStart_h

#include "ADialog.h"

#include <string>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CMsmlDialogVideoMailRecordStart
//
// Description: The MSML Video Mail Start Record Dialog class is responsible for 
// formatting the xml required for a dialog to start recording a video message.
//
///////////////////////////////////////////////////////////////////////////////
class CMsmlDialogVideoMailRecordStart : public ADialog
{
public:
   CMsmlDialogVideoMailRecordStart( const std::string& a_connectionId, const std::string& a_mailbox);
};

#endif

