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
// File Name: CMetaEvent.h
//
// Description: CMetaEvent class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CMetaEvent_h
#define CMetaEvent_h

#include "gclib.h"

///////////////////////////////////////////////////////////////////////////////
//	REFERENCE
///////////////////////////////////////////////////////////////////////////////
//
//	METAEVENT structure
//	typedef struct { 
//		long magicno;			//	for internal use only 
//		unsigned long flags;	//	The GCME_GC_EVENT bit is set if, and only if, 
//								//	the event is a GlobalCall event
//		void *evtdatap; 		//	for internal use only, sr_getevtdatap( ) 
//		long evtlen;			//	for internal use only, sr_getevtlen( ) 
//		long evtdev;			//	event device, sr_getevtdev( ) 
//		long evttype;			//	event type, sr_getevttype( )  
//		LINEDEV linedev;		//	line device for GlobalCall events, gc_GetLineDev( ) 
//		CRN crn;				//	call reference number for GlobalCall events; 
//								//	if 0, no CRN for this event
//		void* extevtdatap;		//	pointer to additional event data 
//		void *usrattr;			//	user assigned attribute associated with the line device, 
//								//	gc_GetUsrAttr( ) 
//		int cclibid;			//	identification of call control library associated with 
//								//	the event: n = cclib ID number, -1 = unknown 
//		int rfu1;				//	reserved for future use 
//	} METAEVENT, *METAEVENTP; 
//
//	EXTENSIONEVTBLK passed in extevtdatap for GCEV_EXTENSION events
//	typedef struct {
//		unsigned char	 ext_id;
//		GC_PARM_BLK 	 parmblk;
//	} EXTENSIONEVTBLK;
//
//	GC_PARM_BLK passed in extevtdatap for non-GCEV_EXTENSION events
//	typedef struct 
//	{
//		unsigned short		parm_data_size;    /* Size of parm_data_buf in bytes */
//		unsigned char		parm_data_buf[1];  /* Address to the parm data buffer,
//												* a chain of GC_PARM_DATA */ 
//	}GC_PARM_BLK, *GC_PARM_BLKP;
//
//	typedef struct 
//	{
//		unsigned short		set_ID; 		   /* Set ID (two bytes long)*/
//		unsigned short		parm_ID;		   /* Parameter ID (two bytes long) */
//		unsigned char		value_size; 	   /* Size of value_buf in bytes */
//		unsigned char		value_buf[1];	   /* Address to the parm value buffer */
//	}GC_PARM_DATA, *GC_PARM_DATAP;
//
//	GC_INFO populated from a METAEVENT with gc_ResultInfo()
//	typedef struct { 
//		int gcValue; 
//		char *gcMsg; 
//		int ccLibId; 
//		char *ccLibName; 
//		long ccValue; 
//		char *ccMsg; 
//		char *additionalInfo; 
//		} GC_INFO; 
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class: ::CMetaEvent
//
// Description: The Meta Event class is responsible for storing the contents
// of a GC MetaEvent.
//
///////////////////////////////////////////////////////////////////////////////
class CMetaEvent
{
public:
   CMetaEvent();
	CMetaEvent( METAEVENT* a_metaEvent);
	virtual ~CMetaEvent();

	long EventType();
	CRN Crn();
	METAEVENT* MetaEvent();

protected:
	void MetaEvent( METAEVENT* a_metaEvent);

private:
	METAEVENT m_metaEvent;
};

#endif

