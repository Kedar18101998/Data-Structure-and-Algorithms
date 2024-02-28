#define _XOPEN_SOURCE 500 
#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h> 
#include <ftw.h> 
#include <sys/stat.h> 
#include <sys/types.h> 

#define TRUE 1 
#define FALSE 0 
#define NR_NFTW_MAX_OPEN_FILES 10 

typedef int flag_t; 
typedef int bool; 

bool is_dir(const char* path_name); 
int nftw_callback(const char* f_name, const struct stat* sb, int f_type, struct FTW* pos); 

int main(int argc, char* argv[])
{
	bool b_ret; 
	int ret; 

	if(argc != 2)
	{
		fprintf(stderr, "Usage Error : %s dir_name\n", argv[0]); 
		exit(EXIT_FAILURE); 
	}

	if((b_ret = is_dir(argv[1])) == FALSE)
	{
		printf("%s\n", argv[1]); 
		exit(EXIT_SUCCESS); 
	}
	
	ret = nftw(argv[1], nftw_callback, NR_NFTW_MAX_OPEN_FILES, 0); 
	if(ret != 0)
	{
		fprintf(stderr, "nftw:%s:%s\n", argv[1], strerror(errno)); 
		exit(EXIT_FAILURE); 
	}

	exit(EXIT_SUCCESS); 
}

bool is_dir(const char* path_name)
{
	static struct stat stat_buffer; 
	int ret; 

	memset(&stat_buffer, 0, sizeof(struct stat)); 
	ret = stat(path_name, &stat_buffer); 
	if(ret == -1)
	{
		fprintf(stderr, "stat:%s:%s\n", path_name, strerror(errno)); 
		exit(EXIT_FAILURE); 
	}

	return (S_ISDIR(stat_buffer.st_mode) ? TRUE : FALSE); 
}


int nftw_callback(const char* f_name, const struct stat* sb, int f_type, struct FTW* pos)
{
	printf("%s\n", f_name); 
	return (0); 
}
