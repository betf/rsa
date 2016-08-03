#include<stdarg.h>
#include "h/dbg.h"

void debug(const char* format, ...)
{ 
  va_list argp;
  
  va_start(argp, format);
  vprintf(format, argp);
  va_end(argp);
}
