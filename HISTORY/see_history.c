#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int direc(const char *dest)
{
	struct dirent *de; 
	DIR *dr; 
    dr= opendir(dest);
	if (dr == NULL) 
	{
		printf("DIRECTORY DOESN'T EXIST" );
        return 0;	
	}
	while ((de = readdir(dr)) != NULL)
			printf("%s\n", de->d_name);
	closedir(dr);
    return 0;
}




void seeH(void){
    
    char destination[100] ;
    char destination2[100] ;
    char file_name[256];
    char history;
    char d[256];
    char m[256];
    int y;
    
    FILE *file;

    direc("./ARCHIVES");   
    scanf("%d", &y);
    sprintf(destination, "./ARCHIVES/%d",y);
    
    direc(destination);
    scanf("%s",&m);
    sprintf(destination2, "%s/%s",destination,m);

    direc(destination2);
    scanf("%s",&d);
    sprintf(file_name, "%s/%s.txt", destination2,d);

    file = fopen(file_name, "r");
    
    while((history = fgetc(file)) != EOF)
      printf("%c", history);

    fclose(file);
    

}

int main(void){
    

    seeH();

    system("pause");  
    return 0;
}