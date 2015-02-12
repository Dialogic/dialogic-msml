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
// File Name: CSipBoardResource.h
//
// Description: CSipBoardResource class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CSipBoardResource_h
#define CSipBoardResource_h

#include <boost/enable_shared_from_this.hpp>

#include "TypeDefs.h"
#include "ASipBoardResource.h"

#include <string>

#include <gcip.h>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipBoardResource
//
// Description: The SIP Board Resource CLass is responsible for opening/closing
// a GC SIP board dewvice and setting runtime configuration parameters.
//
///////////////////////////////////////////////////////////////////////////////
class CSipBoardResource : public ASipBoardResource, public boost::enable_shared_from_this<CSipBoardResource>
{
public:
   CSipBoardResource( CTaskProcessorSptr a_taskProcessor, const std::string& a_deviceName);
   virtual ~CSipBoardResource();

   const char* ClassName();

   const CSipBoardResourceSptr SharedPtr();

   CSrlEventManagerSptr SrlEventManager();

private:
   CSipBoardResource();

   std::string m_deviceName;
   LINEDEV m_srlDeviceHandle;

   int PrimOpen();
   int PrimOnOpened( const CMetaEventSptr& a_metaEvent);
   int PrimClose();
   int PrimOnClosed();

   void LogGcError( const char* a_method, int a_deviceHandle);
};

#endif

