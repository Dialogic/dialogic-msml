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
// File Name: CMsmlResponse.cpp
//
// Description: CMsmlResponse class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CMsmlResponse.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlResponse::CMsmlResponse(const std::string &info)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: const std::string &info
//
///////////////////////////////////////////////////////////////////////////////
CMsmlResponse::CMsmlResponse( const std::string& a_info)
{
   const std::string l_responseCodeLabel = "response=\"";
   unsigned int l_seperatorPos = a_info.find( l_responseCodeLabel);
   if ( l_seperatorPos != a_info.npos)
   {
      m_responseCode = a_info.substr( l_seperatorPos + l_responseCodeLabel.size(), 3);
   }

   const char* l_conferenceIdLabel = "<confid>";
   const char* l_conferenceIdDelim = "</confid>";
   int l_conferenceIdPos = 0;
   l_conferenceIdPos = a_info.find( l_conferenceIdLabel);
   if ( l_conferenceIdPos != a_info.npos)
   {
      l_conferenceIdPos += strlen( l_conferenceIdLabel);
      int l_conferenceIdEndPos = a_info.find( l_conferenceIdDelim, l_conferenceIdPos );
      if ( l_conferenceIdEndPos != a_info.npos)
      {
         m_conferenceId = a_info.substr( l_conferenceIdPos, l_conferenceIdEndPos - l_conferenceIdPos);
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string& CMsmlResponse::ResponseCode()
//
// Description: SIP message respopnse code accessor
//
// Return:      const std::string&
//
// Parameters:
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CMsmlResponse::ResponseCode()
{
   return m_responseCode;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string& CMsmlResponse::ConferenceId()
//
// Description: SIP message respopnse conference ID accessor
//
// Return:      const std::string&
//
// Parameters:
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CMsmlResponse::ConferenceId()
{
   return m_conferenceId;
}
