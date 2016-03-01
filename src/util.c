/*
** util.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/objdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Mon Feb 22 15:56:49 2016 querat_g
** Last update Mon Feb 22 15:59:33 2016 querat_g
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nmobjdump.h"

void	*memdup(void *ptr, size_t size)
{
  void	*ret;

  ret = malloc(size);
  if (!ret)
    return (NULL);
  memcpy(ret, ptr, size);
  return (ret);
}

void	*seek_read(FILE *file, off_t off, size_t sz)
{
  char	*ret;

  if (!file)
    return (NULL);
  ret = malloc(sz);
  if (!ret)
    return (NULL);
  if ((fseek(file, off, SEEK_SET)) == -1)
    return (free(ret), NULL);
  if ((fread(ret, 1, sz, file)) != sz)
    return (free(ret), NULL);
  return (ret);
}
