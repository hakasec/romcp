#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "romcp.h"

int main(int argc, char* argv[])
{
    //if no args given, program will prompt the user to enter one
    if (argc < 2) {
        printf("Please enter a directory.\n");
        printf("Usage: romcp [DIRECTORY]\n");
        return 1;
    }

    DIR *dir;
    struct dirent *ent;
    int i;

    char* buffer;
    int length;
    

    //check if the dir exists
    if ((dir = opendir(argv[1])) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            length = strlen(ent->d_name);

            for (i = length-1; i > 0; i--) {
                if (ent->d_name[i] == '.') {
                    buffer = (char*) malloc((length-i)+1);
                    strncpy(buffer, &ent->d_name[i], length-i);
                    strcat(buffer, "\0");
                    //printf("%s\n%s\n", buffer, ent->d_name);
                    break;
                }

            }

            if (strcmp(buffer, ".md") == 0 || strcmp(buffer, ".gen" == 0)
                    || strcmp(buffer, ".smd") == 0 || strcmp(buffer, ".sg") == 0) {
                systemcopy(ent->d_name, MEGADRIVE);
                free(buffer);

            } else if (strcmp(buffer, ".smc") == 0 || strcmp(buffer, ".sfc" == 0)
                        || strcmp(buffer, ".fig") == 0 || strcmp(buffer, ".swc" == 0)
                        || strcmp(buffer, ".mgd") == 0) {
                systemcopy(ent->d_name, SNES);
                free(buffer);
            }


        }

        closedir(dir);

     } else {
        printf("Could not open directory\n");
     }

    return 0;
}

void systemcopy(char* src, char* dest)
{
    //allocating mem for command string, plus 10 for "cp", null char and spaces
    char* command = (char*) malloc(strlen(src) + strlen(dest) + 5);
    strcpy(command, "cp ");
    strcat(command, src);
    strcat(command, " ");
    strcat(command, dest);
    strcat(command, "\0"); //append the null char

    printf("%s\n", command);
    system(command); //execute command
    free(command); //free command
}
