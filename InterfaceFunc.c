//
// Created by song on 3/1/18.
//
#include "globaluti.h"
void FuncCd(char * cmdline)
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
            for(int k=0;k<10;k++)
            {
                if((curnode->childlist[k]!=NULL)&&(strcmp(curnode->childlist[k]->name,tmpname)==0))
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
            for(int k=0;k<10;k++)
            {
                if((curnode->childlist[k]!=NULL)&&(strcmp(curnode->childlist[k]->name,tmpname)==0))
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
void FuncMkdir(char *cmdline)
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
                for(int i=0;i<10;i++)
                {
                    newnode->childlist[i]=NULL;
                }
                for(int i=0;i<10;i++)
                {
                    if(curnode->childlist[i]==NULL)
                    {
                        curnode->childlist[i]=newnode;
                        break;
                    }
                }
                curnode->ChildNum++;
                return ;
            }
            i=j;
            flag=0;
            for(int k=0;k<10;k++)
            {
                if((curnode->childlist[k]!=NULL)&&(strcmp(curnode->childlist[k]->name,tmpname)==0))
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
                for(int i=0;i<10;i++)
                {
                    newnode->childlist[i]=NULL;
                }
                for(int i=0;i<10;i++)
                {
                    if(curnode->childlist[i]==NULL)
                    {
                        curnode->childlist[i]=newnode;
                        break;
                    }
                }
                curnode->ChildNum++;
                return ;
            }
            i=j;
            flag=0;
            for(int k=0;k<10;k++)
            {
                if((curnode->childlist[k]!=NULL)&&(strcmp(curnode->childlist[k]->name,tmpname)==0))
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
void FuncDir(char* cmdline)
{
    if(globalcurnode->ChildNum==0)
    {
        printf("Empty directory\n");
        return;
    }
    printf("name  type\n");
    for(int i=0;i<10;i++)
    {
        if(globalcurnode->childlist[i]!=NULL)
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
}
void FuncTouch(char* cmdline)
{
    mycreat(cmdline);
}
void FuncRm(char* mode, char* path)
{
    formalizecmdline(path);
    if(strcmp(mode,"-r")==0)
    {
        if(path[0]=='/')
        {
            char dirname[16];
            int begin=0;
            for(begin=strlen(path)-3;((path[begin]!='/')&&(begin>0)&&(path[begin]!=' '));begin--);
            int cur=0;
            int recordbegin=begin;
            begin++;
            for(;begin<strlen(path)-2;begin++)
            {
                dirname[cur++]=path[begin];
            }

            struct TreeNode* curnode=root;
            int i=0;
            int flag=0;
            while(1)
            {
                char tmpname[16];
                chararrayclear(tmpname,16);
                int j;
                for(j=i+1;;j++)
                {
                    if(path[j]=='$')
                    {
                        struct TreeNode* fathernode=curnode->father;
                        for(int k=0;k<10;k++)
                        {
                            if((fathernode->childlist[k]!=NULL)&&(strcmp(fathernode->childlist[k]->name,curnode->name)==0))
                            {
                                fathernode->childlist[k]=NULL;
                                fathernode->ChildNum--;
                                dirdelete(&curnode);
                                return;
                            }
                        }
                        return;
                    }
                    if(path[j]=='/')
                    {
                        break;
                    }
                    tmpname[j-i-1]=path[j];
                }
                if((strcmp(tmpname,dirname)==0)&&(recordbegin==i))
                {
                    for(int k=0;k<10;k++)
                    {
                        if((curnode->childlist[k]!=NULL)&&(strcmp(curnode->childlist[k]->name,tmpname)==0))
                        {
                            flag=1;
                            curnode->ChildNum--;
                            curnode=curnode->childlist[k];
                            curnode->father->childlist[k]=NULL;
                            break;
                        }
                    }
                    dirdelete(&curnode);
                    return;
                }
                i=j;
                flag=0;
                for(int k=0;k<10;k++)
                {
                    if((curnode->childlist[k]!=NULL)&&(strcmp(curnode->childlist[k]->name,tmpname)==0))
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
            int i=-1;
            int flag=0;
            while(1)
            {
                char tmpname[16];
                chararrayclear(tmpname,16);
                int j;
                for(j=i+1;;j++)
                {
                    if(path[j]=='$')
                    {
                        struct TreeNode* fathernode=curnode->father;
                        for(int k=0;k<10;k++)
                        {
                            if((fathernode->childlist[k]!=NULL)&&(strcmp(fathernode->childlist[k]->name,curnode->name)==0))
                            {
                                fathernode->childlist[k]=NULL;
                                fathernode->ChildNum--;
                                dirdelete(&curnode);
                                return;
                            }
                        }
                        return;
                    }
                    if(path[j]=='/')
                    {
                        break;
                    }
                    tmpname[j-i-1]=path[j];
                }
//            strcat(curpath,tmpname);
//            strcat(curpath,"/");
                i=j;
                flag=0;
                for(int k=0;k<10;k++)
                {
                    if((curnode->childlist[k]!=NULL)&&(strcmp(curnode->childlist[k]->name,tmpname)==0))
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
    else
    {
        if(path[0]=='/')
        {
            struct TreeNode* curnode=root;
            int i=0;
            int flag=0;
            while(1)
            {
                char tmpname[16];
                chararrayclear(tmpname,16);
                int j;
                for(j=i+1;;j++)
                {
                    if(path[j]=='$')
                    {
                        struct TreeNode* fathernode=curnode->father;
                        for(int k=0;k<10;k++)
                        {
                            if(strcmp(fathernode->childlist[k]->name,curnode->name)==0)
                            {
                                fathernode->childlist[k]=NULL;
                                fathernode->ChildNum--;
                                filedelete(&curnode);
                                return;
                            }
                        }
                    }
                    if(path[j]=='/')
                    {
                        break;
                    }
                    tmpname[j-i-1]=path[j];
                }
                i=j;
                flag=0;
                for(int k=0;k<10;k++)
                {
                    if((curnode->childlist[k]!=NULL)&&(strcmp(curnode->childlist[k]->name,tmpname)==0))
                    {
                        flag=1;
                        curnode=curnode->childlist[k];
//                        if(curnode->childlist[k]->type==0)
//                        {
//                            printf("Invalid Path\n");
//                            return ;
//                        }
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
            int i=-1;
            int flag=0;
            while(1)
            {
                char tmpname[16];
                chararrayclear(tmpname,16);
                int j;
                for(j=i+1;;j++)
                {
                    if(path[j]=='$')
                    {
                        struct TreeNode* fathernode=curnode->father;
                        for(int k=0;k<10;k++)
                        {
                            if((fathernode->childlist[k]!=NULL)&&(strcmp(fathernode->childlist[k]->name,curnode->name)==0))
                            {
                                fathernode->childlist[k]=NULL;
                                fathernode->ChildNum--;
                                filedelete(&curnode);
                                return;
                            }
                        }
                    }
                    if(path[j]=='/')
                    {
                        break;
                    }
                    tmpname[j-i-1]=path[j];
                }
                i=j;
                flag=0;
                for(int k=0;k<10;k++)
                {
                    if((curnode->childlist[k]!=NULL)&&(strcmp(curnode->childlist[k]->name,tmpname)==0))
                    {
                        flag=1;
                        curnode=curnode->childlist[k];
//                        if(curnode->type==0)
//                        {
//                            printf("Invalid Path\n");
//                            return ;
//                        }
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
}
int FuncVim(char*path)
{
    FILE* buffp;
    int fd=myopen(path,1);
    if(fd==-1)
    {
        printf("this is write\n");
        mycreat(path);
        fd=myopen(path,1);
//        char* args[]={"vim","/home/song/Desktop/File System/buffile",NULL};
//        int status;
//        if(!fork())
//        {
//            execvp("vim",args);
//        }
//        wait(&status);
//        char buf[4000];
//        FILE* buffp=fopen("/home/song/Desktop/File System/buffile","r+b");
//        if(buffp==NULL)
//        {
//            printf("Open File failed\n");
//        }
//        int readnum=fread(buf,sizeof(char),4000,buffp);
//        printf("readnum=%d",readnum);
//        fclose(buffp);
        char buf[1000];
        int num=scanf("%s",buf);
        for(int i=0;i<strlen(buf);i++)
        {
           printf("%c",buf[i]);
        }
        mywrite(fd,buf,strlen(buf));
    }
    else
    {
        printf("this is read\n");
        char buf[1000];
        for(int i=0;i<1000;i++)
        {
            buf[i]='\0';
        }
        printf("\n");
        int readnum=myread(fd,buf,u_ofile[fd]->ptrtoactiveinode->length);
//        FILE* buffp=fopen("/home/song/Desktop/File System/buffile","wb");
//        if(buffp==NULL)
//        {
//            printf("cannot open buffp");
//            return 0;
//        }
//        int writenum=fwrite(buf,sizeof(char),readnum,buffp);
//        fclose(buffp);
//        buffp=fopen("/home/song/Desktop/File System/buffile","rb");
//        char* args[]={"vim","/home/song/Desktop/File System/buffile",NULL};
//        int status;
//        if(!fork())
//        {
//            execvp("vim",args);
//        }
//        wait(&status);
//        fclose(buffp);
        for(int i=0;i<u_ofile[fd]->ptrtoactiveinode->length;i++)
        {
            printf("%c",buf[i]);
        }
        printf("\n");
//        buffp=fopen("/home/song/Desktop/File System/buffile","r+b");
//        if(buffp==NULL)
//        {
//            printf("Open File failed\n");
//        }
//        readnum=fread(buf,sizeof(char),4000,buffp);
//        printf("readnum=%d",readnum);
//        fclose(buffp);
//        mywrite(fd,buf,readnum);
    }
    myclose(fd);
    buffp=fopen("/home/song/Desktop/File System/buffile","w");
    fclose(buffp);
    return 1;
}
