#include"define.h"
typedef enum CMD
{
    CMD_MKDIR  = 1,  //1
    CMD_REMOVE    ,  //2
    CMD_COPY      ,  //3
    CMD_MOVE      ,  //4
    CMD_FIND      ,  //5
    CMD_N            //6
}cmd;

extern void init(int n);
extern void cmd_mkdir(char path[PATH_MAX_LEN+1], char name[NAME_MAX_LEN+1]);
extern void cmd_rm(char path[PATH_MAX_LEN+1]);
extern void cmd_cp(char src_path[PATH_MAX_LEN+1], char dst_path[PATH_MAX_LEN+1]);
extern void cmd_mv(char src_path[PATH_MAX_LEN+1], char dst_path[PATH_MAX_LEN+1]);
extern int  cmd_find(char path[PATH_MAX_LEN+1]);


static bool run(int m)
{
    bool is_accepted = true;
    int  cmd;
    int  ret;
    int  answer;
    char name[NAME_MAX_LEN+1];
    char path1[PATH_MAX_LEN+1], path2[PATH_MAX_LEN+1];

    while(m--)
    {
        scanf("%d",&cmd);

        switch (cmd)
        {
        case CMD_MKDIR:
            scanf("%s%s",&path1,&name);
            cmd_mkdir(path1,name);
            break;

        case CMD_REMOVE:
            scanf("%s",&path1);
            cmd_rm(path1);
            break;

        case CMD_COPY:
            scanf("%s%s",&path1,&path2);
            cmd_cp(path1,path2);
            break;

        case CMD_MOVE:
            scanf("%s%s",&path1,&path2);
            cmd_mv(path1,path2);
            break;

        case CMD_FIND:
            scanf("%s",&path1);
            ret = cmd_find(path1);
            
            scanf("%d",&answer);

            is_accepted &= (ret == answer);

            break;
        default:
            CONS_OUT("[#ERROR] [CMD is not correct:%d]\n\n",cmd);
            CONS_OUT("Enter CMD index from following\n",cmd);
            CONS_OUT("1: Make   Directory\n",cmd);
            CONS_OUT("2: Remove Directory\n",cmd);
            CONS_OUT("3: Copy   Directory\n",cmd);
            CONS_OUT("4: Remove Directory\n",cmd);
            CONS_OUT("5: Find   Directory\n",cmd);
            break;
        }
    }

    return is_accepted;
}

int main()
{
    int test_case, T;
    int n, m;

    freopen("./input/test_cases_input.txt","r",stdin);

    setbuf(stdout,NULL);

    scanf("%d",&T);

    for(test_case = 1; test_case<=T; test_case++)
    {
        scanf("%d%d",&n,&m);
      
        init(n);

        if(run(m))
        {
            CONS_OUT("#Test Case:%d Passed\n",test_case);
        }
        else
        {
            CONS_OUT("#Test Case:%d Fail\n",test_case);
        }
    }

    return 0;
}