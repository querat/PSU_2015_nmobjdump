/*
** dump_f.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/objdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Feb 21 10:03:22 2016 querat_g
** Last update Tue Feb 23 09:36:28 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>
#include "nmobjdump.h"

bool		fdata_get_bits(t_fdata *data, t_obj *obj)
{
  if (!data || !obj)
    return (false);
  if (obj->head.e_ident[EI_CLASS] == ELFCLASS64)
    data->bits = strdup("64");
  else if (obj->head.e_ident[EI_CLASS] == ELFCLASS32)
    data->bits = strdup("32");
  else
    data->bits = strdup("");
  return (true);
}

void		fdata_get_flag(t_fdata *data, t_obj *obj)
{
  size_t	i;

  if (!data || !obj || !obj->sect)
    return ;

  if (obj->head.e_phnum != 0)
    data->flag |= D_PAGED;
  if (obj->head.e_type == ET_EXEC)
    data->flag |= EXEC_P;
  else if (obj->head.e_type == ET_REL)
    data->flag |= HAS_RELOC;
  else if (obj->head.e_type == ET_DYN)
    data->flag |= DYNAMIC;
  i = 0;
  while (i < obj->head.e_shnum)
    {
      if (obj->sect && obj->sect[i].name &&
	  (!strcmp(obj->sect[i].name, ".symtab") ||
	   !strcmp(obj->sect[i].name, ".dynsym") ))
	data->flag |= HAS_SYMS;
      ++i;
    }
}

void		init_fdata(t_fdata *data, t_obj *obj)
{
  if (!data)
    return ;
  memset(data, 0, sizeof(t_fdata));
  fdata_get_arch(data, obj);
  fdata_get_bits(data, obj);
  fdata_get_flag(data, obj);
}

void		dump_f_option(t_obj *obj)
{
  t_fdata	data;

  if (!obj)
    return ;

  init_fdata(&data, obj);
  printf("\n");
  printf("%s:     file format elf64-x86-64\n"
	 , obj->path ? obj->path : "");
  printf("architecture: i386:x86-64, flags 0x%08x:\n"
	 , data.flag);
  dump_flags(&data);
  printf("start address 0x%016lx\n", obj->head.e_entry);
  printf("\n");

  t_fdata_dest(&data);

  return ;
}
