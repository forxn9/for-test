#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 100
#define MAX_COLUMN 100
#define CASE_N "-n"
#define CASE_I "-i"
#define CASE_E "-e"

char desktop[MAX_LINE][MAX_COLUMN];
char exec_cat_name[20] = "cat ";

int main(int agrc, char *argv[]){

    char options[6][100] = {0};
    char name[100] = {0};
    char icon[100] = {0};
    char exec[100] = {0};
    char name_zh[50] = {0};
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
    bool with_zh = false;
    while (fgets(desktop[i], 255, fp) != NULL)
    {
        if (strstr(desktop[i],"Name"))
        {
            if (strstr(desktop[i],"[zh_CN]"))
            {
                memcpy(name_zh,desktop[i]+1,strlen(desktop[i])-3);
                with_zh =true;
            }else
            {
                memcpy(name,desktop[i],strlen(desktop[i])-1);
            }
        }
        if (strstr(desktop[i],"Icon"))
        {
            memcpy(icon,desktop[i],sizeof(desktop[i]));
        }
        if (strstr(desktop[i],"Exec"))
        {
            memcpy(exec,desktop[i],strlen(desktop[i])-1);
        }   
        i++;
    }
  
    if (memcmp(options[3],"-n",2) == 0)
    {
        if (with_zh){
            printf("%s或%s",name+5,name_zh+12);
        }else{
            printf("%s",name+5);
        }
    }else if (memcmp(options[3],"-i",2) == 0)
    {
        printf("%s",icon+5);
    }else if (memcmp(options[3],"-e",2) == 0)
    {
        if (options[4])
        {
            char exec_combain[100] = {0};
            //char *ptr = strtok(exec, " ");
            sprintf(exec_combain, "%s > %s", exec+5, options[4]);
            printf("%s",exec_combain);
            system(exec_combain);
        }else
        {
            printf("need file path after '-e' ");
        }
        printf("%s",options[4]);
       
    }else
    {
        printf("without argument -n -i -e !!!\n");
    }
    
    
    if (pclose(fp) == -1) {
        perror("pclose failed");
        return -2;
    }
    return 0;
}


