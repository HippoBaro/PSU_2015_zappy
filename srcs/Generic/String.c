/*
** String.c for zappy in /home/pasteu_e/rendu/PSU_2015_zappy/srcs/Generic
**
** Made by Etienne Pasteur
** Login   <pasteu_e@epitech.net>
**
** Started on  Sun Jun 26 16:08:06 2016 Etienne Pasteur
** Last update Sun Jun 26 16:09:00 2016 Etienne Pasteur
*/

#include "Generic.h"

string		vasprintf(const char *fmt, va_list ap)
{
    va_list	apcpy;
    size_t	size;
    char	*ret;

    va_copy(apcpy, ap);
    size = (size_t) (vsnprintf(NULL, 0, fmt, apcpy) + 1);
    va_end(apcpy);
    ret = xcalloc(1, size);
    if (vsnprintf(ret, size, fmt, ap) == -1)
      return (NULL);
    return (ret);
}

string		asprintf(const char *fmt, ...)
{
    string	ret;
    va_list	ap;

    va_start(ap, fmt);
    ret = vasprintf(fmt, ap);
    va_end(ap);
    return (ret);
}

string		strappend(string dest, string source, Selection freeOption)
{
    char	*new_str;

    if (dest == NULL)
        new_str = xmalloc(strlen(source) + 1);
    else
        new_str = xmalloc(strlen(dest) + strlen(source) + 1);
    new_str[0] = '\0';
    if (dest != NULL)
        strcat(new_str, dest);
    strcat(new_str, source);
    if ((freeOption == FIRST || freeOption == BOTH)  && dest != NULL)
        xfree(dest, strlen(dest));
    if ((freeOption == SECOND || freeOption == BOTH)  && source != NULL)
        xfree(source, strlen(source));
    return new_str;
}
