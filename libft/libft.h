/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoreno- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 06:10:21 by smoreno-          #+#    #+#             */
/*   Updated: 2019/04/29 03:08:39 by smoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>

# define FLAG_ZEROPAD       (1U << 0U)
# define FLAG_LEFT          (1U << 1U)
# define FLAG_PLUS          (1U << 2U)
# define FLAG_SPACE         (1U << 3U)
# define FLAG_HASH          (1U << 4U)
# define FLAG_CHAR          (1U << 5U)
# define FLAG_SHORT         (1U << 6U)
# define FLAG_LONG          (1U << 7U)
# define FLAG_LONGLONG      (1U << 8U)
# define FLAG_PRECISION     (1U << 9U)
# define FLAG_UPPERCASE     (1U << 10U)
# define FLAG_WILD          (1U << 11U)
# define FLAG_LONGFLOAT     (1U << 12U)
# define IS_DIGIT(c)        ((unsigned int) ((c - '0') < 10))
# define VALID_SPEFLAG      " CcSsplhjlzbDdioOuUxXfF.0+*#-%"
# define VALID_NBOP         "bDdioOuUxXfF"
# define BUFFER_SIZE        64
# define BUFF_SIZEGNL		1

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_lst_str
{
	char				c;
	struct s_lst_str	*next;
}					t_lst_str;

typedef struct		s_lst_args
{
	char			buf[BUFFER_SIZE];
	char			str[5];
	char			*ptr;
	unsigned int	flag;
	int				width;
	int				precision;
	int				base;
	int				len;
	int				swi;
	int				count_print;
	int				buflen;
	int				negatif;
	int				intlen;
	int				i;
	int				j;
	int				err;
	long double		plus;
	int				s_precision;
	long double		save;
	long double		value;
	unsigned int	temp;
	int				padf;
	int				tmp;
	t_lst_str		*first;
	t_lst_str		*list;
}					t_lst_args;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
int					ft_intlen(int n);
size_t				ft_listlen(t_list *lst);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isspace(char c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
int					ft_counter_words(const char *str, char c);
void				ft_sortinttab(int *tab, size_t size);
char				*ft_itoa(int n);
void				ft_putstr(char *str);
void				ft_puttab(char **tab);
void				ft_putchar(char c);
void				ft_putnbr(int nb);
void				ft_putendl(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_wlen(wchar_t *str, t_lst_args *spe);
void				ft_printpad(t_lst_args *spe);
int					nanv(t_lst_args *spe, long double value);
void				ft_buffzerohach(t_lst_args *spe);
int					ft_testmaxw(const char **format, t_lst_args *spe,
		wchar_t wc);
void				ft_rpading(t_lst_args *spe);
int					ft_nulstring(const char **format, t_lst_args *spe,
		char *ptr);
int					ft_string(const char **format, t_lst_args *spe,
		va_list va);
int					ft_wstring(t_lst_args *spe, wchar_t *ptr);
int					ft_pawchar(wchar_t c, t_lst_args *spe, const char **format);
void				ptrnvalue(t_lst_args *spe);
int					ft_pastring(const char **format, t_lst_args *spe,
		char *ptr);
int					ft_putw(wchar_t *w, t_lst_args *spe);
int					ft_loopcheckvalidw(wchar_t *w, t_lst_args *spe);
int					ft_loopwlen(wchar_t *str, t_lst_args *spe);
void				ft_loopwlen2(wchar_t *str, t_lst_args *spe);
int					match_char(char *str, char c);
void				get_base(const char **format, t_lst_args *spe, va_list va);
int					get_precision(const char **format, t_lst_args *spe,
		va_list va);
void				get_wild(const char **format, t_lst_args *spe, va_list va);
void				ft_buffzerop(t_lst_args *spe);
int					ft_pwchar(wchar_t c, t_lst_args *spe);
void				ft_printwchar(char *str, t_lst_args *spe);
int					ft_padwchar(t_lst_args *spe, const char **format);
void				ft_buffhash(t_lst_args *spe);
void				ft_getsign(t_lst_args *spe);
void				ft_printbuff(t_lst_args *spe);
int					ft_nbrlong(t_lst_args *spe, va_list va);
int					ft_get_flags(const char **format, t_lst_args *spe,
		va_list va);
int					get_speflag(const char **format, t_lst_args *spe);
int					ft_print_char(const char **format, t_lst_args *spe,
		va_list va);
int					ft_long_long(t_lst_args *spe, unsigned long long value);
int					ft_nbr(const char **format, t_lst_args *spe, va_list va);
int					ft_printf(const char *format, ...);
int					ft_float(t_lst_args *spe, va_list va);
int					ft_buff_format(t_lst_args *spe);
t_lst_str			*ft_new_lststr(char c);
void				ft_free_lst(t_lst_args *spe);
void				ft_print_lst(t_lst_args *spe);
void				ft_lst_link(const char format, t_lst_args *spe);
int					get_next_line(const int fd, char **line);

#endif
