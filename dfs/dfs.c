#include <stdio.h>
#include <string.h>
#include<malloc.h>

void dfs(char *S, int len, char **res, int *returnSize, char *buf, int idx, int *visited) {
    /* 满足条件进行赋值 */
    if (idx == len) {
        res[*returnSize] = (char*)malloc(sizeof(char) * (len + 1));
        strcpy(res[*returnSize], buf);
        (*returnSize)++;
        return;
    }
    int i;
    /* 回溯算法 */
    for (i = 0; i < len; i++) {
        if (visited[i] == 0) {
            buf[idx] = S[i];
            visited[i] = 1;
            dfs(S, len, res, returnSize, buf, idx + 1, visited);
            visited[i] = 0;
        }
    }
}

char** permutation(char* S, int* returnSize){
    int len = strlen(S);
    int n = 1;
    int i;
    /* 计算输出长度 */
    for (i = 1; i <= len; i++) {
        n *= i;
    }
    char **res   = (char**)malloc(sizeof(char*) * n);
    char *buf    = (char*)malloc(sizeof(char) * (len + 1));
    int *visited = (int*)malloc(sizeof(int) * len);
    memset(visited, 0, sizeof(int) * len);
    buf[len] = '\0';
    *returnSize = 0;
    dfs(S, len, res, returnSize, buf, 0, visited);
    return res;
}

int main(){
    char name[10];
    int returnsize=0;
    int i = 0;
    printf("Input string: ");
    scanf("%s",name);
    char **res2=permutation(name,&returnsize);
    while (*res2)
    {
       printf("%s\n",*res2);
        res2=res2+1;
    }
}