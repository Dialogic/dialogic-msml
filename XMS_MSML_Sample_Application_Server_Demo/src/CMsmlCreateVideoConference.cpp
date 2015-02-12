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
// File Name: CMsmlCreateVideoConference.cpp
//
// Description: CMsmlCreateVideoConference class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CMsmlCreateVideoConference.h"


///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlCreateVideoConference::CMsmlCreateConference()
// Description: Constructor
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
CMsmlCreateVideoConference::CMsmlCreateVideoConference(int a_layout, const std::string& a_rootSize)
{ 
   switch(a_layout)
   {
	   case 1:
		   MsmlCreate1PartyVideoConference(a_rootSize);
	      break;
	   case 2:
	      MsmlCreate2PartyVideoConference(a_rootSize);
		  break;
	   case 4:
	      MsmlCreate4PartyVideoConference(a_rootSize);
		  break;
	   case 5:
	      MsmlCreate5PartyVideoConference(a_rootSize);
		  break;
	   case 6:
	      MsmlCreate6PartyVideoConference(a_rootSize);
		  break;
	   case 7:
	      MsmlCreate7PartyVideoConference(a_rootSize);
		  break;
	   case 9:
	      MsmlCreate9PartyVideoConference(a_rootSize);
		  break;
	   default:
          MsmlCreate1PartyVideoConference(a_rootSize);
		  break;
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlCreateVideoConference::~CMsmlCreateVideoConference()
// Description: Destructor
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
CMsmlCreateVideoConference::~CMsmlCreateVideoConference()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlCreateVideoConference::MsmlCreate4PartyVideoConference(const std::string& a_rootSize)
// Description: Create a 1 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlCreateVideoConference::MsmlCreate1PartyVideoConference(const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <createconference >\r\n\
      <audiomix>\r\n\
         <asn ri=\"00s\"/>\r\n\
      </audiomix>\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"1\" left=\"0\" top=\"0\" relativesize=\"1\" />\r\n\
         <region id=\"2\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
         <region id=\"3\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
         <region id=\"4\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"5\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
         <region id=\"6\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"7\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"8\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"9\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
      </videolayout>\r\n\
   </createconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlCreateVideoConference::MsmlCreate2PartyVideoConference(const std::string& a_rootSize)
// Description: Create a 2 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlCreateVideoConference::MsmlCreate2PartyVideoConference(const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <createconference >\r\n\
      <audiomix>\r\n\
         <asn ri=\"00s\"/>\r\n\
      </audiomix>\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"1\" left=\"0\" top=\"25%\" relativesize=\"1/2\" />\r\n\
         <region id=\"2\" left=\"50%\" top=\"25%\" relativesize=\"1/2\" />\r\n\
         <region id=\"3\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
         <region id=\"4\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"5\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
         <region id=\"6\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"7\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"8\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"9\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
      </videolayout>\r\n\
   </createconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlCreateVideoConference::MsmlCreate4PartyVideoConference(const std::string& a_rootSize)
// Description: Create a 4 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlCreateVideoConference::MsmlCreate4PartyVideoConference(const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <createconference >\r\n\
      <audiomix>\r\n\
         <asn ri=\"00s\"/>\r\n\
      </audiomix>\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"1\" left=\"0\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"2\" left=\"50%\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"3\" left=\"0\" top=\"50%\" relativesize=\"1/2\" />\r\n\
         <region id=\"4\" left=\"50%\" top=\"50%\" relativesize=\"1/2\" />\r\n\
		 <region id=\"5\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
         <region id=\"6\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"7\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"8\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"9\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
      </videolayout>\r\n\
   </createconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlCreateVideoConference::MsmlCreate5PartyVideoConference(const std::string& a_rootSize)
// Description: Create a 5 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlCreateVideoConference::MsmlCreate5PartyVideoConference(const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <createconference >\r\n\
      <audiomix>\r\n\
         <asn ri=\"00s\"/>\r\n\
      </audiomix>\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"1\" left=\"0\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"2\" left=\"0\" top=\"50%\" relativesize=\"1/2\" />\r\n\
         <region id=\"3\" left=\"50%\" top=\"0\" relativesize=\"1/3\" />\r\n\
         <region id=\"4\" left=\"67%\" top=\"33%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"5\" left=\"50%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
         <region id=\"6\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"7\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"8\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"9\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
      </videolayout>\r\n\
   </createconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlCreateVideoConference::MsmlCreate6PartyVideoConference(const std::string& a_rootSize)
// Description: Create a 6Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlCreateVideoConference::MsmlCreate6PartyVideoConference(const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <createconference >\r\n\
      <audiomix>\r\n\
         <asn ri=\"00s\"/>\r\n\
      </audiomix>\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"1\" left=\"0\" top=\"0\" relativesize=\"2/3\" />\r\n\
         <region id=\"2\" left=\"67%\" top=\"0\" relativesize=\"1/3\" />\r\n\
         <region id=\"3\" left=\"67%\" top=\"33%\" relativesize=\"1/3\" />\r\n\
         <region id=\"4\" left=\"67%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
         <region id=\"5\" left=\"33%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
         <region id=\"6\" left=\"0\" top=\"67%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"7\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"8\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"9\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
      </videolayout>\r\n\
   </createconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlCreateVideoConference::MsmlCreate7PartyVideoConference(const std::string& a_rootSize)
// Description: Create a 7Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlCreateVideoConference::MsmlCreate7PartyVideoConference(const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <createconference >\r\n\
      <audiomix>\r\n\
         <asn ri=\"00s\"/>\r\n\
      </audiomix>\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"1\" left=\"0\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"2\" left=\"50%\" top=\"0\" relativesize=\"1/2\" />\r\n\
         <region id=\"3\" left=\"0%\" top=\"50%\" relativesize=\"1/2\" />\r\n\
         <region id=\"4\" left=\"50%\" top=\"50%\" relativesize=\"1/4\" />\r\n\
         <region id=\"5\" left=\"75%\" top=\"50%\" relativesize=\"1/4\" />\r\n\
         <region id=\"6\" left=\"50%\" top=\"75%\" relativesize=\"1/4\" />\r\n\
		 <region id=\"7\" left=\"75%\" top=\"75%\" relativesize=\"1/4\" />\r\n\
		 <region id=\"8\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
		 <region id=\"9\" left=\"99%\" top=\"99%\" relativesize=\"1/100\" />\r\n\
      </videolayout>\r\n\
   </createconference>\r\n\
</msml>";
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlCreateVideoConference::MsmlCreate9PartyVideoConference(const std::string& a_rootSize)
// Description: Create a 9 Party Video Conference
// Return: 
// Parameters: none
///////////////////////////////////////////////////////////////////////////////
void CMsmlCreateVideoConference::MsmlCreate9PartyVideoConference(const std::string& a_rootSize)
{
   m_contentType = "Content-Type: application/xml";
   m_content = "\
<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n\
<msml version=\"1.1\">\r\n\
   <createconference >\r\n\
      <audiomix>\r\n\
         <asn ri=\"00s\"/>\r\n\
      </audiomix>\r\n\
      <videolayout>\r\n\
         <root size=\"" + a_rootSize + "\" />\r\n\
         <region id=\"1\" left=\"0\" top=\"0\" relativesize=\"1/3\" />\r\n\
         <region id=\"2\" left=\"33%\" top=\"0\" relativesize=\"1/3\" />\r\n\
         <region id=\"3\" left=\"67%\" top=\"0%\" relativesize=\"1/3\" />\r\n\
         <region id=\"4\" left=\"0\" top=\"33%\" relativesize=\"1/3\" />\r\n\
         <region id=\"5\" left=\"33%\" top=\"33%\" relativesize=\"1/3\" />\r\n\
         <region id=\"6\" left=\"67%\" top=\"33%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"7\" left=\"0\" top=\"67%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"8\" left=\"33%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
		 <region id=\"9\" left=\"67%\" top=\"67%\" relativesize=\"1/3\" />\r\n\
      </videolayout>\r\n\
   </createconference>\r\n\
</msml>";
}


