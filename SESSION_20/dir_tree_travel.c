/* command line
 * # ./rdirt dir_path
 *
 * 	1) Command line validation : check for right number of arguments 
 * 	2) Command line argument validation : check if the argument is dir 
 * 	3) Print all path names belonging to directory tree rooted at dir_path 
 */ 

#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <errno.h> 
#include <string.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <dirent.h> 

#define TRUE 	1 
#define FALSE 	0 

int is_dir(const char* file_path); 
void r_travel(char* path); 
char* concat_paths(char* dir_name, char* base_name); 


int main(int argc, char* argv[]) 
{
	char* p1 = NULL; 
	char* p2 = NULL; 

	if(argc != 2)
	{
		fprintf(stderr, "%s dir_path\n", argv[0]); 
		exit(EXIT_FAILURE); 
	}

	if(!is_dir(argv[1]))
	{
		fprintf(stderr, "argument to %s must be a valid dir path", 
						argv[0]); 
		exit(EXIT_FAILURE); 
	}

	r_travel(argv[1]); 


	/* 
	p1 = concat_paths("/home/yogeshwar", "CPA"); 
	p2 = concat_paths("/home/yogeshwar/", "CPA"); 
	printf("p1 = %s\n", p1); 
	printf("p2 = %s\n", p2); 

	free(p1); 
	p1 = NULL; 

	free(p2); 
	p2 = NULL; 
	*/ 
	return (0); 
}

void r_travel(char* path) 
{
	DIR* dp = NULL; 
	struct dirent* dentry = NULL; 
	char* abs_path = NULL; 

	dp = opendir(path); 
	assert(dp != NULL); 
	
	printf("DIR:%s\n", path); 
	while((dentry = readdir(dp)) != NULL)
	{
		if((strlen(dentry->d_name) == 1 && !strncmp(dentry->d_name, ".", 1))
			|| 
			(strlen(dentry->d_name) == 2 && !strncmp(dentry->d_name, "..", 2))
		)
			continue; 

		abs_path = concat_paths(path, dentry->d_name); 
		assert(abs_path); 
		if(!is_dir(abs_path)) 
		{
			printf("\t%s\n", dentry->d_name); 
			 
		}
		else 
		{
			r_travel(abs_path); 
		} 

		free(abs_path); 
		abs_path = NULL;

	}

	closedir(dp); 
	dp = NULL; 
}

char* concat_paths(char* dir_name, char* base_name) 
{
	int len_dir_name = strlen(dir_name); 
	int len_base_name = strlen(base_name); 
	int dest_len; 
	char* dest_path = NULL; 	
	int forward_flag = FALSE; 

	if(dir_name[len_dir_name-1] == '/') 
	{
		dest_len = len_dir_name + len_base_name + 1; 
		forward_flag = TRUE; 
	} 
	else 
		dest_len = len_dir_name + len_base_name + 2; 

	dest_path = (char*)calloc(1, dest_len); 
	assert(dest_path != NULL); 

	strncpy(dest_path, dir_name, len_dir_name); 
	if(!forward_flag)
		dest_path[len_dir_name] = '/'; 
	
	if(forward_flag)
		strncpy(dest_path + len_dir_name, base_name, len_base_name); 
	else 
		strncpy(dest_path + len_dir_name + 1, base_name, len_base_name); 

	return (dest_path);

}


int is_dir(const char* file_path) 
{
	struct stat sb; 
	int ret; 

	memset(&sb, 0, sizeof(struct stat)); 
	ret = stat(file_path, &sb); 
	if(ret != 0)
	{
		fprintf(stderr, "stat:%s:%s\n", file_path, strerror(errno)); 
		exit(EXIT_FAILURE); 
	}
	
	return (S_ISDIR(sb.st_mode)); 
}
