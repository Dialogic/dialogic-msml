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
//	File Name:		CConferenceManager.h
//
//	Description:	CConferenceManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CConferenceManager_h
#define CConferenceManager_h

#include "Singleton.h"
#include "TypeDefs.h"

#include <boost/thread/mutex.hpp>

#include <string>
#include <map>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CConferenceManager
//
// Description: Manages information on a set of conferences
//
///////////////////////////////////////////////////////////////////////////////
class CConferenceManager : public Singleton<CConferenceManager>
{
   friend class Singleton<CConferenceManager>;

public:
   virtual ~CConferenceManager();

   int AddConference( CConferenceSptr a_conference);
   int RemoveConference( CConferenceSptr a_conference);
   CConferenceSptr FindConference( const std::string& a_conferenceName);

   bool ConferenceExists( const std::string& a_conferenceName);

private:
   std::map<std::string, CConferenceSptr> m_conferenceRegistry;
   boost::mutex m_mutex;
};

#endif

