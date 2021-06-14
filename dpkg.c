#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


#define DPKG_L "dpkg -L"

int judge_file_exist(char *file_path);
int judge_file_symlink(char *file_path );

char temp[100] = {0};
char output[][50] = {0};
char debname[20];
char exec_debname[20] = "dpkg -L ";

int StorageStr(){
    printf("please input the deb name:");
    scanf("%s",debname);
    strcat(exec_debname,debname);
    
    int i=0;
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
        judge_file_exist(output[i]);
        judge_file_symlink(output[i]);
        memset(temp,0,sizeof(temp));
        i++;
    }
    
    if (pclose(fp) == -1) {
        perror("pclose failed");
        return -2;
    }
    return 0;
    
}


int judge_file_exist( char *file_path)   
{   
    char *temp=file_path;
    if((access(temp,F_OK)) != 0){   
        printf("file %s not exist\n",temp);  
    }


    return 0;   
}

int judge_file_symlink(char *file_path){
    char file_name[100] = "sudo file ";
    FILE *fp;
    char temp[500] = {0};
    strcat(file_name,file_path);
    // printf("AA%s\n",file_name);
    if ((fp = popen(file_name,"r")) == NULL)
    {
        perror("popen error\n");
        return -1;
    }
    fgets(temp, 255, fp);
    // printf("%s\n",temp);
    if(strstr(temp,"broken symbolic link")){
        printf("broken symbolic link\n");
    }
    memset(file_name,0,sizeof(file_name));
    if (pclose(fp) == -1) {
        perror("pclose failed");
        return -2;
    }
    return 0;
}


int main(){
    StorageStr();
}