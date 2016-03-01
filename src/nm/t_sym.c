/*
** t_sym.c for  in /home/querat_g/tmp/PSU_2015_nmobjdump/src/nm
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Thu Feb 25 16:46:37 2016 querat_g
** Last update Sun Feb 28 16:14:24 2016 querat_g
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

/*
** void* pointer because sent to t_list->print()
*/
void	t_sym_print(void *ptr)
{
  t_sym	*s;

  s = ptr;
  if (!s || s->flag == 'a')
    return ;

  if (s->flag == 'w' || s->flag == 'U')
    printf("                 %c ", s->flag);
  else
    printf("%016lx %c ", s->addr, s->flag);
  printf("%s\n", s->name ? s->name : "NULL");
}

/*
** t_sym de-allocator
*/
void		t_sym_dest(void *ptr)
{
  t_sym		*s;

  s = ptr;
  if (!s)
    return ;
  if (s->name)
    free(s->name);
  free(s);
}

/*
** Sent as parameter to t_list->sort() during symbol sorting
*/
int		t_sym_cmp_underscore(void *p1, void *p2)
{
  t_sym		*first;
  t_sym		*second;
  int		fcount;
  int		scount;

  first = p1;
  second = p2;
  if (!first  || (!first->name)  ||
      !second || (!second->name)  )
    return (0);
  fcount = count_underscores(first->name);
  scount = count_underscores(second->name);

  if ((fcount && scount) && fcount > scount)
    return (1);
  return (0);
}

/*
** Sent as parameter to t_list->sort() during symbol sorting
*/
int		t_sym_cmp(void *p1, void *p2)
{
  t_sym		*first;
  t_sym		*second;
  int		ret;

  first = p1;
  second = p2;

  if (!first  || (!first->name)  ||
      !second || (!second->name)  )
    return (0);

  ret = strcasecmp(skip_underscores(first->name),
		   skip_underscores(second->name));
  return (ret);
}
