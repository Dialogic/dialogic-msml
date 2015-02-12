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
// File Name: Singleton.h
//
// Description: Singleton class declaration
//
///////////////////////////////////////////////////////////////////////////////
#ifndef Singleton_h
#define Singleton_h

#include <cstdlib>

#include <boost/utility.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>

///////////////////////////////////////////////////////////////////////////////
// Class: ::Singleton
//
// Description: The Singleton template class is responsible to make sure that 
// only one instance of the templated type exists and to provide an interface 
// for global access of the singleton instanse.
//
///////////////////////////////////////////////////////////////////////////////
template< typename T>
class Singleton : boost::noncopyable 
{
public:
   virtual ~Singleton() { }
   static boost::shared_ptr<T> Instance () {
      // first check
      if ( !m_instance) {
         // scoped lock
         boost::mutex::scoped_lock lock( m_mutex);

         // second check
         if ( !m_instance )
         {
            m_instance = boost::shared_ptr<T> (new T());
            atexit( &Singleton< T>::Destroy);
         }
      }
      return m_instance;
   }

   // this will assert if the instance is already initialized
   // because the singletom is already initialized, use the non-initializing function.
   template< typename A>
   static boost::shared_ptr<T> Instance ( A a_parm) {
      // first check
      if ( !m_instance) {
         // scoped lock
         boost::mutex::scoped_lock lock( m_mutex);

         // second check
         if ( !m_instance )
         {
            m_instance = boost::shared_ptr<T> (new T( a_parm));
            atexit( &Singleton< T>::Destroy);
         }
         else
         {
            assert(0);
         }
      }
      else
      {
         assert(0);
      }
      return m_instance;
   }

   static void Destroy()
   {
      m_instance.reset();
   }

private:
   static boost::shared_ptr<T> m_instance;
   static boost::mutex m_mutex;
};

template < typename T>
boost::shared_ptr<T> Singleton<T>::m_instance;

template < typename T>
boost::mutex Singleton< T>::m_mutex;

#endif
