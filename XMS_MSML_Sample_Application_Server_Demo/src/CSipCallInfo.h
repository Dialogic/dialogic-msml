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
// File Name: CSipCallInfo.h
//
// Description: CSipCallInfo class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CSipCallInfo_h
#define CSipCallInfo_h

#include <string>

///////////////////////////////////////////////////////////////////////////////
// Class: ::CSipCallInfo
//
// Description: The SIP Call INfo class is responsible for storing and querying
// information about a SIP call.
//
///////////////////////////////////////////////////////////////////////////////
class CSipCallInfo
{
public:
   void CallId( const std::string& callId);
   void To( const std::string& to);
   void From( const std::string& from);
   void OfferSdp( const std::string& sdp);
   void AnswerSdp( const std::string& sdp);
   void MimeType( const std::string& mimeType);
   void MimeData( const std::string& mimeData);
   void ResponseType( const int& responseType);
   void ResponseCode( const int& responseCode);

   const std::string& CallId();
   const std::string& To();
   const std::string& From();
   const std::string& OfferSdp();
   const std::string& AnswerSdp();
   const std::string& MimeType();
   const std::string& MimeData();
   const int& ResponseType();
   const int& ResponseCode();

   bool IsMsml();
   bool IsDialogExit();

   bool VideoAvailableInAnswerSdp();
   bool VideoAvailableInOfferSdp();

private:
   std::string m_callId;
   std::string m_to;
   std::string m_from;
   std::string m_offerSdp;
   std::string m_answerSdp;
   std::string m_mimeType;
   std::string m_mimeData;
   int m_responseType;
   int m_responseCode;
};

#endif
