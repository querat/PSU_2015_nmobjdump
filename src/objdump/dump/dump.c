/*
** dump.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/objdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Feb 19 15:45:29 2016 querat_g
** Last update Mon Feb 22 16:41:45 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <ctype.h>
#include "nmobjdump.h"

/*
** Used by is_ignored_sec()
**
** some sections are arbitrarly ignored by libbfd, used by objdump.
** Because fuck logic.
*/
static char	*tab[] =
  {
    ".rela.eh_frame",
    ".shstrtab",
    ".symtab",
    ".bss",
    ".tbss",
    ".rela.text",
    ".rela.data",
    ".rela.init",
    ".rela.rodata",
    ".rela.fini_array",
    ".rela.data.rel",
    ".rela.init_array",
    ".rela.rodata",
    ".rela__devtable",
    ".strtab",
    ""
  };

bool		is_ignored_sect(char *name)
{
  int		i;
  i = 0;
  if (name[0] &&
      ((!strncmp(name, ".rela.debug", 11)) ||
       (!strncmp(name, ".rela.text", 10))))
    return (true);
  while (tab[i][0])
    if (!strcmp(tab[i++], name))
      return (true);
  return (false);
}

void		dump_section_header(t_sect *s)
{
  if (!s || !s->name || is_ignored_sect(s->name))
    return ;

  if (s->head->sh_size)
    {
      printf("Contents of section %s:\n", s->name ? s->name : "");
      hex_dump(s->buf, s->head->sh_size, s->head->sh_addr);
    }
}

void		dump_sections_headers_table(t_obj *obj)
{
  size_t	i;
  size_t	size;

  size = obj->head.e_shnum;
  i = 0;

  if (!obj || !obj->sect)
    return ;

  dump_f_option(obj);

  while (i < size)
    {
      dump_section_header(&obj->sect[i]);
      ++i;
    };
}

void		dump_program_header(Elf64_Phdr *h)
{
  printf(GREEN);
  printf("Dumping program Header -------------------------------\n");
  printf("p_type\t\t\t%d\n", h->p_type);
  printf("p_flags\t\t\t%d\n", h->p_flags);
  printf("p_offset\t\t%lu\n", h->p_offset);
  printf("p_vaddr\t\t\t%lx\n", h->p_vaddr);
  printf("p_paddr\t\t\t%lx\n", h->p_paddr);
  printf("p_filesz\t\t%lx\n", h->p_filesz);
  printf("p_memsz\t\t\t%lx\n", h->p_memsz);
  printf("p_align\t\t\t%lx\n", h->p_align);
  printf("!Phdr ------------------------------------------------\n");
  printf(WHITE);
}

void		dump_program_headers_table(Elf64_Phdr *array, size_t size)
{
  size_t	i;

  i = 0;
  if (!array)
    return ;
  while (i < size)
    {
      dump_program_header(&array[i]);
      ++i;
    };
  putchar('\n');
}
