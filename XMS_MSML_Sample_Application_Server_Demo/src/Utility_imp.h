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
// File Name: Utility_imp.h
//
// Description: Function template implementations of utility functions
//
///////////////////////////////////////////////////////////////////////////////
#ifndef Utility_imp_h
#define Utility_imp_h

#include <sstream>
#include <iomanip>

///////////////////////////////////////////////////////////////////////////////
// Function: std::string ::AsString(T a_value)
//
// Description: Convert value of parameterized type to a std::string
//
// Return: std::string
//
// Parameters: T a_value
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
std::string AsString( T a_value)
{
   std::ostringstream l_stream;
   l_stream << a_value;
   return l_stream.str();
}

///////////////////////////////////////////////////////////////////////////////
// Function: std::string ::AsHexString(T a_value, int a_width)
//
// Description: Convert value of parameterized type to a hex formatted std::string
//
// Return: std::string
//
// Parameters: T a_value
//             int a_width
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
std::string AsHexString( T a_value, int a_width)
{
   std::ostringstream l_stream;
   l_stream << "0x" << std::hex << std::setw( a_width) << std::setfill('0') << std::uppercase << a_value;
   return l_stream.str();
}

#endif
