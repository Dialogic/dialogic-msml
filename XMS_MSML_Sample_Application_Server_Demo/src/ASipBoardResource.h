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
// File Name: ASipBoardResource.h
//
// Description: ASipBoardResource class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef ASipBoardResource_h
#define ASipBoardResource_h

#include "ATaskHandler.h"
#include "AObserverSubject.h"
#include "SipBoardResourceStates.h"

///////////////////////////////////////////////////////////////////////////////
// Enumeration: ::EnumSipBoardResourceNotifications
//
// Description: Observer notifications supported by SIP Board Resource objects
//
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
   SIP_BOARD_RESOURCE_OPENED,
   SIP_BOARD_RESOURCE_CLOSED,
} EnumSipBoardResourceNotifications;

///////////////////////////////////////////////////////////////////////////////
// Class: ::ASipBoardResource
//
// Description: The abstract SIP Board Resource class implements the public 
// interface and state machine for the SIP Board Resource class.  The SIP Board 
// Resource CLass is responsible for opening/closing a GC SIP board dewvice and
// setting runtime configuration parameters.
//
///////////////////////////////////////////////////////////////////////////////
class ASipBoardResource : public ATaskHandler, public AObserverSubject
{
   friend class ASipBoardResourceState;
   friend class CSipBoardResourceClosedState;
   friend class CSipBoardResourceOpeningState;
   friend class CSipBoardResourceOpenedState;
   friend class CSipBoardResourceClosingState;

public:
   ASipBoardResource( CTaskProcessorSptr a_taskProcessor);
   virtual ~ASipBoardResource();

   void Open();
   void OnOpened( const CMetaEventSptr& a_metaEvent);
   void Close();
   void OnClosed();

   const char* StateDesc();
   LogObjectTypeEnum LogObjectType();

protected:
   virtual int PrimOpen() = 0;
   virtual int PrimOnOpened( const CMetaEventSptr& a_metaEvent) = 0;
   virtual int PrimClose() = 0;
   virtual int PrimOnClosed() = 0;

private:
   ASipBoardResource();

   void BasicOpen();
   void BasicOnOpened( const CMetaEventSptr& a_metaEvent);
   void BasicClose();
   void BasicOnClosed();

   void SetStateToClosed();
   void SetStateToOpening();
   void SetStateToOpened();
   void SetStateToClosing();

   ASipBoardResourceState* m_state; 
   static CSipBoardResourceClosedState m_closedState;
   static CSipBoardResourceOpeningState m_openingState;
   static CSipBoardResourceOpenedState m_openedState;
   static CSipBoardResourceClosingState m_closingState; 
};

#endif
