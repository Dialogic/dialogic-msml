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
// File Name: CGlobalCallManager.cpp
//
// Description: CGlobalCallManager class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CGlobalCallManager.h"
#include "CLogger.h"

#include "CConfigOptions.h"

#ifndef _WIN32
#include "devmapr4.h"
#endif

///////////////////////////////////////////////////////////////////////////////
// Function: CGlobalCallManager::CGlobalCallManager()
//
// Description: Default constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CGlobalCallManager::CGlobalCallManager() 
   : AGlobalCallManager()
   , m_logger( CLogger::Instance())
{

    memset(&m_libData,0,sizeof(IPCCLIB_START_DATA));
	memset(m_virtBoard,0,sizeof(IP_VIRTBOARD) * 1);
    INIT_IPCCLIB_START_DATA(&m_libData, 1, m_virtBoard);
	INIT_IP_VIRTBOARD(&m_virtBoard[0]);

	m_libData.num_boards = 1; 
	m_libData.max_parm_data_size = 4096;
	m_libData.media_operational_mode = MEDIA_OPERATIONAL_MODE_3PCC;
  	
    m_ccLibStart[0].cclib_name = "GC_H3R_LIB";
	m_ccLibStart[0].cclib_data = &m_libData;

	m_virtBoard[0].h323_max_calls = IP_CFG_NO_CALLS;
	m_virtBoard[0].h323_signaling_port = 1720;
	m_virtBoard[0].localIP.ip_ver = IPVER4;
	m_virtBoard[0].localIP.u_ipaddr.ipv4 = 0;
	m_virtBoard[0].sip_signaling_port = CConfigOptions::Instance()->SipPort();
	m_virtBoard[0].sip_msginfo_mask = IP_SIP_MIME_ENABLE | IP_SIP_MSGINFO_ENABLE;

    // Translates to max MSML body size
    m_virtBoard[0].sip_mime_mem.size = 5000;

	m_libData.board_list = m_virtBoard;

	m_gcLibStart.cclib_list = m_ccLibStart;
	m_gcLibStart.num_cclibs = 1;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CGlobalCallManager::~CGlobalCallManager()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CGlobalCallManager::~CGlobalCallManager()
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CGlobalCallManager::ClassName()
//
// Description: Access the class name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CGlobalCallManager::ClassName()
{
   return "CDGlobalCallManager";
}

///////////////////////////////////////////////////////////////////////////////
// Function: const char* CGlobalCallManager::Name()
//
// Description: Access the object name
//
// Return: const char* 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
const char* CGlobalCallManager::Name()
{
   return "GlobalCall Manager";
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CGlobalCallManager::PrimStart()
//
// Description: Determine the number of available HMP SIP resources, initialize 
// the SRL event environment and Start GlobalCall
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CGlobalCallManager::PrimStart()
{
   m_logger->Log( LOG_LEVEL_DEBUG, *this, "PrimStart");

   int l_sipChannels = AvailableSystemSipResources();
   if ( l_sipChannels == -1)
   {
      return -1;
   }

   if ( CConfigOptions::Instance()->MaxChannels() < l_sipChannels)
   {
      l_sipChannels = CConfigOptions::Instance()->MaxChannels();
   }

   CConfigOptions::Instance()->MaxChannels(l_sipChannels);

 	m_virtBoard[0].total_max_calls = l_sipChannels;
	m_virtBoard[0].sip_max_calls = l_sipChannels;

	m_logger->Log( LOG_LEVEL_DEBUG, *this, "gc_Start() Using SIP Channels", l_sipChannels);

#ifdef WIN32

	int	mode = SR_STASYNC | SR_POLLMODE; 

#else

	int	mode = SR_POLLMODE;

#endif

#ifdef WIN32

	if ( sr_setparm(SRL_DEVICE, SR_MODELTYPE, &mode) != 0) 
	{
      return -1;
	}

#else

	if ( sr_setparm(SRL_DEVICE, SR_MODEID, &mode) == -1) 
	{
      m_logger->Log( LOG_LEVEL_ERROR, *this, "PrimStart", "Unable to set to SR_POLLMODE");
	}

#endif

   int l_result = gc_Start(&m_gcLibStart);
   if (l_result != GC_SUCCESS)
   {
      LogGcError( "PrimStart");
      return -1;
   }

   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CGlobalCallManager::PrimStop()
//
// Description: Stop GlobalCall
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CGlobalCallManager::PrimStop()
{
   m_logger->Log( LOG_LEVEL_DEBUG, *this, "PrimStop");
   int l_result = gc_Stop();
   if (l_result != GC_SUCCESS)
   {
      LogGcError( "PrimStart");
      return -1;
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: int CGlobalCallManager::AvailableSystemSipResources()
//
// Description: Determine the number of available HMP SIP resources
//
// Return: int - 0 on success, otherwise failure
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
int CGlobalCallManager::AvailableSystemSipResources()
{
   m_logger->Log( LOG_LEVEL_DEBUG, *this, "AvailableSystemSipResources");

   int l_physicalBoardCount(0);
   int l_result;
   if ( ( l_result = SRLGetAllPhysicalBoards( &l_physicalBoardCount, 0)) != ESR_INSUFBUF)
   {
      m_logger->Log( LOG_LEVEL_ERROR, *this, "AvailableSystemSipResources", "SRLGetAllPhysicalBoards() failed");
      return -1;
   }

   m_logger->Log( LOG_LEVEL_DEBUG, *this, "AvailableSystemSipResources physical board count =", l_physicalBoardCount);
   if ( l_physicalBoardCount < 1)
   {
      m_logger->Log( LOG_LEVEL_ERROR, *this, "AvailableSystemSipResources", "physical board count < 1");
      return -1;
   }

   AUID l_physicalBoard;
   if ( ( l_result = SRLGetAllPhysicalBoards( &l_physicalBoardCount, &l_physicalBoard)) != ESR_NOERR)
   {
      m_logger->Log( LOG_LEVEL_ERROR, *this, "AvailableSystemSipResources", "SRLGetAllPhysicalBoards() failed");
      return -1;
   }
   m_logger->Log( LOG_LEVEL_DEBUG, *this, "AvailableSystemSipResources physical board =", l_physicalBoard);


   int  l_virtualBoardCount(0);
   if ( ( l_result = SRLGetVirtualBoardsOnPhysicalBoard( l_physicalBoard, &l_virtualBoardCount, 0)) != ESR_INSUFBUF)
   {
      m_logger->Log( LOG_LEVEL_ERROR, *this, "AvailableSystemSipResources", "SRLGetVirtualBoardsOnPhysicalBoard() failed");
      return -1;
   }
   m_logger->Log( LOG_LEVEL_DEBUG, *this, "AvailableSystemSipResources virtual board count =", l_virtualBoardCount);


   SRLDEVICEINFO* l_virtualBoardInfo = new SRLDEVICEINFO[ l_virtualBoardCount];
   if ( ( l_result = SRLGetVirtualBoardsOnPhysicalBoard( l_physicalBoard,
                                                         &l_virtualBoardCount,
                                                         l_virtualBoardInfo) )  != ESR_NOERR)
   {
      m_logger->Log( LOG_LEVEL_ERROR, *this, "AvailableSystemSipResources", "SRLGetVirtualBoardsOnPhysicalBoard() failed");
      return -1;
   }

   int l_iptDeviceCount(0);
   unsigned long lic_msk;
   LIC_FEATURE_BLK lic_data;
   INIT_LICENSED_FEATURES_VERSION(&lic_data);
   
   if ( (l_result = dev_GetLicFeatureData(&lic_data)) != 0)
   {
       m_logger->Log( LOG_LEVEL_ERROR, *this, "AvailableSystemSipResources()", "dev_getLicFeatureData() failed");
       m_logger->Log( LOG_LEVEL_ERROR, *this, "AvailableSystemSipResources()", "Could not get licensed feature information");
       return -1;
   }
   else
   {
      m_logger->Log( LOG_LEVEL_DEBUG, *this, "**********************************************");
      for (unsigned int i = 0; i < lic_data.NumFeatures; i++)
      {
         // Debug
         //m_logger->Log( LOG_LEVEL_DEBUG, *this, "License Feature Name", FeatureNameTable[lic_data.lic_data_buf[i].FeatureEnum]);
         //m_logger->Log( LOG_LEVEL_DEBUG, *this, "License Feature Count", lic_data.lic_data_buf[i].FeatureCount);
         m_logger->Log( LOG_LEVEL_DEBUG, *this, FeatureNameTable[lic_data.lic_data_buf[i].FeatureEnum], lic_data.lic_data_buf[i].FeatureCount);
         if( 0 == strcmp(FeatureNameTable[lic_data.lic_data_buf[i].FeatureEnum], LM_FEATURE_NAME_IPCC))
         {
            //m_logger->Log( LOG_LEVEL_DEBUG, *this, "Number of 3PCC IPCall Control Licenses", lic_data.lic_data_buf[i].FeatureCount);
            l_iptDeviceCount =  lic_data.lic_data_buf[i].FeatureCount; 
         }
      }
      m_logger->Log( LOG_LEVEL_DEBUG, *this, "**********************************************");
   }    

   m_logger->Log( LOG_LEVEL_DEBUG, *this, "AvailableSystemSipResources", l_iptDeviceCount);
   return l_iptDeviceCount;

}

///////////////////////////////////////////////////////////////////////////////
// Function: void CGlobalCallManager::LogGcError(const char *a_method)
//
// Description: Log a GlobalCall error
//
// Return: void
//
// Parameters: const char *a_method
//
///////////////////////////////////////////////////////////////////////////////
void CGlobalCallManager::LogGcError( const char* a_method)
{
   GC_INFO l_gcErrorInfo;
   if ( gc_ErrorInfo( &l_gcErrorInfo) != GC_SUCCESS)
   {
      m_logger->Log( LOG_LEVEL_ERROR, *this, a_method, " gc_ErrorInfo() failed, unable to retrieve error info");
   }
   else
   {
      std::ostringstream l_stream;
	   l_stream << 	ATDV_NAMEP( 0 )
         << ", GC error="
         << "\n\tgcValue  : 0x" << std::hex << l_gcErrorInfo.gcValue
         << "\n\tgcMsg    : " << l_gcErrorInfo.gcMsg
         << "\tccLibId  : " << std::dec << l_gcErrorInfo.ccLibId
         << "\n\tccLibName: " << l_gcErrorInfo.ccLibName
         << "\n\tccValue  : 0x" << std::hex << l_gcErrorInfo.ccValue
         << "\n\tccMsg    : " << l_gcErrorInfo.ccMsg
         << "\tinfo     : " << l_gcErrorInfo.additionalInfo;
      const std::string& l_msg = l_stream.str();
      m_logger->Log( LOG_LEVEL_ERROR, *this, a_method, l_msg);
   }
}
