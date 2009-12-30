%{
#include "LOG.h"
#include "FileCallbackLog.class.h"
%}


%include "std_string.i"

%ignore LOG;
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
