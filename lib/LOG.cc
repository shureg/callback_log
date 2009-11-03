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

boost::signal< void (CALLBACK_LOG::LOG_LVL, boost::format) > CALLBACK_LOG::LOG;
