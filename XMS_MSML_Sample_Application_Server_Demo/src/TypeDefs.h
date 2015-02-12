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
// File Name: TypeDefs.h
//
// Description: Common type definitions
//
///////////////////////////////////////////////////////////////////////////////
#ifndef TypeDefs_h
#define TypeDefs_h

#include <boost/shared_ptr.hpp>

#include <sstream>
#include <map>

class CConfigOptions;
typedef boost::shared_ptr< CConfigOptions> CConfigOptionsSptr;

class ATask;
typedef boost::shared_ptr< ATask> ATaskSptr;

class CTaskProcessor;
typedef boost::shared_ptr<CTaskProcessor> CTaskProcessorSptr;

class CLogger;
typedef boost::shared_ptr<CLogger> CLoggerSptr;

typedef boost::shared_ptr< std::stringstream> LogItemSptr;

class ACallflow;
typedef boost::shared_ptr<ACallflow> ACallflowSptr;

class CCallflow;
typedef boost::shared_ptr<CCallflow> CCallflowSptr;

class CCallflowManager;
typedef boost::shared_ptr<CCallflowManager> CCallflowManagerSptr;

class AResourceGroup;
typedef boost::shared_ptr<AResourceGroup> AResourceGroupSptr;

class CResourceGroup;
typedef boost::shared_ptr<CResourceGroup> CResourceGroupSptr;

class CResourceGroupManager;
typedef boost::shared_ptr<CResourceGroupManager> CResourceGroupManagerSptr;

class ASipResource;
typedef boost::shared_ptr<ASipResource> ASipResourceSptr;

class ASipBoardResource;
typedef boost::shared_ptr<ASipBoardResource> ASipBoardResourceSptr;

class CSipResource;
typedef boost::shared_ptr<CSipResource> CSipResourceSptr;

class CSipBoardResource;
typedef boost::shared_ptr<CSipBoardResource> CSipBoardResourceSptr;

class CSipResourceManager;
typedef boost::shared_ptr<CSipResourceManager> CSipResourceManagerSptr;

class CResourceManager;
typedef boost::shared_ptr<CResourceManager> CResourceManagerSptr;

class CSrlEventManager;
typedef boost::shared_ptr< CSrlEventManager> CSrlEventManagerSptr;

class ATaskHandler;
typedef std::map< ATaskHandler*, ATaskSptr> ATaskHandlerList;
typedef std::map< int, ATaskHandlerList *> ATaskHandlerListByNotificationMap;
typedef std::map< long, ATaskHandlerList *> ATaskHandlerListByEventMap;

class CMetaEvent;
typedef boost::shared_ptr< CMetaEvent> CMetaEventSptr;

class CSipCallInfo;
typedef boost::shared_ptr< CSipCallInfo> CSipCallInfoSptr;

class AGlobalCallManager;
typedef boost::shared_ptr<AGlobalCallManager> AGlobalCallManagerSptr;

class CGlobalCallManager;
typedef boost::shared_ptr<CGlobalCallManager> CGlobalCallManagerSptr;

class ADialog;
typedef boost::shared_ptr<ADialog> ADialogSptr;

class CMsmlEvent;
typedef boost::shared_ptr<CMsmlEvent> CMsmlEventSptr;

class CMsmlResponse;
typedef boost::shared_ptr<CMsmlResponse> CMsmlResponseSptr;

class CConference;
typedef boost::shared_ptr<CConference> CConferenceSptr;

class AHttpManager;
typedef boost::shared_ptr<AHttpManager> AHttpManagerSptr;

class CHttpManager;
typedef boost::shared_ptr<CHttpManager> CHttpManagerSptr;

class AHttpRequest;
typedef boost::shared_ptr<AHttpRequest> AHttpRequestSptr;
/*
class CHttpRequest;
typedef boost::shared_ptr<CHttpRequest> CHttpRequestSptr;

class CHttpDelete;
typedef boost::shared_ptr<CHttpDelete> CHttpDeleteSptr;
*/
typedef std::map< void*, AHttpRequestSptr> AHttpRequestMap;

#endif
