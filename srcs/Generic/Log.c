/*
** Log.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Generic
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:01:58 2016 Etienne Pasteur
** Last update Sun Jun 26 16:06:29 2016 Etienne Pasteur
*/

#include "Generic.h"

extern uint64_t		on_heap;

static inline string	GetCurrentTime()
{
  char			*ret;
  time_t		t;
  struct tm		*p;

  t = time(NULL);
  ret = xmalloc(sizeof(char) * 50);
  p = localtime(&t);
  strftime(ret, 50, "%d/%m/%y : %T", p);
  return (ret);
}

static inline string	GetCurrentUsage()
{
  int			sizeInByte;

  sizeInByte = (int)((double)(on_heap * CHAR_BIT) / 8);
  if (sizeInByte < 1)
    return (asprintf("MEM : %d b", (int) (on_heap * CHAR_BIT)));
  if (sizeInByte < 1024)
    return (asprintf("MEM : %d B", sizeInByte));
  else if (sizeInByte > 1024 && sizeInByte < 1048576)
    return (asprintf("MEM : %.3f KB", (float)sizeInByte / (float)1024));
  else
    return (asprintf("MEM : %.3f MB", (float)sizeInByte / (float)1048576));
}

static void     OutputLog(LogLevel level, const string time,
                          const string usage, const string content)
{
  if (level == ERROR)
  {
    fprintf(stderr, COLOR_RED "[%s | %s] ERROR : %s" COLOR_RESET "\n",
            time, usage, content);
    exit(EXIT_FAILURE);
  }
  else if (level == SUCCESS)
    fprintf(stdout, COLOR_GRN "[%s | %s] SUCCESS : %s" COLOR_RESET "\n",
            time, usage, content);
  else if (level == WARNING)
    fprintf(stdout, COLOR_YEL "[%s | %s] WARNING : %s" COLOR_RESET "\n",
            time, usage, content);
  else if (level == INFORMATION)
    fprintf(stdout, "[%s | %s] INFORMATION : %s\n",
            time, usage, content);
  else
    fprintf(stdout, "[%s | %s] UNKNOWN LOG LEVEL : %s\n",
            time, usage, content);
}

void			Log(LogLevel level, const string log, ...)
{
/*  va_list		ap;
  string		time;
  string		usage;
  string		content;

  time = GetCurrentTime();
  usage = GetCurrentUsage();
  va_start(ap, log);
  content = vasprintf(log, ap);
  va_end(ap);
  if (content == NULL)
    return;
  OutputLog(level, time, usage, content);
  xfree(time, strlen(time));
  xfree(content, strlen(content));
  xfree(usage, strlen(usage));*/
}
