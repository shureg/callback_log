// =====================================================================================
// 
//       Filename:  CallbackLog.class.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/06/09 19:18:18
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Alexander Kabanov (aak), alexander.kabanov@gmail.com
//        Company:  
// 
// =====================================================================================

#include "callback_log/CallbackLog.class.h"
#include "boost/bind.hpp"
#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace CALLBACK_LOG;
using namespace std;

unsigned long CallbackLog::msg_ctr = 0;

CallbackLog::CallbackLog(const string& _label, LOG_LVL _loglvl,
      const string& context, bool bind_immediately): 
   label(_label), loglvl(_loglvl), context(context)
{
   if(bind_immediately) bind(ST_LOG);
}

CallbackLog::~CallbackLog(){}

void CallbackLog::bind(log_signal& log)
{
   log_connection = 
      log.connect( boost::bind(&CallbackLog::process_message,this,_1,_2) );
}

void CallbackLog::unbind()
{
   log_connection.disconnect();
}

void CallbackLog::spawn_threaded_log()
{
   if( mt_log_ptr.get() == 0) mt_log_ptr.reset(new log_signal);

   CallbackLog* new_log = spawn_from_this();
   new_log->unbind();
   new_log->bind(*mt_log_ptr);
   thread_logs.push_back(new_log);
}

void CallbackLog::add_threaded_log(CallbackLog* cbl, bool unbind_first)
{
   if( mt_log_ptr.get() == 0) mt_log_ptr.reset(new log_signal);

   if (unbind_first)
      cbl->unbind();
   
   cbl->bind(*mt_log_ptr);
   thread_logs.push_back(cbl);
}

const std::string CallbackLog::loglvl_str(LOG_LVL lvl)
{
   if (lvl == DEBUG)
      return "DEBUG";
   else if (lvl == TRACE)
      return "TRACE";
   else if (lvl == INFO)
      return "INFO";
   else if (lvl == WARNING)
      return "WARNING";
   else if (lvl == ERROR)
      return "ERROR";
   else if (lvl == EXCEPTION)
      return "EXCEPTION";
   else if (lvl == EXTERNAL_EXCEPTION)
      return "EXTERNAL_EXCEPTION";
   else
      LOG(EXCEPTION,boost::format("Log level %d is not valid") % lvl);
}

void CallbackLog::process_message(LOG_LVL msglvl, boost::format msg)
{
   if(msglvl >= loglvl)
   {
      string new_msg_str = 
	 (boost::format("%s | {%s} <%s: %s> - %s - [%d] : %s") 
	  % timestamp() % ( boost::this_thread::get_id() ) % label % context
	  % loglvl_str(msglvl) % ++(CallbackLog::msg_ctr) % msg.str()).str();

      write_message(new_msg_str);

      if(msglvl == EXCEPTION) throw new_msg_str.c_str();
   }
}

const string CallbackLog::timestamp() const
{
   return boost::posix_time::to_simple_string( 
	 boost::posix_time::microsec_clock::local_time() );
}

void CallbackLog::set_context(const std::string& context_)
{
   context = context_;
}
