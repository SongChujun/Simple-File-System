#include "globaluti.h"

//
// Created by song on 3/1/18.
//
void FuncCreat(const char* path)
{
    char dirname[16];
    int begin=0;
    for(begin=strlen(path)-1;((path[begin]!='/')&&(begin>0));begin--);
    int cur=0;
    int recordbegin=begin;
    begin++;
    for(;begin<strlen(path)-2;begin++)
    {
        dirname[cur++]=path[begin];
    }
    struct TreeNode* curnode=root;
    int i=1;
    int flag=0;
    while(1)
    {
        char tmpname[16];
        int j;
        for(j=i+1;;j++)
        {
            if(path[j]=='$')
            {
                return;
            }
            if(path[j]=='/')
            {
                break;
            }
            tmpname[j-i-1]=path[i];
        }
        i=j;
        flag=0;
        if((strcmp(tmpname,dirname)==0)&&(recordbegin==i))
        {
            struct TreeNode* newnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
            strcpy(newnode->name,dirname);
            newnode->father=curnode;
            newnode->type=0;
            newnode->ChildNum=0;
            curnode->childlist[(curnode->ChildNum)++]=newnode;
            freeinodenum=computeinodenum();
            curnode->inodenum=freeinodenum;
            freenode[freeinodenum]=1;
            struct inode newinode;
            newinode.length=0;
                                                                                                        
        }
        for(int k=0;k<curnode->ChildNum;k++)
        {
            if(strcmp(curnode->name,tmpname)==0)
            {
                flag=1;
                curnode=curnode->childlist[curnode->ChildNum];
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
int FuncOpen(const char* path)
{
    char filename[16];
    int begin=0;
    for(begin=strlen(path)-1;((path[begin]!='/')&&(begin>0));begin--);
    int cur=0;
    int recordbegin=begin;
    begin++;
    for(;begin<strlen(path)-2;begin++)
    {
        filename[cur++]=path[begin];
    }
    struct TreeNode* curnode=root;
    int i=1;
    int flag=0;
    while(1)
    {
        char tmpname[16];
        int j;
        for(j=i+1;;j++)
        {
            if(path[j]=='$')
            {

            }
            if(path[j]=='/')
            {
                break;
            }
            tmpname[j-i-1]=path[i];
        }
        i=j;
        flag=0;
        if((strcmp(tmpname,filename)==0)&&(recordbegin==i))
        {
            struct TreeNode* newnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
            strcpy(newnode->name,filename);
            newnode->father=curnode;
            newnode->type=0;
            newnode->ChildNum=0;
            curnode->childlist[(curnode->ChildNum)++]=newnode;

            freeinodenum=computeinodenum();
            curnode->inodenum=freeinodenum;
            freenode[freeinodenum]=1;

            struct inode newinode;
            newinode.length=0;

            struct activeinode* actvinode=(struct activeinode*)malloc(sizeof(actvinode));
            actvinode->length=0;
            freesystemopenfilesheet[computefreesheetnum()]=1;
            u_ofile[computefreesheetnum()]=(struct systemopenfilesheet*)malloc(sizeof(struct systemopenfilesheet));
            u_ofile[computefreesheetnum()]->offset=0;
            u_ofile[computefreesheetnum()]->ptrtoactiveinode=actvinode;
            u_ofile[computefreesheetnum()]->refcount=1;
        }
        for(int k=0;k<curnode->ChildNum;k++)
        {
            if(strcmp(curnode->name,tmpname)==0)
            {
                flag=1;
                curnode=curnode->childlist[curnode->ChildNum];
                if(curnode->type==0)
                {
                    printf("Invalid Path\n");
                    return -1;
                }
                break;
            }
        }
        if(flag==0)
        {
            printf("The file doesn't exist!\n");
            return -1;
        }
    }

}
void close(int fd)
{
    freesystemopenfilesheet[fd]=0;
    free(u_ofile[fd]->ptrtoactiveinode);
}