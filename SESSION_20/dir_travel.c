#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <string.h> 
#include <dirent.h> 


int main(int argc, char* argv[])
{
	DIR* dp = NULL; 
	struct dirent* dentry = NULL; 

	if(argc != 2)
	{
		fprintf(stderr, "usage error:%s dir_path\n", argv[0]); 
		exit(EXIT_FAILURE); 
	}

	dp = opendir(argv[1]); 
	assert(dp); 

	while((dentry = readdir(dp)) != NULL)
	{
		if((strlen(dentry->d_name) == 1 && !strncmp(dentry->d_name, ".", 1)) || 
			(strlen(dentry->d_name) == 2 && !strncmp(dentry->d_name, "..", 2)))
			continue; 
		if(dentry->d_type == DT_DIR) 
			printf("[DIR]\t\t");
		else 
			printf("[NONDIR]\t"); 
		printf("%s\n", dentry->d_name); 
	} 

	closedir(dp); 
	dp = NULL; 

	return (EXIT_SUCCESS); 
}
