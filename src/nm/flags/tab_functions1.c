/*
** tab_functions1.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/nm
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Wed Feb 24 17:17:53 2016 querat_g
** Last update Fri Feb 26 15:33:23 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>
#include "nmobjdump.h"

char		d_maj_flag(t_obj *obj, Elf64_Sym *sym)
{
  if (sym->st_shndx >= obj->head.e_shnum)
    return (0);

  if ((obj->sect[sym->st_shndx].head->sh_type  == SHT_DYNAMIC) ||
      (obj->sect[sym->st_shndx].head->sh_type  == SHT_PROGBITS &&
       obj->sect[sym->st_shndx].head->sh_flags == (SHF_ALLOC | SHF_WRITE)))
    return ('D');

  return (0);
}

char		u_min_flag(t_obj *obj, Elf64_Sym *sym)
{
  (void)obj;
  if (ELF64_ST_BIND(sym->st_info) == STB_GNU_UNIQUE)
    return ('u');
  return (0);
}

char		t_maj_flag(t_obj *obj, Elf64_Sym *sym)
{
  if (sym->st_shndx >= obj->head.e_shnum)
    return (0);

  if (obj->sect[sym->st_shndx].head->sh_type  == SHT_PROGBITS		  &&
      obj->sect[sym->st_shndx].head->sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
    return ('T');
  if ((obj->sect[sym->st_shndx].head->sh_type == SHT_INIT_ARRAY) ||
      (obj->sect[sym->st_shndx].head->sh_type == SHT_FINI_ARRAY)  )

    return ('T');
  return (0);
}

char		r_maj_flag(t_obj *obj, Elf64_Sym *sym)
{
  if (sym->st_shndx >= obj->head.e_shnum)
    return (0);
  if (obj->sect[sym->st_shndx].head->sh_type  == SHT_PROGBITS &&
      obj->sect[sym->st_shndx].head->sh_flags == SHF_ALLOC)
    return ('R');
  return (0);
}

char		v_flag(t_obj *obj, Elf64_Sym *sym)
{
  (void)obj;
  if (ELF64_ST_BIND(sym->st_info) == STB_WEAK &&
      ELF64_ST_TYPE(sym->st_info) == STT_OBJECT)
    {
      if (sym->st_shndx == SHN_UNDEF)
        return ('v');
      return ('V');
    }
  return (0);
}
