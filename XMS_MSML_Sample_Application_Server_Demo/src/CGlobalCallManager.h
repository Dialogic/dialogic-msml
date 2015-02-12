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
// File Name: CGlobalCallManager.h
//
// Description: CGlobalCallManager class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CGlobalCallManager_h
#define CGlobalCallManager_h

#include "AGlobalCallManager.h"
#include "Singleton.h"

#include "gcip.h"
#include "srllib.h"
#include "LicensedFeatures.h"
#include "devmgmt.h"

///////////////////////////////////////////////////////////////////////////////
// Class: ::CGlobalCallManager
//
// Description: The GlobalCall Manager is a singleton responsible for starting
// and stopping GlobalCall and discovering available GC resopurces.
//
///////////////////////////////////////////////////////////////////////////////
class CGlobalCallManager : public AGlobalCallManager, public Singleton<CGlobalCallManager>
{
   friend class Singleton<CGlobalCallManager>;

public:
   virtual ~CGlobalCallManager();
   const char* ClassName();
   const char* Name();

private:
   CGlobalCallManager();

   CLoggerSptr m_logger;

   int PrimStart();
   int PrimStop();

   IPCCLIB_START_DATA m_libData;
	IP_VIRTBOARD m_virtBoard[1];
	CCLIB_START_STRUCT m_ccLibStart[1];
	GC_START_STRUCT m_gcLibStart;

   int AvailableSystemSipResources();

   void LogGcError( const char* a_method);
};

#endif
