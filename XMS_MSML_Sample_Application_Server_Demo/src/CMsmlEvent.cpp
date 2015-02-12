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
// File Name: CMsmlEvent.cpp
//
// Description: CMsmlEvent class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CMsmlEvent.h"

const std::string CMsmlEvent::m_emptyString;

///////////////////////////////////////////////////////////////////////////////
// Function: CMsmlEvent::CMsmlEvent(const std::string &a_info)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: const std::string &a_info
//
///////////////////////////////////////////////////////////////////////////////
CMsmlEvent::CMsmlEvent( const std::string& a_info)
{
   const char* l_eventNameLabel = "event name=\"";
   const char* l_eventNameDelim = "\"";
   const char* l_eventParmNameLabel = "<name>";
   const char* l_eventParmNameDelim = "</name>";
   const char* l_eventParmValueLabel = "<value>";
   const char* l_eventParmValueDelim = "</value>";
   int l_eventParmNamePos = 0;
   int l_eventParmValuePos = 0;

   int l_eventNamePos = a_info.find( l_eventNameLabel);
   if ( l_eventNamePos != a_info.npos)
   {
      l_eventNamePos += strlen( l_eventNameLabel);
      int eventNameEndPos = a_info.find( l_eventNameDelim, l_eventNamePos );
      if ( eventNameEndPos != a_info.npos)
      {
         m_name = a_info.substr( l_eventNamePos, eventNameEndPos - l_eventNamePos);
         while ( (l_eventParmNamePos = a_info.find( l_eventParmNameLabel, l_eventParmNamePos)) != a_info.npos)
         {
            l_eventParmNamePos += strlen( l_eventParmNameLabel);
            int eventParmNameEndPos = a_info.find( l_eventParmNameDelim, l_eventParmNamePos );
            if ( eventParmNameEndPos != a_info.npos)
            {
               std::string eventParmName = a_info.substr( l_eventParmNamePos, eventParmNameEndPos - l_eventParmNamePos);
               l_eventParmNamePos = eventParmNameEndPos + strlen(l_eventParmNameDelim);
               l_eventParmValuePos = a_info.find( l_eventParmValueLabel, l_eventParmNamePos);
               if ( l_eventParmValuePos != a_info.npos)
               {
                  std::string eventParmValue;
                  l_eventParmValuePos += strlen( l_eventParmValueLabel);
                  int eventParmValueEndPos = a_info.find( l_eventParmValueDelim, l_eventParmNamePos );
                  if ( eventParmValueEndPos != a_info.npos)
                  {
                     eventParmValue = a_info.substr( l_eventParmValuePos, eventParmValueEndPos - l_eventParmValuePos);
                     l_eventParmNamePos = eventParmValueEndPos + strlen(l_eventParmNameDelim);
                     AddParm( eventParmName, eventParmValue);
                  }
               }
            }
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CMsmlEvent::Name()
//
// Description: Access the event name
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CMsmlEvent::Name()
{
   return m_name;
}

///////////////////////////////////////////////////////////////////////////////
// Function: std::map<std::string,std::string>& CMsmlEvent::Parms()
//
// Description: Access the event parameters
//
// Return: std::map<std::string,std::string>&
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
std::map<std::string,std::string>& CMsmlEvent::Parms()
{
   return m_parms;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CMsmlEvent::AddParm(std::string &name, std::string &value)
//
// Description: Add an event parameter
//
// Return: void
//
// Parameters: std::string &name
//             std::string &value
//
///////////////////////////////////////////////////////////////////////////////
void CMsmlEvent::AddParm( std::string& name, std::string& a_value)
{
   m_parms[name] = a_value;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CMsmlEvent::MatchedDtmf()
//
// Description: Access the dtmf string that is a result of a dtmf.match event
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CMsmlEvent::MatchedDtmf()
{
   if ( m_parms.find("dtmf.end") != m_parms.end())
   {
      if ( m_parms["dtmf.end"] == "dtmf.match")
      {
         return m_parms["dtmf.digits"];
      }
   }
   return m_emptyString;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CMsmlEvent::LastDtmf()
//
// Description: Access the dtmf string that is a result of a dtmf.last event
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CMsmlEvent::LastDtmf()
{
   if ( m_parms.find("dtmf.last") != m_parms.end())
   {
      return m_parms["dtmf.last"];
   }
   return m_emptyString;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CMsmlEvent::ParmValue( const std::string& a_parm)
//
// Description: Access the value of a parameter
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CMsmlEvent::ParmValue( const std::string& a_parm)
{
   if ( m_parms.find( a_parm) != m_parms.end())
   {
      return m_parms[ a_parm];
   }
   return m_emptyString;
}


