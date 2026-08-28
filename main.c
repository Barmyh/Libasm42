#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *s); //declare asm function
char *ft_strcpy(char *dest, const char *src);
int ft_strcmp(const char *s1, const char *s2);

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
	return 0;
}
