/*
** nm_utils.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/nm
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Feb 26 09:10:59 2016 querat_g
** Last update Sun Feb 28 16:15:07 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>
#include "nmobjdump.h"
#include "list.h"

char	*safe_str_get(t_obj *obj, size_t offset)
{
  char	*tmp;

  if (!obj || !obj->head.e_shnum || !obj->sect ||
      obj->head.e_shstrndx > obj->head.e_shnum)
    return (NULL);
  if (offset > obj->strtab->head->sh_size)
    return (NULL);
  asprintf(&tmp, "%s", obj->strtab->buf + offset);
  return (tmp);
}

/*
** Looks in the obj t_sect array for the section *name
*/
t_sect	*get_t_sect(t_obj *obj, char *name)
{
  off_t	i;

  i = -1;
  if (!name || !obj || !obj->head.e_shnum || !obj->sect)
    return (NULL);
  while (++i < obj->head.e_shnum)
    {
      if ((obj->sect[i].name)		   &&
	  (obj->sect[i].name[0])	   &&
	  (!strcmp(obj->sect[i].name, name)))
	return (&obj->sect[i]);
    }
  return (NULL);
}

bool	set_sym_tables_into_t_obj(t_obj *obj)
{
  if (!obj || !obj->head.e_shnum || !obj->sect)
    return (false);
  obj->symtab = get_t_sect(obj, ".symtab");
  obj->dynsym = get_t_sect(obj, ".dynsym");
  obj->strtab = get_t_sect(obj, ".strtab");
  if (!obj->strtab)
    return (false);
  return (((obj->symtab      && obj->symtab->name  &&
	    obj->symtab->buf && obj->symtab->head) ||
	   (obj->dynsym      && obj->dynsym->name  &&
	    obj->dynsym->buf && obj->dynsym->head) ));
}

Elf64_Sym	*get_next_sym(t_sect *symtab,
			      size_t *off)
{
  Elf64_Sym		*ret;

  if (((*off) + sizeof(Elf64_Sym)) > symtab->head->sh_size)
    return (NULL);
  ret = memdup((void*)((size_t)symtab->buf + (*off)), sizeof(Elf64_Sym));
  if (!ret)
    return (NULL);
  (*off) += sizeof(Elf64_Sym);
  return (ret);
}

t_sect		*get_next_sect(t_obj *obj, size_t *off)
{
  t_sect	*s;

  if (!obj || !obj->sect || !off || (*off) >= obj->head.e_shnum)
    return (NULL);
  s = &obj->sect[(*off)];
  ++(*off);
  return (s);
}
