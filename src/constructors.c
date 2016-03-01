/*
** dest.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/objdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Feb 23 09:46:15 2016 querat_g
** Last update Tue Feb 23 09:48:59 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include "nmobjdump.h"

/*
** Pseudo constructeur de t_obj
*/
bool	t_obj_const(t_obj *obj, char *path)
{
  if (!obj || !path)
    return (false);
  obj = memset(obj, 0, sizeof(t_obj));
  if (!can_use_file(path))
    return (t_obj_dest(obj), false);
  if (!(obj->path = strdup(path)))
    return (t_obj_dest(obj), false);
  if (!(obj->file = fopen(path, "r")))
    return (t_obj_dest(obj), false);
  if (!(file_is_elf(obj)))
    return (t_obj_dest(obj), false);
  get_prog_headers_table(obj);
  if (!get_prog_sections_table(obj))
    return (t_obj_dest(obj), false);
  return (true);
}
