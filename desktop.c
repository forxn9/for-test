#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define MAX_LINE 50
#define MAX_COLUMN 50
#define CASE_N "-n"
#define CASE_I "-i"
#define CASE_E "-e"

char desktop[MAX_LINE][MAX_COLUMN];
char exec_cat_name[20] = "cat ";

int main(int agrc, char *argv[]){

    char options[5][100] = {0};
    char name[20] = {0};
    char icon[30] = {0};
    char exec[30] = {0};
    FILE *fp;
    
    if (agrc < 3)
    {
        printf("not enough argment\n");
        return -1;
    }
    
    for (size_t i = 0; i < agrc; i++)
    {
        memcpy(options[i],argv[i],sizeof(argv[i])+1);
    }

    char *temp = options[2];
    strcat(exec_cat_name,temp);

    if ((fp = popen(exec_cat_name,"r")) == NULL)
    {
        perror("popen error\n");
        return -1;
    }
    size_t i=0;
    while (fgets(desktop[i], 255, fp) != NULL)
    {
        // printf("%s",desktop[i]);
        if (strstr(desktop[i],"Name"))
        {
            memcpy(name,desktop[i],sizeof(desktop[i]));
        }
        if (strstr(desktop[i],"Icon"))
        {
            memcpy(icon,desktop[i],sizeof(desktop[i]));
        }
        if (strstr(desktop[i],"Exec"))
        {
            memcpy(exec,desktop[i],sizeof(desktop[i]));
        }   
        i++;
    }
  
    if (memcmp(options[3],"-n",2) == 0)
    {
        printf("%s",name+5);
    }else if (memcmp(options[3],"-i",2) == 0)
    {
        printf("%s",icon+5);
    }else if (memcmp(options[3],"-e",2) == 0)
    {
        system(exec+5);
    }else
    {
        printf("error argument!!!\n");
    }
    
    
    if (pclose(fp) == -1) {
        perror("pclose failed");
        return -2;
    }
    return 0;
}


