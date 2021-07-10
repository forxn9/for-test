#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE 100
#define MAX_COLUMN 100
#define OPTIONS_LENGTH 2

enum{
    OPTIONS_ONE=1,
    OPTIONS_TWO,
    OPTIONS_THREE,
    OPTIONS_FOUR,
};


#define CASE_N "-n"
#define CASE_I "-i"
#define CASE_E "-e"


char desktop[MAX_LINE][MAX_COLUMN];
char exec_cat_name[100] = "cat ";

int main(int agrc, char **argv){

    char options[6][100] = {0};
    char name[100] = {0};
    char icon[100] = {0};
    char exec[100] = {0};
    char name_zh[50] = {0};
    FILE *fp;
    
    //判断输入参数个数
    if (agrc < 3)
    {
        printf("not enough argment\n");
        return -1;
    }
    //输入参数赋值
    for (size_t i = 0; i < agrc; i++)
    {
        memcpy(options[i],argv[i],strlen(argv[i]));
    }
    // 利用cat 命令读取desktop文件数据
    char *temp = options[OPTIONS_TWO];
    strcat(exec_cat_name,temp);

    if ((fp = popen(exec_cat_name,"r")) == NULL)
    {
        perror("popen error\n");
        return -1;
    }
    // 将Name Name[zh_CN]　Icon Exec字段赋值给desktop[i]数组
    size_t i=0;
    bool with_zh = false;
    while (fgets(desktop[i], 255, fp) != NULL)
    {
        if (strncmp(desktop[0],"[Desktop Entry]",15))
        {
            return 1;
        }
        // TODO check other desktop rule
        if (strstr(desktop[i],"Name"))
        {
            if (strstr(desktop[i],"[zh_CN]"))
            {
                #if defined(DEBUG)
                int N =strlen(desktop[i]);
                printf("N:%d\n",N);
                for (size_t j = 0; j < strlen(desktop[i]); j++)
                {
                   printf("desktop[%d][%d]:%c\n",i,j,desktop[i][j]);
                }
                #endif // DEBUG
                if (desktop[i][strlen(desktop[i])-2] == ';')
                {
                    memcpy(name_zh,desktop[i],strlen(desktop[i])-3); //直接去掉字符‘;&&"’
                }else
                {
                    memcpy(name_zh,desktop[i],strlen(desktop[i])-2);
                }
                with_zh =true;
            }else
            {
                if (desktop[i][strlen(desktop[i])-2] == ';')
                {
                    memcpy(name,desktop[i],strlen(desktop[i])-2);
                }else
                {
                    memcpy(name,desktop[i],strlen(desktop[i])-1);
                }
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

    // 排除 "-n" "-i" "-e" 以外的情况
    if (strlen(options[OPTIONS_THREE]) != OPTIONS_LENGTH)
    {
        printf("error argument [%s] \n",options[OPTIONS_THREE]);
        if (pclose(fp) == -1) {
            perror("pclose failed\n");
            return -2;
        }
        return -1;
    }
    
    // 函数主题，相应各选项
    if (memcmp(options[OPTIONS_THREE],"-n",OPTIONS_LENGTH) == 0)
    {
        if (with_zh){
            printf("%s或%s\n",name+5,name_zh+13);
        }else{
            printf("%s\n",name+5);
        }
    }
    else if (memcmp(options[OPTIONS_THREE],"-i",OPTIONS_LENGTH) == 0)
    {
        printf("%s",icon+5);
    }
    else if (memcmp(options[OPTIONS_THREE],"-e",OPTIONS_LENGTH) == 0)
    {
        if (strlen(options[OPTIONS_FOUR]))
        {
            char exec_combain[100] = {0};
            //char *ptr = strtok(exec, " ");
            sprintf(exec_combain, "%s > %s", exec+5, options[OPTIONS_FOUR]);
            system(exec_combain);
        }else
        {
            printf("need file path after '-e'\n");
        }      
    }
    else
    {
        printf("without argument -n -i -e !!!\n");
    }
    
    if (pclose(fp) == -1) {
        perror("pclose failed\n");
        return -2;
    }

    return 0;
}


