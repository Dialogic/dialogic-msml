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
//	File Name:		CTask_imp.h
//
//	Description:	CTask template function implemetations
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function: CTask1::CTask1(boost::function1<void, T&> a_taskFunc, const T &a_taskData, const char *a_debugInfo)
//
// Description: Initializing constructor
//
// Return:  
//
// Parameters: boost::function1<void 
//             T&> a_taskFunc 
//             const T &a_taskData 
//             const char *a_debugInfo 
//
///////////////////////////////////////////////////////////////////////////////
#ifndef CTask_imp_h
#define CTask_imp_h

template< typename T>
CTask1<T>::CTask1( boost::function1< void, T&> a_taskFunc, const T& a_taskData, const char* a_debugInfo) 
   : ATask( a_debugInfo)
   , m_taskFunc( a_taskFunc)
   , m_taskData( a_taskData)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CTask1::CTask1(boost::function1<void, T&> a_taskFunc, const char *a_debugInfo)
//
// Description: Initializing constructor
//
// Return:  
//
// Parameters: boost::function1<void 
//             T&> a_taskFunc 
//             const char *a_debugInfo 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
CTask1<T>::CTask1( boost::function1< void, T&> a_taskFunc, const char* a_debugInfo) 
   : ATask( a_debugInfo)
   , m_taskFunc( a_taskFunc)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CTask1::CTask1(const CTask1<T>&a_task)
//
// Description: Initializing constructor
//
// Return:  
//
// Parameters: const CTask1<T>&a_task 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
CTask1<T>::CTask1( const CTask1< T>& a_task) 
   : m_taskFunc( a_task.m_taskFunc)
   , m_taskData( a_task.m_taskData)
{
}

///////////////////////////////////////////////////////////////////////////////
// Function: CTask1::~CTask1()
//
// Description: Destructor
//
// Return:  
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
CTask1<T>::~CTask1()
{
   m_taskFunc.clear();
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CTask1::()()
//
// Description: Function call operator
//
// Return: void 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
void CTask1<T>::operator () () { m_taskFunc(m_taskData); }

///////////////////////////////////////////////////////////////////////////////
// Function: CTask1<T>& CTask1::=(const CTask1<T>&a_task)
//
// Description: Assignment operator
//
// Return: CTask1<T>& 
//
// Parameters: const CTask1<T>&a_task 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
CTask1< T>& CTask1<T>::operator=( const CTask1< T>& a_task)
{
   if ( this != &a_task)
   {
      m_taskFunc = a_task.m_taskFunc;
      m_taskData = a_task.m_taskData;
   }
   return *this;
}

///////////////////////////////////////////////////////////////////////////////
// Function: void CTask1::TaskData(T &a_taskData)
//
// Description: Set the task data
//
// Return: void 
//
// Parameters: T &a_taskData 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
void CTask1<T>::TaskData( T& a_taskData)
{
   m_taskData = a_taskData;
}

///////////////////////////////////////////////////////////////////////////////
// Function: T& CTask1::TaskData()
//
// Description: Access the Task Data
//
// Return: T& 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
T& CTask1<T>::TaskData()
{
   return m_taskData;
}

///////////////////////////////////////////////////////////////////////////////
// Function: boost::function1<void,T&> CTask1::TaskFunc()
//
// Description: Access the task function
//
// Return: boost::function1<void,T&> 
//
// Parameters: none 
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
boost::function1< void, T&> CTask1<T>::TaskFunc()
{
   return m_taskFunc;
}

#endif

