#ifndef LIB_H
# define LIB_H

char            *ft_substr(char *s, int start, int len);
char            *ft_strdup(char *s1);
char            *ft_strchr(char *s, int c);
char            *ft_strtrim(char *s1, char *set);
char            *ft_strjoin(char *s1, char *s2);
char            *ft_strrchr(const char *s, int c);
char            **ft_split(char const *s, char c);
int                     ft_strlen(char *s);
int                     ft_strncmp(char *s1, char *s2, int n);
int                     ft_isalnum(int c);
void            *ft_memcpy(void *restrict dst, const void *restrict src, size_t n);
void            *my_realloc(void *ptr, size_t old_size, size_t new_size);
void            ft_strncpy(char *s, char *d, int size);

#endif
