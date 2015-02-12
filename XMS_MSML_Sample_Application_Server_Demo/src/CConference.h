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
//	File Name:		CConference.h
//
//	Description:	CConference class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CConference_h
#define CConference_h

#include <boost/thread/mutex.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <string>
#include <set>
#include <map>
#include <vector>

#define MAX_LAYOUT_COUNT 7
#define MAX_REGION_COUNT 9

///////////////////////////////////////////////////////////////////////////////
// Class: ::CConference
//
// Description: Instances of this class hold information about a conference
//
///////////////////////////////////////////////////////////////////////////////
class CConference : public boost::enable_shared_from_this<CConference>
{
public:
   CConference( const std::string& a_conferenceName, const std::string& a_conferenceId);
   virtual ~CConference();

   int AddConferenceLeg( const std::string& a_conferenceLegId);
   int RemoveConferenceLeg( const std::string& a_conferenceLegId);

   const std::string& ConferenceName();
   const std::string& ConferenceId();

   bool IsEmpty();
   int NumConfParties();

   //JM VideoConf
   //static void AllowedLayouts(int a_layoutCount, int* a_layouts);
   //static void InitialLayout(int a_initialLayout);
   //static int InitialLayout();
   int ConfigureVideoLayouts(int a_layoutCount, int* a_layouts, int a_initialLayout);
   int CycleLayout();
   int GetDisplayRegion(const std::string& a_conferenceLegId);
   int RotateParties();
   int GetLayout();
   int* GetVisibleRegions();
   int RefreshRegions();
   bool IsRegionActive(int a_region);
   int GetNextOpenRegion();

private:
   CConference();    // no implementation, must use initializing constructor

   bool IsLegInConference( const std::string& a_conferenceLegId);

   std::string m_conferenceName;
   std::string m_conferenceId;
   //std::set<std::string> m_conferenceLegs;
   std::map<std::string,int> m_conferenceLegs;
   boost::mutex m_mutex;
   
   int m_layoutIndex;
   int m_allowedLayouts[MAX_LAYOUT_COUNT];
   int m_allowedLayoutsCount;
   int m_visibleRegions[MAX_REGION_COUNT];


};

#endif


