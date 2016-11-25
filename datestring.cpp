#include "datestring.hpp"


std::string dateString(int64_t date_time)
{
  struct tm date_tm;
  localtime_r(&date_time,&date_tm);
  char buffer[256];
  strftime(buffer,sizeof buffer,"%Y-%m-%d %I:%M:%S %p",&date_tm);
  return buffer;
}
