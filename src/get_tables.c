/*
** get_tables.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/objdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Fri Feb 19 15:51:42 2016 querat_g
** Last update Thu Feb 25 23:48:08 2016 querat_g
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <elf.h>
#include <string.h>
#include "nmobjdump.h"

/*
** Reads the program headers array starting at the file_header.e_phoff offset
** Allocates and Stores it in obj->p_head
*/
bool	get_prog_headers_table(t_obj *obj)
{
  size_t	size;

  obj->p_head = NULL;
  if (!obj || !obj->file)
    return (false);
  size = sizeof(Elf64_Phdr) * obj->head.e_phnum;
  if (!size || !obj->head.e_phoff)
    return (false);
  if ((fseek(obj->file, obj->head.e_phoff, SEEK_SET)) == -1)
    return (false);
  obj->p_head = calloc(size, 1);
  if (!obj->p_head)
    return (false);
  if (fread(obj->p_head, 1, size, obj->file) != size)
    return (false);
  return (true);
}

char	*load_section_into_buffer(t_obj *obj, t_sect *s)
{
  if (!s || !s->head || !obj || !obj->file)
    return (NULL);

  if ((fseek(obj->file, s->head->sh_offset, SEEK_SET)) == -1)
    return (NULL);
  s->buf = calloc(s->head->sh_size, 1);
  if (!s->buf)
    return (NULL);
  if ((fread(s->buf, 1, s->head->sh_size, obj->file)) != s->head->sh_size)
    return (free(s->buf), NULL);

  return (s->buf);
}

char		*get_section_name(t_obj *obj, Elf64_Shdr *h, t_sect *s)
{
  t_sect	text;
  char		*name;

  memset(&text, 0, sizeof(t_sect));
  if (!obj || !obj->file || obj->head.e_shstrndx >= obj->head.e_shnum ||
      !s || !h)
    return (NULL);
  text.head = memdup(&h[obj->head.e_shstrndx], sizeof(Elf64_Shdr));
  if ((text.head) == NULL)
    return (NULL);
  text.buf = seek_read(obj->file, text.head->sh_offset, text.head->sh_size);
  if (!text.buf)
    return (free(text.head), NULL);
  if (s->head->sh_name > text.head->sh_size)
    return (free(text.head), free(text.buf), NULL);
  name = strdup(&text.buf[s->head->sh_name]);

  free(text.head);
  free(text.buf);
  return (name);
}

bool		load_sections_in_t_obj(t_obj *obj, Elf64_Shdr *h)
{
  size_t	i;

  i = 0;
  if (!h)
    return (false);

  obj->sect = calloc(obj->head.e_shnum, sizeof(t_sect));
  if (!obj->sect)
    return (free(h), false);
  while (i < obj->head.e_shnum)
    {
      obj->sect[i].head = memdup(&h[i], sizeof(Elf64_Shdr));
      obj->sect[i].buf = load_section_into_buffer(obj, &obj->sect[i]);
      obj->sect[i].name = get_section_name(obj, h, &obj->sect[i]);
      ++i;
    }
  return (true);
}

/*
** Reads the sections headers array starting at the file_header.e_phoff offset
** Allocates and Stores it in obj->s_head
*/
bool		get_prog_sections_table(t_obj *obj)
{
  size_t	size;
  Elf64_Shdr	*h;

  if (!obj || !obj->file)
    return (false);
  size = sizeof(Elf64_Shdr) * obj->head.e_shnum;
  if (!size || !obj->head.e_shoff)
    return (false);
  if ((fseek(obj->file, obj->head.e_shoff, SEEK_SET)) == -1)
    return (false);
  h = calloc(size, 1);
  if (!h)
    return (false);
  if ((fread(h, 1, size, obj->file)) != size)
    return (free(h), false);
  if (!load_sections_in_t_obj(obj, h))
    return (free(h), false);
  free(h);
  return (true);
}
