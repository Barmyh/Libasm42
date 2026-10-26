#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define W	"\033[37m"
#define RESET   "\033[0m"

size_t ft_strlen(const char *s); //declare asm function
int ft_strcmp(const char *s1, const char *s2);
char *ft_strcpy(char *dst, const char *src);
ssize_t ft_write(int fd, const char *buf, size_t bytes_count);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);
void *ft_calloc(size_t count, size_t size);

