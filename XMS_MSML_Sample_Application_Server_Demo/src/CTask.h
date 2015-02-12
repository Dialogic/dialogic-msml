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
// File Name: CTask.h
//
// Description: Declarations for the task classes
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CTask_h
#define CTask_h

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

///////////////////////////////////////////////////////////////////////////////
// Class: ::ATask
//
// Description: Abstract Task class is responsible for defining the interface 
// and variables common to the concrete classes.
//
///////////////////////////////////////////////////////////////////////////////
class ATask
{
public:
   ATask( const char* a_debugInfo = 0);
   virtual ~ATask();
   virtual void operator () ();
   const char* DebugInfo();
private:
   const char* m_debugInfo;
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CTask0
//
// Description: Concrete template class for a task that is a function object 
// with no parameters.
//
///////////////////////////////////////////////////////////////////////////////
class CTask0 : public ATask
{
public:

   CTask0( boost::function0< void> a_taskFunc, const char* a_debugInfo = 0);
   CTask0( const CTask0& a_task);
   virtual ~CTask0();

   void operator () ();
   CTask0& operator=( const CTask0& a_task);
   boost::function0< void> TaskFunc();

private:
   CTask0();
   boost::function0< void> m_taskFunc;
};

///////////////////////////////////////////////////////////////////////////////
// Class: ::CTask1
//
// Description: Concrete template class for a task that is a function object 
// with one parameter.
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
class CTask1 : public ATask
{
public:
   CTask1( boost::function1< void, T&> a_taskFunc, const T& a_taskData, const char* a_debugInfo = 0);

   CTask1( boost::function1< void, T&> a_taskFunc, const char* a_debugInfo = 0);

   CTask1( const CTask1< T>& a_task);

   virtual ~CTask1();

   void operator () ();

   CTask1< T>& operator=( const CTask1< T>& a_task);

   void TaskData( T& a_taskData);
   T& TaskData();

   boost::function1< void, T&> TaskFunc();

private:
   CTask1();
   boost::function1< void, T&> m_taskFunc;
   T m_taskData;
};

#include "CTask_imp.h"
#endif
