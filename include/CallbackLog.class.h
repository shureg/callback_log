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
#include "boost/ptr_container/ptr_list.hpp"

namespace CALLBACK_LOG
{
   typedef 
      boost::signals2::signal< void (CALLBACK_LOG::LOG_LVL, boost::format) >
      log_signal;

   class CallbackLog
   {
   public:

      CallbackLog(const std::string&, LOG_LVL, const std::string& context,
	    bool bind_immediately=true);

      static unsigned long msg_ctr;

      void set_context(const std::string& context_);

      void spawn_threaded_log();

      void add_threaded_log(CallbackLog* cbl, bool unbind_first = true);

   protected:

      void bind(log_signal&);

      void unbind();

      void process_message(LOG_LVL, boost::format);

      virtual void write_message(const std::string&) = 0;

      const std::string loglvl_str(LOG_LVL);

      const std::string label;

      const std::string timestamp() const;

      LOG_LVL loglvl;

      std::string context;

      virtual CallbackLog* spawn_from_this() = 0;

      boost::signals2::connection log_connection;

      boost::ptr_list< CallbackLog > thread_logs; 
   };
}
#endif //_GLT_CALLBACKLOG_CLASS_INC
