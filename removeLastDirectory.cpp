#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

///Removes given directory recursivelly.
/** 
 * \param path Path to directory
 */
void removeDir(char *path)
{
        if (access(path, F_OK) != 0)
        {
                return;
        }
        struct dirent *entry = NULL;
        DIR *dir = NULL;
        dir = opendir(path);
        while(entry = readdir(dir))
        {
                DIR *sub_dir = NULL;
                FILE *file = NULL;
                char abs_path[100] = {0};
                if(*(entry->d_name) != '.')
                {
                        sprintf(abs_path, "%s/%s", path, entry->d_name);
                        if(sub_dir = opendir(abs_path))
                        {
                                closedir(sub_dir);
                                removeDir(abs_path);
                        }
                        else
                        {
                                if(file = fopen(abs_path, "r"))
                                {
                                        fclose(file);
                                        remove(abs_path);
                                }
                        }
                }
        }
        remove(path);
}

int main()
{
	removeDir("jfshome/omkar/C++Test/dataHidding");
}
