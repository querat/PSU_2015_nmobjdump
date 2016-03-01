/*
** dest.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/objdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Feb 23 09:46:15 2016 querat_g
** Last update Tue Feb 23 10:13:09 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include "nmobjdump.h"

/*
** Pseudo destructeur de t_fdata
*/
void	t_fdata_dest(t_fdata *d)
{
  if (!d)
    return ;
  if (d->arch)
    free(d->arch);
  if (d->bits)
    free(d->bits);
  memset(d, 0, sizeof(t_fdata));
  return ;
}

/*
** Pseudo destructeur de t_sect
*/
void	t_sect_dest(t_sect *s)
{
  if (!s)
    return ;

  if (s->head)
    free(s->head);
  if (s->name)
    free(s->name);
  if (s->buf)
    free(s->buf);
  memset(s, 0, sizeof(t_sect));
  return ;
}

/*
** Pseudo destructeur de t_obj
*/
void	t_obj_dest(t_obj *obj)
{
  off_t	i;

  i = 0;
  if (!obj)
    return ;
  free(obj->path);
  if (obj->file)
    fclose(obj->file);
  free(obj->p_head);
  if (obj->sect)
    {
      while (i < obj->head.e_shnum)
	t_sect_dest(&obj->sect[i++]);
      free(obj->sect);
    }
  memset(obj, 0, sizeof(t_obj));
}
