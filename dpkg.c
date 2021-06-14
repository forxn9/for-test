#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define DPKG_L "dpkg -L"

int judge_file(char *file_path);

char temp[100] = {0};
char output[][50] = {0};
char debname[20];

char exec_debname[20] = "dpkg -L ";

int StorageStr(){
    printf("please input the deb name:");
    scanf("%s",debname);
    strcat(exec_debname,debname);
    
    int i=0;
   // char temp[20]={0};
    FILE *fp;
    if ((fp = popen(exec_debname,"r")) == NULL)
    {
        perror("popen error\n");
        return -1;
    }

    while (fgets(temp, 255, fp) != NULL)
    {
        memcpy(output[i],temp,strlen(temp)-1);
        //printf("%s\n",output[i]);
        judge_file(output[i]);
        
        memset(temp,0,sizeof(temp));
        i++;
    }
    
    if (pclose(fp) == -1) {
        perror("pclose failed");
        return -2;
    }
    return 0;
    
}


int judge_file( char *file_path)   
{   
    if((access(file_path,F_OK)) != 0){   
        printf("file %s not exist\n",file_path);  
    }   
    return 0;   
}

int main(){
    StorageStr();
}