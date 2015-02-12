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
// File Name: CMsmlDialogVideoMailPlay.cpp
//
// Description: CMsmlDialogVideoMailPlay class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CMsmlDialogVideoMailPlay.h"
#include "CConfigOptions.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlDialogVideoMailPlay::CMsmlDialogVideoMailPlay(const std::string &a_connectionId, const std::string &a_mailbox)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: const std::string &a_connectionId
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
CMsmlDialogVideoMailPlay::CMsmlDialogVideoMailPlay( 
         const std::string& a_connectionId,
         const std::string& a_mailbox)
{
   std::string l_mediaPath = CConfigOptions::Instance()->MediaPathUri();

   m_contentType = "Content-Type: application/xml";
   m_content = "\
<msml version=\"1.1\" id=\"conn:" + a_connectionId + "\">\r\n\
   <dialogstart target=\"conn:" + a_connectionId + "\" type=\"application/moml+xml\">\r\n\
      <group topology=\"parallel\">\r\n\
         <play>\r\n\
            <media> \r\n\
               <audio uri=\"" + l_mediaPath + "/Mailbox_" + a_mailbox + ".pcm\" \r\n\
                  format=\"audio/proprietary;codecs=linear\" audiosamplerate=\"8\" audiosamplesize=\"16\"/> \r\n\
               <video uri=\"" + l_mediaPath + "/Mailbox_" + a_mailbox + ".vid\" format=\"video/proprietary;codecs=h263\"/> \r\n\
            </media> \r\n\
            <playexit>\r\n\
               <send target=\"dtmf\" event=\"terminate\"/>\r\n\
            </playexit>\r\n\
         </play>\r\n\
         <collect iterate=\"forever\">\r\n\
            <detect>\r\n\
               <send target=\"play\" event=\"terminate\"/>\r\n\
            </detect>\r\n\
         </collect>\r\n\
      </group>\r\n\
   </dialogstart>\r\n\
</msml>";
}

