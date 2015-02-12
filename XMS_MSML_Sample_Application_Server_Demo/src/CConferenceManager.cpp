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
//	File Name:		CConferenceManager.cpp
//
//	Description:	CConferenceManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CConferenceManager.h"
#include "CConference.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CConferenceManager::~CConferenceManager()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CConferenceManager::~CConferenceManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConferenceManager::AddConference(CConferenceSptr a_conference)
//
// Description: Add a conference to be managed
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: CConferenceSptr a_conference 
//
///////////////////////////////////////////////////////////////////////////////
int CConferenceManager::AddConference( CConferenceSptr a_conference)
{
   boost::mutex::scoped_lock lock( m_mutex);
   if ( ConferenceExists( a_conference->ConferenceName()))
   {
      return -1;
   }
   m_conferenceRegistry[ a_conference->ConferenceName()] = a_conference;
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConferenceManager::RemoveConference(CConferenceSptr a_conference)
//
// Description: Remove a conference from being managed
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: CConferenceSptr a_conference 
//
///////////////////////////////////////////////////////////////////////////////
int CConferenceManager::RemoveConference( CConferenceSptr a_conference)
{
   boost::mutex::scoped_lock lock( m_mutex);
   std::map<std::string, CConferenceSptr>:: iterator l_pos;
   l_pos = m_conferenceRegistry.find( a_conference->ConferenceName());
   if ( l_pos != m_conferenceRegistry.end())
   {
      m_conferenceRegistry.erase( l_pos);
      return 0;
   }
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CConferenceSptr CConferenceManager::FindConference(const std::string &a_conferenceName)
//
// Description: Return a smart pointer for a conference given a confernce name
//
// Return: CConferenceSptr 
//
// Parameters: const std::string &a_conferenceName 
//
///////////////////////////////////////////////////////////////////////////////
CConferenceSptr CConferenceManager::FindConference( const std::string& a_conferenceName)
{
   boost::mutex::scoped_lock lock( m_mutex);
   CConferenceSptr l_conference;
   if ( ConferenceExists( a_conferenceName) )
   {
      l_conference = m_conferenceRegistry[ a_conferenceName];
   }
   return l_conference;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CConferenceManager::ConferenceExists(const std::string &a_conferenceName)
//
// Description: Test if a conference exists
//
// Return: bool 
//
// Parameters: const std::string &a_conferenceName 
//
///////////////////////////////////////////////////////////////////////////////
bool CConferenceManager::ConferenceExists( const std::string& a_conferenceName)
{
   return m_conferenceRegistry.find( a_conferenceName) != m_conferenceRegistry.end();
}

