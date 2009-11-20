// =====================================================================================
// 
//       Filename:  CallbackLog.class.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/06/09 19:12:20
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Alexander Kabanov (aak), alexander.kabanov@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef _GLT_CALLBACKLOG_CLASS_INC
#define _GLT_CALLBACKLOG_CLASS_INC

#include "boost/format.hpp"
#include <string>
#include "callback_log/LOG.h"

namespace CALLBACK_LOG
{
   class CallbackLog
   {
   public:

      CallbackLog(const std::string&, LOG_LVL);

      static unsigned long msg_ctr;

   protected:

      void bind();

      void process_message(LOG_LVL, boost::format);

      virtual void write_message(const std::string&) = 0;

      const std::string loglvl_str(LOG_LVL);

      const std::string label;

      const std::string timestamp() const;

      LOG_LVL loglvl;
   };
}
#endif //_GLT_CALLBACKLOG_CLASS_INC
