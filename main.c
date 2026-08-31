#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

size_t ft_strlen(const char *s); //declare asm function
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
// ssize_t ft_read(int fd, void *buf, size_t count);


int main(void) {

	printf("### test for: ft_strlen ###");
	const char *tests[] = { "", "a", "hello", "42 Luxembourg", NULL};

	for (int i = 0; tests[i]; i++)
		printf("\"%s\"  mine=%zu  libc=%zu\n", tests[i], ft_strlen(tests[i]), strlen(tests[i]));

	printf("\n");
	printf("### test for: ft_strcpy ###");
	char dest_mine[100];
	char dest_libc[100];

	for (int i = 0; tests[i]; i++)
	{
		ft_strcpy(dest_mine, tests[i]);
		strcpy(dest_libc, tests[i]);
		printf("\"%s\"  mine=\"%s\"  libc=\"%s\"\n", tests[i], dest_mine, dest_libc);
	}

	printf("\n");
	printf("### test for: ft_strcmp ###");
	const char *pairs[][2] = {{"hello", "hello"}, {"abc", "abd"}, {"abc", "abc "}, {"", ""}, {"42", "24"}};

	for (int i = 0; i < 5; i++) {
		printf("mine=%-4d libc=%-4d  (\"%s\" vs \"%s\")\n",
			ft_strcmp(pairs[i][0], pairs[i][1]),
			strcmp(pairs[i][0], pairs[i][1]),
        		pairs[i][0], pairs[i][1]);
	}

	printf("\n");
	printf("### test for: ft_write ###");
	const char *w_msg = "write message: please work";

	errno = 0;
	ssize_t mine = ft_write(1, w_msg, strlen(w_msg));
	int mine_errno = errno;

	errno = 0;
	ssize_t libc = write(1, w_msg, strlen(w_msg));
	int libc_errno = errno;

	printf("return: mine=%zd libc=%zd\n", mine, libc);
	printf("errno : mine=%d libc=%d\n", mine_errno, libc_errno);

	return 0;

}
