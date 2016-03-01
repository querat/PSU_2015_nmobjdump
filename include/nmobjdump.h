/*
** nmobjdump.h for  in /home/querat_g/tmp/PSU_2015_nmobjdump
**
** Made by querat_g
** Login   <querat_g@epitech.net>
**
** Started on  Tue Feb 16 10:03:58 2016 querat_g
** Last update Sun Feb 28 16:15:19 2016 querat_g
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

#include <elf.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

# ifndef DEBUG
#  define DEBUG				0
# endif

/*
** BFD macros
*/
# define BFD_NO_FLAGS			0x00
# define HAS_RELOC			0x01
# define EXEC_P				0x02
# define HAS_LINENO			0x04
# define HAS_SYMS			0x10
# define HAS_LOCALS			0x20
# define DYNAMIC			0x40
# define WP_TEXT			0x80
# define D_PAGED			0x100
# define BFD_IS_RELAXABLE		0x200
# define BFD_TRADITIONAL_FORMAT		0x400
# define BFD_IN_MEMORY			0x800
# define HAS_LOAD_PAGE			0x1000
# define BFD_LINKER_CREATED		0x2000
# define BFD_DETERMINISTIC_OUTPUT	0x4000
# define BFD_COMPRESS			0x8000
# define BFD_DECOMPRESS			0x10000
# define BFD_PLUGIN			0x20000

/*
** Colors
*/
# define RED		"\033[1;31m"
# define GREEN		"\033[1;32m"
# define YELLOW		"\033[1;33m"
# define BROWN		"\033[0;33m"
# define BLUE		"\033[1;34m"
# define PINK		"\033[1;35m"
# define CYAN		"\033[1;36m"
# define WHITE		"\033[0m"

/*
** Holds the header of a section, it's name and its raw data
*/
typedef struct	s_sect
{
  Elf64_Shdr	*head;
  char		*name;
  char		*buf;
}		t_sect;

/*
** Used for easier processing of ELF files
*/
typedef struct	s_obj
{
  char		*path;
  FILE		*file;
  Elf64_Ehdr	head;
  Elf64_Phdr	*p_head;
  t_sect	*sect;
  t_sect	*symtab;
  t_sect	*dynsym;
  t_sect	*strtab;
  t_list	*symlist;
}		t_obj;

/*
** used by my_objdump for holding $(objdump -f) informations
*/
typedef struct	s_fdata
{
  int		flag;
  char		*arch;
  char		*bits;
}		t_fdata;

typedef struct	s_sym
{
  size_t	addr;
  char		*name;
  char		flag;
}		t_sym;

int		main(int ac, char **argv);

/*
** Misc functions
*/
void		*memdup(void *ptr, size_t size);

/*
** Objdump specific functions
*/
bool		objdump_core(FILE *file);
bool		objdump_ret(FILE *file, bool val);
bool		not_recognized(char *path);
bool		is_implemented(FILE *file, Elf64_Ehdr *head);
bool		objdump(char *path);

/*
** Dumping functions
*/
void		dump_section_header(t_sect *s);
void		dump_sections_headers_table(t_obj *obj);
void		dump_program_header(Elf64_Phdr *h);
void		dump_program_headers_table(Elf64_Phdr *h, size_t size);
void		dump_f_option(t_obj *obj);
void		dump_char_line(char *buf, size_t lft);
void		dump_hex_line(char *buf, size_t lft);
int		get_pad(size_t max);
void		dump_offset(size_t i, size_t off, size_t size);
void		hex_dump(char *buf, size_t size, size_t off);
void		dump_flags(t_fdata *data);
char		*get_arch(t_obj *obj);
bool		fdata_get_arch(t_fdata *data, t_obj *obj);
bool		not_recognized(char *path);

/*
** Elf file processing
*/
bool		can_use_file(char *path);
bool		file_is_elf(t_obj *obj);
bool		read_elf_header(char *path, FILE *file, Elf64_Ehdr *head);
void		*seek_read(FILE *file, off_t off, size_t size);

/*
** Program headers
*/
bool		get_prog_headers_table(t_obj *obj);

/*
** Sections headers
*/
bool		get_prog_sections_table(t_obj *obj);
t_sect		*get_section_by_index(t_obj *obj, size_t index);
void		print_section_name(t_obj *obj, Elf64_Shdr *s);

/*
** Pseudo-destructors & constructors
*/
void		t_obj_dest(t_obj *obj);
bool		t_obj_const(t_obj *obj, char *path);
void		t_sect_dest(t_sect *s);
void		t_fdata_dest(t_fdata *d);

/*
** NM functions
*/
char		lower_case(char c);
t_sect		*get_next_sect(t_obj *obj, size_t *off);

/*
** char (*tab)(t_obj*, Elf64) functions
*/
char		get_flag(t_obj *obj, Elf64_Sym *sym);
char		d_maj_flag(t_obj *obj, Elf64_Sym *sym);
char		u_min_flag(t_obj *obj, Elf64_Sym *sym);
char		t_maj_flag(t_obj *obj, Elf64_Sym *sym);
char		r_maj_flag(t_obj *obj, Elf64_Sym *sym);
char		v_flag(t_obj *obj, Elf64_Sym *sym);
char		w_flag(t_obj *obj, Elf64_Sym *sym);
char		u_maj_flag(t_obj *obj, Elf64_Sym *sym);
char		a_maj_flag(t_obj *obj, Elf64_Sym *sym);
char		c_maj_flag(t_obj *obj, Elf64_Sym *sym);
char		b_maj_flag(t_obj *obj, Elf64_Sym *sym);
char		unknown_flag(t_obj *obj, Elf64_Sym *sym);
int		t_sym_cmp(void *p1, void *p2);
int		t_sym_cmp_underscore(void *p1, void *p2);
void		t_sym_dest(void *ptr);
void		t_sym_print(void *ptr);
char		*skip_underscores(char *str);
int		count_underscores(char *str);

/*
** nm_utils.c
*/
Elf64_Sym	*get_next_sym(t_sect *symtab,
			      size_t *off);
bool		set_sym_tables_into_t_obj(t_obj *obj);
t_sect		*get_t_sect(t_obj *obj, char *name);
char		*safe_str_get(t_obj *obj, size_t offset);

#endif /* !nmobjdump.h */
