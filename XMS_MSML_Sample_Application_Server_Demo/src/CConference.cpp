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
//	File Name:		CConference.cpp
//
//	Description:	CConference class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CConference.h"
#include "CConferenceManager.h"

//int CConference::m_allowedLayouts[] = {1,2,4,6,9};
//int CConference::m_allowedLayoutsCount = 5;
//int CConference::m_initialLayout = 1;

///////////////////////////////////////////////////////////////////////////////
// Function: CConference::CConference(const std::string &a_conferenceName, const std::string &a_conferenceId)
//
// Description: Initializing constructor
//
// Return:  
//
// Parameters: const std::string &a_conferenceName 
//             const std::string &a_conferenceId 
//
///////////////////////////////////////////////////////////////////////////////
CConference::CConference( const std::string& a_conferenceName, const std::string& a_conferenceId)
   : m_conferenceName( a_conferenceName)
   , m_conferenceId( a_conferenceId)
   , m_layoutIndex(0)
   , m_allowedLayoutsCount(MAX_LAYOUT_COUNT)
{
	   m_allowedLayouts[0] = 1;
	   m_allowedLayouts[1] = 2;
	   m_allowedLayouts[2] = 4;
	   m_allowedLayouts[3] = 5;
	   m_allowedLayouts[4] = 6;
	   m_allowedLayouts[5] = 7;
	   m_allowedLayouts[6] = 9;

	   for(int i=0; i<MAX_REGION_COUNT; i++)
	   {
		   m_visibleRegions[i]=i+1;
	   }

}

///////////////////////////////////////////////////////////////////////////////
// Function: CConference::~CConference()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
CConference::~CConference()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConference::AddConferenceLeg(const std::string &a_conferenceLegId)
//
// Description: Add a conference leg to the conference
//
// Return: int  - 0 onr success, otherwise failure
//
// Parameters: const std::string &a_conferenceLegId 
//
///////////////////////////////////////////////////////////////////////////////
int CConference::AddConferenceLeg( const std::string& a_conferenceLegId)
{
   boost::mutex::scoped_lock lock( m_mutex);
   if ( IsLegInConference( a_conferenceLegId) )
   {
      return -1;
   }
   int l_displayRegion = GetNextOpenRegion();
   if(l_displayRegion == 0)
   {
      return -1;
   }
   m_conferenceLegs.insert(make_pair(a_conferenceLegId,l_displayRegion));
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConference::RemoveConferenceLeg(const std::string &a_conferenceLegId)
//
// Description: Remove a conference leg from the conference
//
// Return: int  - 0 on success, otherwise failure
//
// Parameters: const std::string &a_conferenceLegId 
//
///////////////////////////////////////////////////////////////////////////////
int CConference::RemoveConferenceLeg( const std::string& a_conferenceLegId)
{
   boost::mutex::scoped_lock lock( m_mutex);
   if ( IsLegInConference( a_conferenceLegId) )
   {
      m_conferenceLegs.erase(a_conferenceLegId);
      if ( m_conferenceLegs.empty())
      {
         CConferenceManager::Instance()->RemoveConference( shared_from_this());
      }
      return 0;
   }
   return -1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string& CConference::ConferenceName()
//
// Description: Access the conference name
//
// Return: const std::string& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CConference::ConferenceName()
{
   return m_conferenceName;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string& CConference::ConferenceId()
//
// Description: Access the conference ID
//
// Return: const std::string& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CConference::ConferenceId()
{
   return m_conferenceId;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CConference::IsEmpty()
//
// Description: Test if the conference has no conference legs
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
bool CConference::IsEmpty()
{
   return m_conferenceLegs.empty();
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConference::NumConfParties()
//
// Description: Return Num conference legs
//
// Return: bool 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
int CConference::NumConfParties()
{
   return m_conferenceLegs.size();
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CConference::IsLegInConference(const std::string &a_conferenceLegId)
// Description: Test if a conference leg is inj this conference
//
// Return: bool 
//
// Parameters: const std::string &a_conferenceLegId 
//
///////////////////////////////////////////////////////////////////////////////
bool CConference::IsLegInConference( const std::string& a_conferenceLegId)
{
   return m_conferenceLegs.find( a_conferenceLegId) != m_conferenceLegs.end();
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CConference::IsRegionActive(int a_region)
// Description: Test if region is actively used in this conference
//
// Return: bool 
//
// Parameters: int a_region 
//
///////////////////////////////////////////////////////////////////////////////
bool CConference::IsRegionActive( int a_region)
{
	bool bRet=false;
	std::map<std::string, int>::iterator r;

	for(r=m_conferenceLegs.begin(); r!=m_conferenceLegs.end(); r++)
	{
		if(r->second == a_region)
			return true;
	}
	return false;
}

//*****************************************************************************
// Function: int CConference::GetDisplayRegion(const std::string& a_conferenceLegId)
// Description: Get the Display Region for a Conference Leg
// Return: int - DisplayRegion
// Parameters: none
//*****************************************************************************
int CConference::GetDisplayRegion(const std::string& a_conferenceLegId)
{
	std::map<std::string,int>::iterator l_ConferenceLeg;
   if(IsLegInConference(a_conferenceLegId))
   {
	   l_ConferenceLeg = m_conferenceLegs.find(a_conferenceLegId);
	   return l_ConferenceLeg->second;
   }
   return 0;
}

//*****************************************************************************
// Function: int CConference::GetNextOpenRegion()
// Description: Get the Next open Display Region for a Conference Leg 
// Return: int - DisplayRegion
// Parameters: none
//*****************************************************************************
int CConference::GetNextOpenRegion()
{
   for(int l_region=1; l_region<MAX_REGION_COUNT+1; l_region++)
   {
      if(!IsRegionActive(l_region))
      {
         return l_region;
      }
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CConference::ConfigureVideoLayouts(int a_layoutCnt, int* a_layouts, int a_initialLayout)
//
// Description: Configure Video Conference Layouts
//
// Return: int  - 0 on success, otherwise failure
//
// Parameters: const std::string &a_conferenceLegId 
//
///////////////////////////////////////////////////////////////////////////////
int CConference::ConfigureVideoLayouts(int a_layoutCount, int* a_layouts, int a_initialLayout)
{
   
   // Set the number of video conference layouts
   if (a_layoutCount > MAX_LAYOUT_COUNT)
   {
      m_allowedLayoutsCount = MAX_LAYOUT_COUNT;
   }
   else
   {
      m_allowedLayoutsCount = a_layoutCount;
   }

   // Set the video conference allowed layouts and initial layout
   for (int i=0; i<m_allowedLayoutsCount; i++)
   {
      m_allowedLayouts[i] = a_layouts[i];
      if (m_allowedLayouts[i] == a_initialLayout)
      {
         m_layoutIndex = i;
      }
   }

   return 0;
}

//*****************************************************************************
// Function: void CConference::CycleLayout()
// Description: Cycle Layout between supported Layouts
// Return: int
// Parameters: none
//*****************************************************************************
int CConference::CycleLayout()
{
   int newLayout = 1;
   m_layoutIndex = ++m_layoutIndex % m_allowedLayoutsCount;

   newLayout = m_allowedLayouts[m_layoutIndex];

   return newLayout;
}

//*****************************************************************************
// Function: void CConference::GetLayout()
// Description: Get Current Layout
// Return: int
// Parameters: none
//*****************************************************************************
int CConference::GetLayout()
{
   return m_allowedLayouts[m_layoutIndex];
}

//*****************************************************************************
// Function: int* CConference::GetVisibleRegions()
// Description: GetVisibleRegion vector
// Return: int
// Parameters: none
//*****************************************************************************
int* CConference::GetVisibleRegions()
{
   return m_visibleRegions;
}

//*****************************************************************************
// Function: int CConference::RotateParties()
// Description: Rotate the visible parties within the conference layout
// Return: int - 0 for success, otherwise error
// Parameters: none
//*****************************************************************************
int CConference::RotateParties()
{
      int l_visibleParties[MAX_REGION_COUNT];
	  int l_start=0;
	  int l_end = MAX_REGION_COUNT;

	  if(NumConfParties() < m_allowedLayouts[m_layoutIndex])
		  l_end = m_allowedLayouts[m_layoutIndex];
	  else if (NumConfParties() > MAX_REGION_COUNT)
		  l_end = MAX_REGION_COUNT;
	  else
		  l_end = NumConfParties();

      for (int i=l_start;i<l_end;i++)
      {
         l_visibleParties[i] = m_visibleRegions[i];
      }

      for (int i=l_start;i<l_end-1;i++)
      {
         m_visibleRegions[i+1] = l_visibleParties[i];
      }
      m_visibleRegions[l_start] = l_visibleParties[l_end-1];

      return 0;

}

//*****************************************************************************
// Function: int CConference::RefreshRegions()
// Description: Refresh regions to bring active regions to front
// Return: int - 0 for success, otherwise error
// Parameters: none
//*****************************************************************************
int CConference::RefreshRegions()
{
	  std::map<std::string, int>::iterator p;
	  std::vector<int> l_regionList(MAX_REGION_COUNT,0);

	  int k = 0;
	  p=m_conferenceLegs.begin();
	  for(p=m_conferenceLegs.begin(); p!=m_conferenceLegs.end(); p++)
	  {
		  l_regionList[k++] = p->second;
	  }

	  for(int l_region=1; l_region<MAX_REGION_COUNT+1; l_region++)
	  {
		  if(!IsRegionActive(l_region))
		  {
			  l_regionList[k++] = l_region;
		  }
	  }

	  for(int i=0; i<MAX_REGION_COUNT; i++)
	  {
		  m_visibleRegions[i] = l_regionList[i];
	  }

      return 0;
}
