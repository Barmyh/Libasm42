#include "libasm.h"

void title(char *msg) {
	int extention = 10;
	printf("\n\n");
	printf(YELLOW "%s\n" RESET, msg);
	for (size_t i = 0; i < strlen(msg) + extention; i++) {
		printf(YELLOW "─" RESET);
	}
	printf("\n\n");
}


void create_file(const char *test) {
        int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
                perror("open error");
                return;
        }
        write(fd, test, strlen(test));
        close(fd);

}


int main(void) {

	// ft_strlen
	title("Test for ft_strlen");
	const char *tests[] = {
		"",
		"a", 
		"hello",
		"42 Luxembourg",
		"a very long and boring string to test and with as you please!",
		NULL};

	for (int i = 0; tests[i]; i++) {
		printf("Test: \"%s\"\n", tests[i]);
		printf(GREEN "mine = %zu" RESET, ft_strlen(tests[i]));
		printf("\n");
		printf(BLUE "libc = %zu" RESET, strlen(tests[i]));
		printf("\n\n");
	}	


	// ft_strcmp
	title("Test for ft_strcmp");
	const char *str1[] = {"abc", "abc", "ab"};
	const char *str2[] = {"abc", "ab", "abc"};

	for (int i = 0; i < 3; i++) {
		printf("Test: str1: \"%s\" str2: \"%s\"\n", str1[i], str2[i]);
		printf(GREEN "mine = %d" RESET, ft_strcmp(str1[i], str2[i]));
		printf("\n");
		printf(BLUE "libc = %d" RESET, strcmp(str1[i], str2[i]));
		printf("\n\n");
	}


	// ft_strcpy
	title("Test for ft_strcpy");
	char dst_mine[100];
	char dst_libc[100];
	for (int i = 0; tests[i]; i++) {
		printf("Test: \"%s\"\n", tests[i]);
		printf(GREEN "mine = %s" RESET, ft_strcpy(dst_mine, tests[i]));
		printf("\n");
		printf(BLUE "libc = %s\n" RESET, strcpy(dst_libc, tests[i]));
		printf("\n\n");
	}


	// ft_write
	title("Test for ft_write");
	for (int i = 0; tests[i]; i++) {

		printf("Test: \"%s\"\n", tests[i]);
		printf(GREEN);
		fflush(stdout);
		ssize_t mine = ft_write(1, tests[i], strlen(tests[i]));
		printf(" | mine = [%zd]\n", mine);
		printf(RESET);
		fflush(stdout);

		printf(BLUE);
		fflush(stdout);
		ssize_t libc = write(1, tests[i], strlen(tests[i]));
		printf(" | libc = [%zd]\n", libc);
		printf(RESET);
		fflush(stdout);
		printf("\n");

	}


	// ft_read
	title("Test for ft_read");
	for (int i = 0; tests[i]; i++) {
		create_file(tests[i]);
		int fd_mine = open("test.txt", O_RDONLY);
		char mine_buf[1024] = {0};

		printf("Test: \"%s\"\n", tests[i]);
		printf(GREEN);
		ssize_t mine = ft_read(fd_mine, mine_buf, strlen(tests[i]));
		printf(" | mine = [%zd] \"%s\"\n", mine, mine_buf);
		printf(RESET);

		int fd_libc = open("test.txt", O_RDONLY);
		char libc_buf[1024] = {0};

		printf(BLUE);
		ssize_t libc = read(fd_libc, libc_buf, strlen(tests[i]));
                printf(" | libc = [%zd] \"%s\"\n", libc, libc_buf);
		printf(RESET);
		printf("\n");
	}
	
	// ft_calloc
	title("Test for ft_calloc");
	size_t sizes[] = {0, 1, 5, 10, 42, 100, 1000};
	size_t array_len = sizeof(sizes) / sizeof(sizes[0]); // (56 bytes / 8 bytes = 7)
	
	for (size_t i = 0; i < array_len; i++) {

		void *mine = ft_calloc(sizes[i], sizeof(int));
		void *libc = calloc(sizes[i], sizeof(int));
		printf("Test for size: %zu\n", sizes[i]);

		if (mine == NULL && libc == NULL)
			printf("size: %zu: both NULL\n", sizes[i]);
		else if (mine == NULL || libc == NULL)
			printf("size: %zu: different\n", sizes[i]);
		else if (memcmp(mine, libc, sizes[i] * sizeof(int)) == 0)
			printf(GREEN "OK\n" RESET);
		else
			printf(RED "KO\n" RESET);
		printf("\n");
		free(mine);
		free(libc);
	}	

	return 0;
}
