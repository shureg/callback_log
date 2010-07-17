// =====================================================================================
// 
//       Filename:  FileCallbackLog.class.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/06/09 19:33:12
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Alexander Kabanov (aak), alexander.kabanov@gmail.com
//        Company:  
// 
// =====================================================================================

#include "callback_log/FileCallbackLog.class.h"
#include <fstream>

using namespace CALLBACK_LOG;
using namespace std;

FileCallbackLog::FileCallbackLog(const string& _filename, const string& _label,
      LOG_LVL _loglvl, const string& context, bool bind_immediately):
   CallbackLog(_label,_loglvl,context,bind_immediately), filename(_filename)
{
}

void FileCallbackLog::write_message(const string& msg)
{
   ofstream ofs(filename.c_str(),ios::app);

   ofs << msg;

   ofs.close();
}

CallbackLog* FileCallbackLog::spawn_from_this()
{
   string spf = ( boost::format("%s.%s") 
	 % filename % (boost::this_thread::get_id()) ).str();

   FileCallbackLog* tmp = new FileCallbackLog(spf,label,loglvl,context,false);

   return (CallbackLog*) tmp;
}
