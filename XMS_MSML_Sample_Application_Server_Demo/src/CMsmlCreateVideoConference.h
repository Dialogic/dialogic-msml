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
// File Name: CMsmlCreateVideoConference.h
//
// Description: CMsmlCreateVideoConference class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CMsmlCreateVideoConference_h
#define CMsmlCreateVideoConference_h

#include "ADialog.h"
#include "Utility.h"
#include <string>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CMsmlCreateVideoConference
//
// Description: The MSML Dialog class is responsible for formatting the xml 
// required to create a video/multimedia conference.
//
///////////////////////////////////////////////////////////////////////////////
class CMsmlCreateVideoConference : public ADialog
{
public:
   CMsmlCreateVideoConference(int a_layout, const std::string& a_rootSize);
   ~CMsmlCreateVideoConference();
private:
	void MsmlCreate1PartyVideoConference(const std::string& a_rootSize);
	void MsmlCreate2PartyVideoConference(const std::string& a_rootSize);
	void MsmlCreate4PartyVideoConference(const std::string& a_rootSize);
	void MsmlCreate5PartyVideoConference(const std::string& a_rootSize);
	void MsmlCreate6PartyVideoConference(const std::string& a_rootSize);
	void MsmlCreate7PartyVideoConference(const std::string& a_rootSize);
	void MsmlCreate9PartyVideoConference(const std::string& a_rootSize);
};

#endif

