#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void addH(char name[],char descrip[], int quan,char d[], char m[],int y ){
    
    char destination[100] ;
    char destination2[100] ;
    char file_name[256];
    char info[256];
    
    DIR *dir;
    FILE *file;

    dir = opendir("./ARCHIVES");
    if (dir == NULL) {
        mkdir("./ARCHIVES");
    }


    sprintf(destination, "./ARCHIVES/%d",y);
    dir = opendir(destination);
    if (dir == NULL) {
        mkdir(destination);
    }

    
    sprintf(destination2, "%s/%s",destination,m);
    dir = opendir(destination2);
    if (dir == NULL) {
        
        mkdir(destination2);
    }
    
    sprintf(file_name, "%s/%s.txt", destination2,d);
    file = fopen(file_name, "a");
    
    sprintf(info, "%s~~~~%s~~~~%d", name,descrip,quan);
    fprintf(file,"%s\n",info);

    fclose(file);
    closedir(dir);

}

void main(void){
    
    addH("TEST","sold",50,"26","December",2022);

}