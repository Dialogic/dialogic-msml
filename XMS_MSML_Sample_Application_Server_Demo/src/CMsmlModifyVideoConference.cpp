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
// File Name: CMsmlModifyVideoConference.cpp
//
// Description: CMsmlModifyVideoConference class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CMsmlModifyVideoConference.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::CMsmlModifyVideoConference()
// Description: Constructor
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
CMsmlModifyVideoConference::CMsmlModifyVideoConference(const std::string& a_conferenceId, int a_layout, int* a_regionlist,const std::string& a_rootSize)
{ 
   switch(a_layout)
   {
	   case 1:
		  MsmlModify1PartyVideoConference(a_conferenceId, a_regionlist, a_rootSize);
	      break;
	   case 2:
	      MsmlModify2PartyVideoConference(a_conferenceId, a_regionlist, a_rootSize);
		  break;
	   case 4:
	      MsmlModify4PartyVideoConference(a_conferenceId, a_regionlist, a_rootSize);
		  break;
	   case 6:
	      MsmlModify6PartyVideoConference(a_conferenceId, a_regionlist, a_rootSize);
		  break;
	   case 9:
	      MsmlModify9PartyVideoConference(a_conferenceId, a_regionlist, a_rootSize);
		  break;
	   default:
          MsmlModifyRootSizeVideoConference(a_conferenceId, a_rootSize);
		  break;
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::~CMsmlModifyVideoConference()
// Description: Destructor
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
CMsmlModifyVideoConference::~CMsmlModifyVideoConference()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::MsmlModifyRootSizePartyVideoConference(const std::string& a_conferenceId, const std::string& a_rootSize)
// Description: Modify the root size of a Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlModifyVideoConference::MsmlModifyRootSizeVideoConference(const std::string& a_conferenceId, const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <modifyconference id=\"" + a_conferenceId + "\" >\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
      </videolayout>\r\n\
   </modifyconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::MsmlModify1PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
// Description: Modify to a 1 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlModifyVideoConference::MsmlModify1PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <modifyconference id=\"" + a_conferenceId + "\" >\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[0]) + "\" left=\"0\" top=\"0\" relativesize=\"1/1\" />\r\n\
         <region id=\"" + AsString(a_regionlist[1]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
         <region id=\"" + AsString(a_regionlist[2]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
         <region id=\"" + AsString(a_regionlist[3]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[4]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
         <region id=\"" + AsString(a_regionlist[5]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[6]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[7]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[8]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
      </videolayout>\r\n\
   </modifyconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::MsmlModify2PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
// Description: Modify to a 2 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlModifyVideoConference::MsmlModify2PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <modifyconference id=\"" + a_conferenceId + "\" >\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"" + AsString(a_regionlist[0]) + "\" left=\"0\" top=\"25%\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[1]) + "\" left=\"50%\" top=\"25%\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[2]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
         <region id=\"" + AsString(a_regionlist[3]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[4]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
         <region id=\"" + AsString(a_regionlist[5]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[6]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[7]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[8]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
      </videolayout>\r\n\
   </modifyconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::MsmlModify4PartyVideoConference(const std::string& a_conferenceId, const std::string& a_rootSize)
// Description: Modify to a 4 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlModifyVideoConference::MsmlModify4PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <modifyconference id=\"" + a_conferenceId + "\" >\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"" + AsString(a_regionlist[0]) + "\" left=\"0\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[1]) + "\" left=\"50%\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[2]) + "\" left=\"0\" top=\"50%\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[3]) + "\" left=\"50%\" top=\"50%\" relativesize=\"1/2\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[4]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
         <region id=\"" + AsString(a_regionlist[5]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[6]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[7]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[8]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
      </videolayout>\r\n\
   </modifyconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::MsmlModify5PartyVideoConference(const std::string& a_conferenceId, const std::string& a_rootSize)
// Description: Modify to a 5 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlModifyVideoConference::MsmlModify5PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <modifyconference id=\"" + a_conferenceId + "\" >\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"" + AsString(a_regionlist[0]) + "\" left=\"0\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[1]) + "\" left=\"0\" top=\"50%\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[2]) + "\" left=\"50%\" top=\"0\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[3]) + "\" left=\"67%\" top=\"33%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[4]) + "\" left=\"50%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[5]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[6]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[7]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[8]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
      </videolayout>\r\n\
   </modifyconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::MsmlModify6PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
// Description: Modify to a 6Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlModifyVideoConference::MsmlModify6PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <modifyconference id=\"" + a_conferenceId + "\" >\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"" + AsString(a_regionlist[0]) + "\" left=\"0\" top=\"0\" relativesize=\"2/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[1]) + "\" left=\"67%\" top=\"0\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[2]) + "\" left=\"67%\" top=\"33%\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[3]) + "\" left=\"67%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[4]) + "\" left=\"33%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[5]) + "\" left=\"0\" top=\"67%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[6]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[7]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[8]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
      </videolayout>\r\n\
   </modifyconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::MsmlModify7PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
// Description: Modify to a 7Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlModifyVideoConference::MsmlModify7PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <modifyconference id=\"" + a_conferenceId + "\" >\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"" + AsString(a_regionlist[0]) + "\" left=\"0\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[1]) + "\" left=\"50%\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[2]) + "\" left=\"0%\" top=\"50%\" relativesize=\"1/2\" />\r\n\
         <region id=\"" + AsString(a_regionlist[3]) + "\" left=\"50%\" top=\"50%\" relativesize=\"1/4\" />\r\n\
         <region id=\"" + AsString(a_regionlist[4]) + "\" left=\"75%\" top=\"50%\" relativesize=\"1/4\" />\r\n\
         <region id=\"" + AsString(a_regionlist[5]) + "\" left=\"50%\" top=\"75%\" relativesize=\"1/4\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[6]) + "\" left=\"75%\" top=\"75%\" relativesize=\"1/4\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[7]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[8]) + "\" left=\"99%\" top=\"99%\" relativesize=\"0\" />\r\n\
      </videolayout>\r\n\
   </modifyconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlModifyVideoConference::MsmlModify9PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
// Description: Modify to a 9 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlModifyVideoConference::MsmlModify9PartyVideoConference(const std::string& a_conferenceId, int* a_regionlist, const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <modifyconference id=\"" + a_conferenceId + "\" >\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"" + AsString(a_regionlist[0]) + "\" left=\"0\" top=\"0\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[1]) + "\" left=\"33%\" top=\"0\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[2]) + "\" left=\"67%\" top=\"0%\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[3]) + "\" left=\"0\" top=\"33%\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[4]) + "\" left=\"33%\" top=\"33%\" relativesize=\"1/3\" />\r\n\
         <region id=\"" + AsString(a_regionlist[5]) + "\" left=\"67%\" top=\"33%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[6]) + "\" left=\"0\" top=\"67%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[7]) + "\" left=\"33%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"" + AsString(a_regionlist[8]) + "\" left=\"67%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
      </videolayout>\r\n\
   </modifyconference>\r\n\
</msml>";
}
