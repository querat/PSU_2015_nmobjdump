/*
** file.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/objdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Mon Feb 22 16:06:51 2016 querat_g
** Last update Fri Feb 26 14:21:29 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include "nmobjdump.h"

/*
** Checks access rights for a given file path
*/
bool	can_use_file(char *path)
{
  if (access(path, F_OK))
    {
      dprintf(2, "objdump: '%s': No such file\n", path ? path : "");
      return (false);
    }
  if (access(path, R_OK))
    {
      dprintf(2, "objdump: %s: Permission denied\n", path ? path : "");
      return (false);
    }
  return (true);
}

bool	not_recognized(char *path)
{
  dprintf(2, "objdump: %s: File format not recognized\n", path);
  return (false);
}

/*
** memcmp value is the ELF magic code
*/
bool	file_is_elf(t_obj *obj)
{
  size_t	sz;

  sz = fread(&obj->head, 1, sizeof(Elf64_Ehdr), obj->file);
  if (sz < sizeof(Elf64_Ehdr))
    return (not_recognized(obj->path));
  if (memcmp(&obj->head, ELFMAG, SELFMAG))
    return (not_recognized(obj->path));
  return (true);
}
