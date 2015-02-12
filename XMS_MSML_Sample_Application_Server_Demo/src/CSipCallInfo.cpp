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
// File Name: CSipCallInfo.cpp
//
// Description: CSipCallInfo class implementation
//
///////////////////////////////////////////////////////////////////////////////
#include "CSipCallInfo.h"

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipCallInfo::CallId(const std::string &callId)
//
// Description: Set SIP message "CallId:" header
//
// Return: void
//
// Parameters: const std::string &callId
//
///////////////////////////////////////////////////////////////////////////////
void CSipCallInfo::CallId( const std::string& callId)
{
   m_callId = callId;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipCallInfo::To(const std::string &to)
//
// Description: Set SIP message "To:" header
//
// Return: void
//
// Parameters: const std::string &to
//
///////////////////////////////////////////////////////////////////////////////
void CSipCallInfo::To( const std::string& to)
{
   m_to = to;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipCallInfo::From(const std::string &from)
//
// Description: Set SIP message "From:" header
//
// Return: void
//
// Parameters: const std::string &from
//
///////////////////////////////////////////////////////////////////////////////
void CSipCallInfo::From( const std::string& from)
{
   m_from = from;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipCallInfo::OfferSdp(const std::string &sdp)
//
// Description: Set SIP message offer SDP
//
// Return: void
//
// Parameters: const std::string &sdp
//
///////////////////////////////////////////////////////////////////////////////
void CSipCallInfo::OfferSdp( const std::string& sdp)
{
   m_offerSdp = sdp;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipCallInfo::AnswerSdp(const std::string &sdp)
//
// Description: Set SIP message answer SDP
//
// Return: void
//
// Parameters: const std::string &sdp
//
///////////////////////////////////////////////////////////////////////////////
void CSipCallInfo::AnswerSdp( const std::string& sdp)
{
   m_answerSdp = sdp;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipCallInfo::MimeType(const std::string &mimeType)
//
// Description: Set SIP message MIME type
//
// Return: void
//
// Parameters: const std::string &mimeType
//
///////////////////////////////////////////////////////////////////////////////
void CSipCallInfo::MimeType( const std::string& mimeType)
{
   m_mimeType = mimeType;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipCallInfo::MimeData(const std::string &mimeData)
//
// Description: Set SIP message MIME data
//
// Return: void
//
// Parameters: const std::string &mimeData
//
///////////////////////////////////////////////////////////////////////////////
void CSipCallInfo::MimeData( const std::string& mimeData)
{
   m_mimeData = mimeData;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipCallInfo::ResponseType(const int &responseType)
//
// Description: Set SIP message response type
//
// Return: void
//
// Parameters: const int &responseType
//
///////////////////////////////////////////////////////////////////////////////
void CSipCallInfo::ResponseType( const int& responseType)
{
   m_responseType = responseType;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CSipCallInfo::ResponseCode(const int &responseCode)
//
// Description: Set SIP message response code
//
// Return: void
//
// Parameters: const int &responseCode
//
///////////////////////////////////////////////////////////////////////////////
void CSipCallInfo::ResponseCode( const int& responseCode)
{
   m_responseCode = responseCode;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CSipCallInfo::CallId()
//
// Description: Access SIP message "CallId:" header
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CSipCallInfo::CallId()
{ 
   return m_callId;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CSipCallInfo::To()
//
// Description: Access SIP message "To:" header
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CSipCallInfo::To()
{
   return m_to;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CSipCallInfo::From()
//
// Description: Access SIP message "From:" header
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CSipCallInfo::From()
{
   return m_from;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CSipCallInfo::OfferSdp()
//
// Description: Access SIP message offer SDP
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CSipCallInfo::OfferSdp()
{
   return m_offerSdp;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CSipCallInfo::AnswerSdp()
//
// Description: Access SIP message answer SDP
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CSipCallInfo::AnswerSdp()
{
   return m_answerSdp;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CSipCallInfo::MimeType()
//
// Description: Access SIP message MIME type
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CSipCallInfo::MimeType()
{
   return m_mimeType;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const std::string & CSipCallInfo::MimeData()
//
// Description: Access SIP message MIME data
//
// Return: const std::string &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const std::string& CSipCallInfo::MimeData()
{
   return m_mimeData;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const int & CSipCallInfo::ResponseType()
//
// Description: Access SIP message response type
//
// Return: const int &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const int& CSipCallInfo::ResponseType()
{
   return m_responseType;
}

///////////////////////////////////////////////////////////////////////////////
// Function: const int & CSipCallInfo::ResponseCode()
//
// Description: Access SIP message response code
//
// Return: const int &
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
const int& CSipCallInfo::ResponseCode()
{
   return m_responseCode;
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CSipCallInfo::IsMsml()
//
// Description: Test if MIME data contains MSML
//
// Return: bool
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
bool CSipCallInfo::IsMsml()
{
   const char* l_msmlTag = "msml version";
   return ( m_mimeData.find( l_msmlTag) != m_mimeData.npos);
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CSipCallInfo::IsDialogExit()
//
// Description: Test if MIME data indicates that the message is a dialog.exit
//
// Return: bool
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
bool CSipCallInfo::IsDialogExit()
{
   const char* l_msmlDialogExitTag = "msml.dialog.exit";
   return ( m_mimeData.find( l_msmlDialogExitTag) != m_mimeData.npos);
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CSipCallInfo::VideoAvailableInAnswerSdp()
//
// Description: Test if video is supported in the answer SDP
//
// Return: bool
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
bool CSipCallInfo::VideoAvailableInAnswerSdp()
{
   const char* l_videoTag = "m=video";
   return ( m_answerSdp.find( l_videoTag) != m_answerSdp.npos);
}

///////////////////////////////////////////////////////////////////////////////
// Function: bool CSipCallInfo::VideoAvailableInOfferSdp()
//
// Description: Test if video is supported in the offer SDP
//
// Return: bool
//
// Parameters: none
//
///////////////////////////////////////////////////////////////////////////////
bool CSipCallInfo::VideoAvailableInOfferSdp()
{
   const char* l_videoTag = "m=video";
   return ( m_answerSdp.find( l_videoTag) != m_answerSdp.npos);
}
