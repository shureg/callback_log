// =====================================================================================
// 
//       Filename:  FileCallbackLog.class.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/06/09 19:27:33
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Alexander Kabanov (aak), alexander.kabanov@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef _GLT_FILECALLBACKLOG_CLASS_INC
#define _GLT_FILECALLBACKLOG_CLASS_INC

#include "callback_log/CallbackLog.class.h"

namespace CALLBACK_LOG
{
   class FileCallbackLog: public CallbackLog
   {
   public:

      FileCallbackLog(const std::string&, const std::string&, LOG_LVL,
	    const std:: string& context="default", bool bind_immediately = true);

   protected:

      void write_message(const std::string&);

      std::string filename;

      CallbackLog* spawn_from_this();

   private:

      FileCallbackLog();

   };
}
#endif //_GLT_FILECALLBACKLOG_CLASS_INC
