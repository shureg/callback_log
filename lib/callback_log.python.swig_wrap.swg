%{
#include "LOG.h"
#include "FileCallbackLog.class.h"
%}


%include "std_string.i"

%ignore LOG;
%ignore mt_log_ptr;
%ignore MT_LOG;
%ignore ST_LOG;
%include "LOG.h"

%inline
%{
   void log(CALLBACK_LOG::LOG_LVL l, const std::string& s)
   {
      CALLBACK_LOG::LOG(l,boost::format(s));
   }
%}

%include "CallbackLog.class.h"

%include "FileCallbackLog.class.h"
