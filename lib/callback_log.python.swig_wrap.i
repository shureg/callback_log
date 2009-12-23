%{
#include "LOG.h"
#include "FileCallbackLog.class.h"
%}

%include "std_string.i"

%ignore LOG;
%include "LOG.h"

%inline
%{
   void LOG(CALLBACK_LOG::LOG_LVL l, const std::string& s)
   {
      CALLBACK_LOG::LOG(l,boost::format(s));
   }
%}

%include "FileCallbackLog.class.h"
