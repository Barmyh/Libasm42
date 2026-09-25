#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW  "\033[33m"
#define RESET   "\033[0m"

size_t ft_strlen(const char *s); //declare asm function
int ft_strcmp(const char *s1, const char *s2);
char *ft_strcpy(char *dst, const char *src);
