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
// File Name: CMsmlEvent.h
//
// Description: CMsmlEvent class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CMsmlEvent_h
#define CMsmlEvent_h

#include <string>
#include <map>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CMsmlEvent
//
// Description: The MSML Event class is responsible for parsing and storing the
// contents of an MSML event message.
//
///////////////////////////////////////////////////////////////////////////////
class CMsmlEvent
{
public:
   CMsmlEvent( const std::string& info);
   const std::string& Name();
   std::map<std::string,std::string>& Parms();

   const std::string& MatchedDtmf();
   const std::string& LastDtmf();
   const std::string& ParmValue( const std::string& a_parm);

private:
   std::string m_name;
   std::map<std::string,std::string> m_parms;
   static const std::string m_emptyString;

   CMsmlEvent();
   void AddParm( std::string& name, std::string& value);
};

#endif
