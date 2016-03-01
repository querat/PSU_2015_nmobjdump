/*
** dump_line.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/objdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Sun Feb 21 10:14:39 2016 querat_g
** Last update Sun Feb 21 10:18:06 2016 querat_g
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
** May the holy moulinette appreciate this shit because
** it sure took me some time to format ...
*/
void		dump_char_line(char *buf, size_t lft)
{
  size_t	i;

  i = 0;
  while (i < 16 && i < lft)
    {
      printf("%c", isprint(buf[i]) ? buf[i] : '.');
      ++i;
    }
  while (i < 16)
    {
      printf(" ");
      ++i;
    }
}

void		dump_hex_line(char *buf, size_t lft)
{
  size_t	i;

  i = 0;
  while (i < 16 && i < lft)
    {
      if (i && !(i % 4))
	putchar(' ');
      printf("%x", (unsigned int)(((buf[i] & 0xF0) >> 4)));
      printf("%x", (unsigned int)(buf[i] & 0x0F));
      ++i;
    }
  while (i < 16)
    {
      if (i && !(i % 4))
	printf(" ");
      printf("  ");
      ++i;
    }
    printf("  ");
}

int		get_pad(size_t max)
{
  int		pow;
  size_t	plus;

  plus = 0x100;
  pow = 4;

  while (plus < max)
    {
      plus <<= 4;
      ++pow;
    }
  if (pow > 4)
    --pow;
  if (pow > 4)
    --pow;
  return (pow + '0');
}

void		dump_offset(size_t i, size_t off, size_t size)
{
  char		str[32];
  size_t	max;

  max = off + size;
  strcpy(str, " %03lx ");
  str[3] = (get_pad(max));
  printf(str, i);
}

void		hex_dump(char *buf, size_t size, size_t off)
{
  size_t	i;

  i = 0;
  if (!buf || !size)
    return ;
  while (i < size)
    {
      dump_offset(i + off, size, off);
      dump_hex_line(&buf[i], (size - i));
      dump_char_line(&buf[i], (size - i));
      printf("\n");
      i += 16;
    }
}
