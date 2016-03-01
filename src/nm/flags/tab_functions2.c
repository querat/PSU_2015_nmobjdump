/*
** tab_functions1.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/nm
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Feb 24 17:17:53 2016 querat_g
** Last update Fri Feb 26 10:31:48 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>
#include "nmobjdump.h"

char		w_flag(t_obj *obj, Elf64_Sym *sym)
{
  (void)obj;
  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK)
    {
      if (sym->st_shndx == SHN_UNDEF)
        return ('w');
      return ('W');
    }
  return (0);
}

char		u_maj_flag(t_obj *obj, Elf64_Sym *sym)
{
  (void)obj;
  return ((sym->st_shndx == SHN_UNDEF) ? 'U' : 0);
}

char		a_maj_flag(t_obj *obj, Elf64_Sym *sym)
{
  (void)obj;
  return ((sym->st_shndx == SHN_ABS) ? 'A' : 0);
}

char		c_maj_flag(t_obj *obj, Elf64_Sym *sym)
{
  (void)obj;
  return ((sym->st_shndx == SHN_COMMON) ? 'C' : 0);
}

char		b_maj_flag(t_obj *obj, Elf64_Sym *sym)
{
  (void)obj;
  if (obj->sect[sym->st_shndx].head->sh_type  == SHT_NOBITS &&
      obj->sect[sym->st_shndx].head->sh_flags == (SHF_ALLOC | SHF_WRITE))
    return ('B');
  return (0);
}
