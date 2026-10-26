#include "libasm.h"

void title(char *msg) {
	int extention = 10;
	printf("\n\n");
	printf(YELLOW "%s\n" RESET, msg);
	for (int i = 0; i < strlen(msg) + extention; i++) {
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
	
	// ft_calloc
	title("Test for ft_calloc");

	for (int i = 0; i < 5; i++) {
	    size_t nmemb[] = {1, 5, 10, 42, 100};
	    size_t size[]  = {1, 1, 4, 1, 8};

	    size_t total = nmemb[i] * size[i];

	    unsigned char *mine = ft_calloc(nmemb[i], size[i]);
	    unsigned char *libc = calloc(nmemb[i], size[i]);

	    printf("Test: nmemb = %zu, size = %zu\n",
	        nmemb[i], size[i]);

	    if (mine == NULL || libc == NULL) {
	        printf("Allocation failed\n");
	        free(mine);
	        free(libc);
	        continue;
	    }

	    int mine_zero = 1;
	    int libc_zero = 1;
	    int same = 1;
	    for (size_t j = 0; j < total; j++) {
	      	 if (mine[j] != 0)
	      	     mine_zero = 0;
	      	 if (libc[j] != 0)
	      	     libc_zero = 0;
	      	 if (mine[j] != libc[j])
	       	    same = 0;
	    }
	    printf(" | mine zeroed = %s\n", mine_zero ? "OK" : "FAIL");
	    printf(" | libc zeroed = %s\n", libc_zero ? "OK" : "FAIL");
	    printf(" | same content = %s\n", same ? "OK" : "FAIL");
	    free(mine);
	    free(libc);
	}
 	}	
	return 0;
}
