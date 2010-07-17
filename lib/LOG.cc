// =====================================================================================
// 
//       Filename:  LOG.cc
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  09/06/09 19:48:51
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Alexander Kabanov (aak), alexander.kabanov@gmail.com
//        Company:  
// 
// =====================================================================================

#include "callback_log/LOG.h"

boost::signals2::signal< void (CALLBACK_LOG::LOG_LVL, boost::format) > 
   CALLBACK_LOG::LOG;

boost::thread_specific_ptr<
   boost::signals2::signal< void (CALLBACK_LOG::LOG_LVL, boost::format) > > 
   CALLBACK_LOG::mt_log_ptr;

void CALLBACK_LOG::MT_LOG(CALLBACK_LOG::LOG_LVL lvl, boost::format msg)
{
   (*CALLBACK_LOG::mt_log_ptr)(lvl,msg);
}
