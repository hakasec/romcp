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

            // Megadrive
            if (!strcmp(buffer, ".md") || !strcmp(buffer, ".gen")
                    || !strcmp(buffer, ".smd") || !strcmp(buffer, ".sg")) {
                systemcopy(ent->d_name, MEGADRIVE);
                free(buffer);
            // SNES
            } else if (!strcmp(buffer, ".smc") || !strcmp(buffer, ".sfc")
                        || !strcmp(buffer, ".fig") || !strcmp(buffer, ".swc")
                        || !strcmp(buffer, ".mgd")) {
                systemcopy(ent->d_name, SNES);
                free(buffer);
            // NES
            } else if (!strcmp(buffer, ".nes")) {
                systemcopy(ent->d_name, NES);
                free(buffer);
            // ZXSpectrum
            } else if (!strcmp(buffer, ".sna") || !strcmp(buffer, ".szx")
                        || !strcmp(buffer, ".z80") || !strcmp(buffer, ".tap")
                        || !strcmp(buffer, ".tzx") || !strcmp(buffer, ".gz")
                        || !strcmp(buffer, ".udi") || !strcmp(buffer, ".mgt")
                        || !strcmp(buffer, ".trd") || !strcmp(buffer, ".scl")
                        || !strcmp(buffer, ".dsk")) {
                systemcopy(ent->d_name, ZXSPECTRUM);
                free(buffer);
            // PlayStation
            } else if (!strcmp(buffer, ".bin") || !strcmp(buffer, ".cue")
                        || !strcmp(buffer, ".cbn") || !strcmp(buffer, ".iso")) {
                systemcopy(ent->d_name, PLAYSTATION);
                free(buffer);
            }

            //if (buffer != NULL)
            //    free(buffer);
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
