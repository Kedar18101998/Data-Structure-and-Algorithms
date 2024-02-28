#include <dirent.h> 

void r_travel(const char* path)
{
    DIR* dp = NULL; 
    struct dirent* dentry = NULL; 

    dp = opendir(path); 
    assert(dp != NULL); 

    while((dentry = readdir(dp)) != NULL)
    {
        if(dentry->d_type != DT_DIR)
            printf("%s\n", dentry->d_name); 
        else     
            r_travel(path + "\\" + dentry->d_name); 
    }
}