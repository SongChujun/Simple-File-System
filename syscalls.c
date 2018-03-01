#include "globaluti.h"

//
// Created by song on 3/1/18.
//
#include "globaluti.h"
void creat(char* path)
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
            struct TreeNode* newnode=(TreeNode*)malloc(sizeof(TreeNode));
            strcpy(newnode->name,dirname);
            newnode->father=curnode;
            newnode->type=0;
            newnode->ChildNum=0;
            curnode->chilelist[(curnode->ChildNum)++]=newnode;
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
                curnode=curnode->chilelist[curnode->ChildNum];
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