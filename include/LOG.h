// =====================================================================================
// 
//       Filename:  LOG.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/06/09 19:47:48
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Alexander Kabanov (aak), alexander.kabanov@gmail.com
//        Company:  
// 
// =====================================================================================


#ifndef  _GLT_LOG_INC
#define  _GLT_LOG_INC

#include "boost/signals2.hpp"
#include "boost/format.hpp"
#include "boost/thread.hpp"

namespace CALLBACK_LOG
{
   enum LOG_LVL
   {
      DEBUG = 0,
      TRACE = 10,
      INFO = 20,
      WARNING = 30,
      ERROR = 40,
      EXCEPTION = 50,
      EXTERNAL_EXCEPTION = 60
   };

   //! Single-threaded (thread-safe) log
   extern boost::signals2::signal< void (LOG_LVL, boost::format) > ST_LOG;

   extern boost::thread_specific_ptr<
      boost::signals2::signal< void (LOG_LVL, boost::format) > > mt_log_ptr;

   //! Multi-threaded log
   void MT_LOG(LOG_LVL, boost::format);

   //! Automatic log
   /*! Chooses MT_LOG when it is available, 
    *  for the current thread, otherwise
    *  chooses ST_LOG
    */
   void LOG(LOG_LVL, boost::format);
}


#endif   // ----- #ifndef _GLT_LOG_INC  -----
