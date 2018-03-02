//
// Created by song on 3/1/18.
//
#include "globaluti.h"
void FuncCd(const char * cmdline)
{
    char curpath[128];
    chararrayclear(curpath,128);
    if(cmdline[2]!=' ')
    {
        printf("Unrecognized Command Line!\n");
        return;
    }
    else if(cmdline[3]=='/')
    {
        struct TreeNode* curnode=root;
        int i=3;
        int flag=0;
        while(1)
        {
            char tmpname[16];
            chararrayclear(tmpname,16);
            int j;
            for(j=i+1;;j++)
            {
                if(cmdline[j]=='$')
                {
                    globalcurnode=curnode;
                    strcpy(globalcurpath,cmdline+3);
                    int len=strlen(globalcurpath)-1;
                    globalcurpath[len]='\0';
                    globalcurpath[len-1]='\0';
                    return;
                }
                if(cmdline[j]=='/')
                {
                    break;
                }
                tmpname[j-i-1]=cmdline[j];
            }
//            strcat(curpath,"/");
//            strcat(curpath,tmpname);
            i=j;
            flag=0;
            for(int k=0;k<curnode->ChildNum;k++)
            {
                if(strcmp(curnode->childlist[k]->name,tmpname)==0)
                {
                    flag=1;
                    curnode=curnode->childlist[k];
                    if(curnode->type==0)
                    {
                        printf("Invalid Path\n");
                        return ;
                    }
                    break;
                }
            }
            if(flag==0)
            {
                printf("The file doesn't exist!\n");
                return;
            }
        }
    }
    else if(cmdline[3]!='.')
    {
        struct TreeNode* curnode=globalcurnode;
        int i=2;
        int flag=0;
        while(1)
        {
            char tmpname[16];
            chararrayclear(tmpname,16);
            int j;
            for(j=i+1;;j++)
            {
                if(cmdline[j]=='$')
                {
                    globalcurnode=curnode;
                    if(strlen(globalcurpath)!=1)
                        strcat(globalcurpath,"/");
                    strcat(globalcurpath,cmdline+3);
                    int len=strlen(globalcurpath)-1;
                    globalcurpath[len]='\0';
                    globalcurpath[len-1]='\0';
//                    printf("%s",globalcurpath);
                    return;
                }
                if(cmdline[j]=='/')
                {
                    break;
                }
                tmpname[j-i-1]=cmdline[j];
            }
//            strcat(curpath,tmpname);
//            strcat(curpath,"/");
            i=j;
            flag=0;
            for(int k=0;k<curnode->ChildNum;k++)
            {
                if(strcmp(curnode->childlist[k]->name,tmpname)==0)
                {
                    flag=1;
                    curnode=curnode->childlist[k];
                    if(curnode->type==0)
                    {
                        printf("Invalid Path\n");
                        return ;
                    }
                    break;
                }
            }
            if(flag==0)
            {
                printf("The file doesn't exist!\n");
                return;
            }
        }
    }
    else
    {
        if(globalcurnode!=root)
        {
            globalcurnode=globalcurnode->father;
            int i;
            for(i=strlen(globalcurpath)-1;globalcurpath[i]!='/';i--)
            {
                globalcurpath[i]='\0';
            }
            if(strlen(globalcurpath)!=1)
            {
                globalcurpath[i]='\0';
            }
        }
    }
}
void FuncMkdir(const char *cmdline)
{
    char dirname[16];
    int begin=0;
    for(begin=strlen(cmdline)-3;((cmdline[begin]!='/')&&(begin>0)&&(cmdline[begin]!=' '));begin--);
    int cur=0;
    int recordbegin=begin;
    begin++;
    for(;begin<strlen(cmdline)-2;begin++)
    {
        dirname[cur++]=cmdline[begin];
    }
    if(cmdline[6]=='/')
    {
        struct TreeNode* curnode=root;
        int i=6;
        int flag=0;
        while(1)
        {
            char tmpname[16];
            chararrayclear(tmpname,16);
            int j;
            for(j=i+1;;j++)
            {
                if(cmdline[j]=='$')
                {
                    return;
                }
                if(cmdline[j]=='/')
                {
                    break;
                }
                tmpname[j-i-1]=cmdline[j];
            }
            if((strcmp(tmpname,dirname)==0)&&(recordbegin==i))
            {
                struct TreeNode* newnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
                strcpy(newnode->name,dirname);
                newnode->father=curnode;
                newnode->type=1;
                newnode->ChildNum=0;
                curnode->childlist[(curnode->ChildNum)++]=newnode;
                return ;
            }
            i=j;
            flag=0;
            for(int k=0;k<curnode->ChildNum;k++)
            {
                if(strcmp(curnode->childlist[k]->name,tmpname)==0)
                {
                    flag=1;
                    curnode=curnode->childlist[k];
                    if(curnode->type==0)
                    {
                        printf("Invalid Path\n");
                        return ;
                    }
                    break;
                }
            }
            if(flag==0)
            {
                printf("The file doesn't exist!\n");
                return;
            }
        }
    }
    else
    {
        struct TreeNode* curnode=globalcurnode;
        int i=5;
        int flag=0;
        while(1)
        {
            char tmpname[16];
            chararrayclear(tmpname,16);
            int j;
            for(j=i+1;;j++)
            {
                if(cmdline[j]=='$')
                {
                    return;
                }
                if(cmdline[j]=='/')
                {
                    break;
                }
                tmpname[j-i-1]=cmdline[j];
            }
            if((strcmp(tmpname,dirname)==0)&&(recordbegin==i))
            {
                struct TreeNode* newnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
                strcpy(newnode->name,dirname);
                newnode->father=curnode;
                newnode->type=1;
                newnode->ChildNum=0;
                curnode->childlist[(curnode->ChildNum)++]=newnode;
                return ;
            }
            i=j;
            flag=0;
            for(int k=0;k<curnode->ChildNum;k++)
            {
                if(strcmp(curnode->childlist[k]->name,tmpname)==0)
                {
                    flag=1;
                    curnode=curnode->childlist[k];
                    if(curnode->type==0)
                    {
                        printf("Invalid Path\n");
                        return ;
                    }
                    break;
                }
            }
            if(flag==0)
            {
                printf("The file doesn't exist!\n");
                return;
            }
        }
    }
}
void FuncDir(const char* cmdline)
{
    if(globalcurnode->ChildNum==0)
    {
        printf("Empty Directory!\n");
        return ;
    }
    struct TreeNode* node=globalcurnode->childlist[0];
    printf("name  type\n");
    for(int i=0;i<globalcurnode->ChildNum;i++)
    {
        printf("%s   ",globalcurnode->childlist[i]->name);
        if(globalcurnode->childlist[i]->type==0)
        {
            printf("file\n");
        }
        else
        {
            printf("directory\n");
        }
    }
}
void FuncTouch(const char* cmdline)
{

}
void FuncRm(const char* cmdline)
{

}
