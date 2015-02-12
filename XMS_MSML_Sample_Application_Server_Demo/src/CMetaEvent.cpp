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
// File Name: CMetaEvent.cpp
//
// Description: CMetaEvent calss implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CMetaEvent.h"

///////////////////////////////////////////////////////////////////////////////
// Function: CMetaEvent::CMetaEvent()
//
// Description: Default constructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CMetaEvent::CMetaEvent()
{
   memset( &m_metaEvent, 0, sizeof(METAEVENT));
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMetaEvent::CMetaEvent(METAEVENT *a_metaEvent)
//
// Description: Initializing constructor
//
// Return: 
//
// Parameters: METAEVENT *a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
CMetaEvent::CMetaEvent(METAEVENT* a_metaEvent)
{
   MetaEvent( a_metaEvent);
}

///////////////////////////////////////////////////////////////////////////////
// Function: CMetaEvent::~CMetaEvent()
//
// Description: Destructor
//
// Return: 
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CMetaEvent::~CMetaEvent()
{
   if (m_metaEvent.extevtdatap)
   {
      gc_util_delete_parm_blk( static_cast<GC_PARM_BLKP>(m_metaEvent.extevtdatap));
   }
   delete[] (char *) m_metaEvent.evtdatap;
   m_metaEvent.evtdatap = 0;
   m_metaEvent.evtlen = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function: long CMetaEvent::EventType()
//
// Description: Access the event type
//
// Return: long
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
long CMetaEvent::EventType()
{
   return m_metaEvent.evttype;
}

///////////////////////////////////////////////////////////////////////////////
// Function: CRN CMetaEvent::Crn()
//
// Description: Access the call reference number
//
// Return: CRN
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
CRN CMetaEvent::Crn()
{
   return m_metaEvent.crn;
}

///////////////////////////////////////////////////////////////////////////////
// Function: METAEVENT * CMetaEvent::MetaEvent()
//
// Description: Access the METAEVENT data structure
//
// Return: METAEVENT *
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
METAEVENT* CMetaEvent::MetaEvent()
{
   return &m_metaEvent;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CMetaEvent::MetaEvent(METAEVENT *a_metaEvent)
//
// Description: Set the METAEVENT data members
//
// Return: void
//
// Parameters: METAEVENT *a_metaEvent
//
///////////////////////////////////////////////////////////////////////////////
void CMetaEvent::MetaEvent( METAEVENT* a_metaEvent)
{
   m_metaEvent.magicno = a_metaEvent->magicno;
   m_metaEvent.flags = a_metaEvent->flags;
   m_metaEvent.evtdev = a_metaEvent->evtdev;
   m_metaEvent.evttype = a_metaEvent->evttype;
   m_metaEvent.linedev = a_metaEvent->linedev;
   m_metaEvent.crn = a_metaEvent->crn;

   if (a_metaEvent->extevtdatap)
   {

      GC_PARM_BLKP l_gcParmBlkSource = 0;
      if ( a_metaEvent->evttype == GCEV_EXTENSION)
      {
		   EXTENSIONEVTBLK* l_extensionBlock = (EXTENSIONEVTBLK*)(a_metaEvent->extevtdatap);
   		l_gcParmBlkSource = &l_extensionBlock->parmblk;
      }
      else
      {
       	l_gcParmBlkSource = (GC_PARM_BLK*)( a_metaEvent->extevtdatap);
      }

      GC_PARM_BLKP l_gcParmBlk = 0;
      if ( gc_util_copy_parm_blk(   &l_gcParmBlk,
                                    l_gcParmBlkSource) != GC_SUCCESS )
      {
         //TODO add error reporting
      }
      m_metaEvent.extevtdatap = static_cast<void*> (l_gcParmBlk);
   }
   else
   {
      m_metaEvent.extevtdatap = a_metaEvent->extevtdatap;
   }
   m_metaEvent.usrattr = a_metaEvent->usrattr;
   m_metaEvent.cclibid = a_metaEvent->cclibid;
   m_metaEvent.evtdatap = new char[ a_metaEvent->evtlen];
   m_metaEvent.evtlen = a_metaEvent->evtlen;
   memcpy( m_metaEvent.evtdatap, a_metaEvent->evtdatap, a_metaEvent->evtlen);
}

