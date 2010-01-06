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

#include "boost/signals.hpp"
#include "boost/format.hpp"

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

   extern boost::signal< void (LOG_LVL, boost::format) > LOG;
}

#endif   // ----- #ifndef _GLT_LOG_INC  -----
