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


	title("Test for ft_write & and ft_read");
	const char write_msg[] = "Hello World, ft_write version!\n";
	char read_buf[100];

	printf("Testing successful write/read:\n");
	int ret = write(1, write_msg, strlen(write_msg));
	int ft_ret = ft_write(1, write_msg, strlen(write_msg));
	printf("Input two strings to test the read function!\n");
	int ft_rret = ft_read(0, read_buf, sizeof(read_buf) - 1);
	int rret = read(0, read_buf, sizeof(read_buf) - 1);
	printf(GREEN "ft_write return value: [ft_write: %d, errno: %d] | [ft_read: %d, errno: %d]" RESET, ft_ret, errno, ft_rret, errno);
	printf("\t| ");
	printf(BLUE "write return value: [write: %d, errno: %d] | [read: %d, errno: %d]" RESET, ret, rret);
	printf("\n\n");

	printf("Testing invalid write/read:\n");
	ret = write(-1, write_msg, strlen(write_msg));
	ft_ret = ft_write(-1, write_msg, strlen(write_msg));
	rret = read(-1, read_buf, sizeof(read_buf));
	ft_rret = ft_read(-1, read_buf, sizeof(read_buf));
	printf(GREEN "ft_write return value: [ft_write: %d, errno: %d] | [ft_read: %d, errno: %d]" RESET, ft_ret, errno, ft_rret, errno);
	printf("\t| ");
	printf(BLUE "write return value: [write: %d, errno: %d] | [read: %d, errno: %d]" RESET, ret, errno, rret, errno);
	printf("\n\n");
	return 0;

}
