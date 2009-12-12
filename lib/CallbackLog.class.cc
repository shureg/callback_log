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

CallbackLog::CallbackLog(const string& _label, LOG_LVL _loglvl): 
   label(_label), loglvl(_loglvl)
{}

void CallbackLog::bind()
{
   LOG.connect( boost::bind(&CallbackLog::process_message,this,_1,_2) );
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
   else
      LOG(EXCEPTION,boost::format("Log level %d is not valid") % lvl);
}

void CallbackLog::process_message(LOG_LVL msglvl, boost::format msg)
{
   if(msglvl >= loglvl)
   {
      string new_msg_str = 
	 (boost::format("%s | <%s> - %s - [%d] : %s") 
	  % timestamp() % label 
	  % loglvl_str(msglvl) % ++(CallbackLog::msg_ctr) % msg.str()).str();

      write_message(new_msg_str);

      if(msglvl >= EXCEPTION) throw new_msg_str.c_str();
   }
}

const string CallbackLog::timestamp() const
{
   return boost::posix_time::to_simple_string( 
	 boost::posix_time::microsec_clock::local_time() );
}
