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
      LOG_LVL _loglvl):
   CallbackLog(_label,_loglvl), filename(_filename)
{
   bind();
}

void FileCallbackLog::write_message(const string& msg)
{
   ofstream ofs(filename.c_str(),ios::app);

   ofs << msg;

   ofs.close();
}
