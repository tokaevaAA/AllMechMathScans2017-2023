#include <sys/time.h>
#include <sys/resource.h>
#include "get_time.h"

/* Вернуть процессорное время, затраченное на текущий
   поток, в сотых долях секунды. Берется время только
   самого потока, время работы системных вызовов не
   прибавляется. */
double get_cpu_time (void)
{
  //struct rusage buf;

  //getrusage (RUSAGE_THREAD, &buf);
           
  //return   buf.ru_utime.tv_sec + buf.ru_utime.tv_usec / 1000000.0;
  return 0;

}

/* Возвращает астрономическое (!) время
   в сотых долях секунды */
double  get_full_time (void)
{
  struct timeval buf;

  gettimeofday (&buf, 0);
           /* преобразуем время в секундах
              в сотые доли секунды */
  return   buf.tv_sec 
           /* преобразуем время в микросекундах
              в сотые доли секунды */
         + buf.tv_usec / 1000000.0;
}
