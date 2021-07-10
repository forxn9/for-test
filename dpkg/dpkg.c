#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LINE 500
#define MAX_COLUMN 150

int judge_file_exist(char *file_path);
int judge_file_symlink(char *file_path );
int judge_file_uid(char *file_path);


char output[MAX_LINE][MAX_COLUMN] = {0};
char debname[20];
char exec_debname[20] = "dpkg -L ";

int StorageStr(char **name){
    int i=0;
    FILE *fp;
    char temp[100] = {0};
    // printf("please input the deb name:");
    // scanf("%s",debname);
    char *debname = name[1];
    strcat(exec_debname,debname);

    if ((fp = popen(exec_debname,"r")) == NULL){
        perror("popen error\n");
        return -1;
    }

    while (fgets(temp, 255, fp) != NULL)
    {
        memcpy(output[i],temp,strlen(temp)-1);
        judge_file_uid(output[i]);
        //judge_file_symlink(output[i]);
        memset(temp,0,sizeof(temp));
        i++;
    }
    
    if (pclose(fp) == -1) {
        perror("pclose failed");
        return -2;
    }
    return 0;
    
}

// 判断文件路径以及文件是否存在,已经弃用
int judge_file_exist( char *file_path)   
{   
    char *temp=file_path;
    if((access(temp,F_OK)) != 0){   
        printf("file %s not exist\n",temp);  
    }
    return 0;   
}

// 通过sudo file file_patch 方式判断符号链接是否正常
int judge_file_symlink(char *file_path){
    char file_name[100] = "sudo file ";
    FILE *fp;
    char temp[500] = {0};
    strcat(file_name,file_path);
    if ((fp = popen(file_name,"r")) == NULL){
        perror("popen error\n");
        return -1;
    }
    fgets(temp, 255, fp);
    if(strstr(temp,"broken symbolic link")){
        printf("%s\n",file_path);
    }
    memset(file_name,0,sizeof(file_name));
    if (pclose(fp) == -1) {
        perror("pclose failed");
        return -2;
    }
    return 0;
}

// 判断文件数组是否正常
int judge_file_uid(char *file_path){
    
    struct stat stat_data;

    // stat函数 可以判断文件是否存在
    if (0 != stat(file_path, &stat_data)) {
        printf("%s\n",file_path);
        return -1;
    }
    // 仅仅判断 /usr 文件属主
    if (!strstr(file_path,"/usr/")){
        return 0;
    }

    if (stat_data.st_uid != 0){
        printf("%s\n",file_path);
    }
    
    return 0;
}

int main(int argc, char **argv){
    char **package_name = argv;
    StorageStr(package_name);
    return 0;
}