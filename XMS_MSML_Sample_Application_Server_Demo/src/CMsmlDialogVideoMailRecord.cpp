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
// File Name: CMsmlDialogVideoMailRecord.cpp
//
// Description: CMsmlDialogVideoMailRecord clsss oimplementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CMsmlDialogVideoMailRecord.h"
#include "CConfigOptions.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlDialogVideoMailRecord::CMsmlDialogVideoMailRecord(const std::string &a_connectionId, const std::string &a_mailbox)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: const std::string &a_connectionId
//             const std::string &a_mailbox
//
///////////////////////////////////////////////////////////////////////////////
CMsmlDialogVideoMailRecord::CMsmlDialogVideoMailRecord( 
         const std::string& a_connectionId,
         const std::string& a_mailbox)
{
   std::string l_mediaPath = CConfigOptions::Instance()->MediaPathUri();

   m_contentType = "Content-Type: application/xml";
   m_content = "\
<msml version=\"1.1\" id=\"conn:" + a_connectionId + "\">\r\n\
   <dialogstart target=\"conn:" + a_connectionId + "\" type=\"application/moml+xml\">\r\n\
      <group topology=\"parallel\">\r\n\
        <record \r\n\
            audiodest=\"" + l_mediaPath + "/Mailbox_" + a_mailbox + ".pcm\" \r\n\
            videodest=\"" + l_mediaPath + "/Mailbox_" + a_mailbox + ".vid\" \r\n\
            format=\"video/proprietary;codecs=linear,h263\" audiosamplerate=\"8\" audiosamplesize=\"16\" beep=\"true\"> \r\n\
            <recordexit>\r\n\
               <send target=\"dtmf\" event=\"terminate\"/>\r\n\
            </recordexit>\r\n\
         </record>\r\n\
         <collect iterate=\"forever\">\r\n\
            <pattern digits=\"2\">\r\n\
               <send target=\"record\" event=\"terminate\"/>\r\n\
               <send target=\"source\" event=\"done\" namelist=\"dtmf.digits dtmf.end\"/>\r\n\
            </pattern>\r\n\
            <pattern digits=\"*\">\r\n\
               <send target=\"record\" event=\"terminate\"/>\r\n\
               <send target=\"source\" event=\"done\" namelist=\"dtmf.digits dtmf.end\"/>\r\n\
            </pattern>\r\n\
         </collect>\r\n\
      </group>\r\n\
   </dialogstart>\r\n\
</msml>";
}

