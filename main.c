#include "libasm.h"

void title(char *msg) {
	printf("\n");
	printf(YELLOW "##### %s #####\n" RESET, msg);
	printf("\n");
}

int main(void) {
	
	title("Test for ft_strlen");
	const char *tests[] = { "", "a", "hello", "42 Luxembourg", NULL};

	for (int i = 0; tests[i]; i++) {
		printf("Test: \"%s\"\n", tests[i]);
		printf(GREEN "mine = %zu" RESET, ft_strlen(tests[i]));
		printf("\t| ");
		printf(BLUE "libc = %zu" RESET, strlen(tests[i]));
		printf("\n\n");
	}


	title("Test for ft_strcmp");
	const char *str1[] = {"abc", "abc", "ab"};
	const char *str2[] = {"abc", "ab", "abc"};

	for (int i = 0; i < 3; i++) {
		printf("Test: str1: \"%s\" str2: \"%s\"\n", str1[i], str2[i]);
		printf(GREEN "mine = %d" RESET, ft_strcmp(str1[i], str2[i]));
		printf("\t| ");
		printf(BLUE "libc = %d" RESET, strcmp(str1[i], str2[i]));
		printf("\n\n");
	}

	title("Test for ft_strcpy");
	const char src[] = "Hello World!";
	char dst[100]; 
	printf("Test: \"%s\"\n", src);
	printf(GREEN "mine = %s" RESET, ft_strcpy(dst, src));
	printf("\t| ");
	printf(BLUE "libc = %s\n" RESET, strcpy(dst, src));
	printf("\n\n");

	return 0;

}
