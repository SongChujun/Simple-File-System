#include <stdio.h>
#include <stdlib.h>
#include "globaluti.h"

int main(int argc,char* argv[])
{
    if(argc>1)
    {
        fp=fopen("/home/song/Desktop/File System/DiskSpace","r+b");
        if(fp==NULL)
        {
            printf("File open failed\n");
            return 0;
        }
        struct TreeNode* curnode;
        struct TreeNode *tmpnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
        root=(struct TreeNode*)malloc(sizeof(struct TreeNode));
        strcpy(root->name,"/");
        root->ChildNum=0;
        root->father=NULL;
        for(int i=0;i<10;i++)
        {
            root->childlist[i]=NULL;
        }
        fseek(fp,0,SEEK_SET);
        int num=-2;
        fread(&num,sizeof(int),1,fp);
        if(num<1)
        {
            int k=0;
            for(int i=0;i<10;i++)
            {
                fread(tmpnode,sizeof(struct TreeNode),1,fp);
                if(strcmp(tmpnode->name,"$")!=0)
                {
                    TreeNodeclear(&tmpnode);
                    root->childlist[k++]=tmpnode;
                    tmpnode->father=root;
                    tmpnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
                }
            }
            root->ChildNum=k;
            for(int i=0;i<10;i++)
            {
                curnode=root->childlist[i];
                fread(&num,sizeof(int),1,fp);
                if(num<1)
                {
                    for(int j=0;i<10;i++)
                    {
                        fread(tmpnode,sizeof(struct TreeNode),1,fp);
                    }
                }
                else
                {
                    int k=0;
                    for(int j=0;i<10;i++)
                    {
                        fread(tmpnode,sizeof(struct TreeNode),1,fp);
                        if(strcmp(tmpnode->name,"$")!=0)
                        {
                            TreeNodeclear(&tmpnode);
                            curnode->childlist[k++]=tmpnode;
                            tmpnode->father=curnode;
                            tmpnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
                        }
                    }
                    curnode->ChildNum=k;
                }
            }
        }
        struct TreeNode* nullnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
        strcpy(nullnode->name,"$");
        num=-1;
        fseek(fp,0,SEEK_SET);
        for(int i=0;i<200;i++)
        {
            fwrite(&num,sizeof(int),1,fp);
            fwrite(nullnode,sizeof(struct TreeNode),1,fp);
        }
        fseek(fp,10*512,SEEK_SET);
        fread(&freenode,sizeof(bool),1000,fp);
        fread(&immemblock,sizeof(struct freeblock),1,fp);
        globalcurnode=root;
        strcpy(root->name,"/");
        root->father=NULL;
        strcpy(globalcurpath,"/");
    }
    else
    {

        fp=fopen("/home/song/Desktop/File System/DiskSpace","w");
        fclose(fp);
        fp=fopen("/home/song/Desktop/File System/DiskSpace","r+b");
        if(fp==NULL)
        {
            printf("file open failed\n");
            return 0;
        }
        boolarrayclear(freenode,1000,0);
        fseek(fp,SEEK_SET,FILESIZE*512);
        fputc('0',fp);
        init();
        root=(struct TreeNode*)malloc(sizeof(struct TreeNode));
        globalcurnode=root;
        strcpy(root->name,"/");
        root->ChildNum=0;
        root->father=NULL;
        for(int i=0;i<10;i++)
        {
            root->childlist[i]=NULL;
        }
        strcpy(globalcurpath,"/");
    }
    for(int i=0;i<100;i++)
    {
        freesystemopenfilesheet[i]=0;
    }
    char cmdline[CMDLSIZE];
    printf("root@song-Vostro-14-5480:%s$",globalcurpath);
    while(scanf("%s",cmdline)!=EOF)
    {
        if ((cmdline[0]=='c')&&(cmdline[1]=='d'))
        {
            getchar();
            char tmp[100];
            chararrayclear(tmp,100);
            scanf("%s",tmp);
            strcat(cmdline," ");
            strcat(cmdline,tmp);
            formalizecmdline(cmdline);
            FuncCd(cmdline);
        }
        else if ((cmdline[0]=='m')&&(cmdline[1]=='k'))
        {
            getchar();
            char tmp[100];
            scanf("%s",tmp);
            strcat(cmdline," ");
            strcat(cmdline,tmp);
            formalizecmdline(cmdline);
            FuncMkdir(cmdline);
        }
        else if ((cmdline[0]=='d')&&(cmdline[1]=='i'))
        {
            getchar();
            FuncDir(cmdline);
        }
        else if ((cmdline[0]=='r')&&(cmdline[1]=='m'))
        {
            getchar();
            char mode[100];
            scanf("%s",mode);
            getchar();
            if(strcmp(mode,"-r")!=0)
            {
                FuncRm(" ",mode);
            }
            else
            {
                char path[100];
                scanf("%s",path);
                FuncRm(mode,path);
            }
        }
        else if ((cmdline[0]=='c')&&(cmdline[1]=='r'))
        {
//            FuncCreat(cmdline);
        }
        else if ((cmdline[0]=='o')&&(cmdline[1]=='p'))
        {
//            FuncOpen(cmdline);
        }
        else if ((cmdline[0]=='c')&&(cmdline[1]=='l'))
        {
//            FuncClose(cmdline);
        }
        else if((cmdline[0]=='t')&&(cmdline[1]=='o'))
        {
            getchar();
            char tmp[100];
            tmp[0]=' ';
            scanf("%s",tmp+1);
//            strcat(cmdline," ");
            formalizecmdline(tmp);
            FuncTouch(tmp);
        }
        else if((cmdline[0]=='v')&&(cmdline[1]=='i'))
        {
            getchar();
            char path[100];
            path[0]=' ';
            scanf("%s",path+1);
            formalizecmdline(path);
            FuncVim(path);
        }
        else if(cmdline[0]=='q')
        {
            struct TreeNode* curnode=root;
            struct TreeNode *tmpnode;
            struct TreeNode* nullnode=(struct TreeNode*)malloc(sizeof(struct TreeNode));
            strcpy(nullnode->name,"$");
            fseek(fp,0,SEEK_SET);
            int num=root->ChildNum;
            fwrite(&num, sizeof(int),1,fp);
            for(int i=0;i<10;i++)
            {
                tmpnode=root->childlist[i];
                if(tmpnode!=NULL)
                {
                    fwrite(tmpnode,sizeof(struct TreeNode),1,fp);
                }
                else
                {
                    fwrite(nullnode,sizeof(struct TreeNode),1,fp);
                }
            }
            for(int i=0;i<10;i++)
            {
                curnode=root->childlist[i];
                if(curnode==NULL)
                {
                    int num=-1;
                    fwrite(&num, sizeof(int),1,fp);
                    for(int j=0;j<10;j++)
                    {
                        fwrite(nullnode,sizeof(struct TreeNode),1,fp);
                    }
                }
                else
                {
                    int num=curnode->ChildNum;
                    fwrite(&num,sizeof(int),1,fp);
                    for(int j=0;j<10;j++)
                    {
                        if(curnode->childlist[j]!=NULL)
                        {
                            fwrite(curnode->childlist[j],sizeof(struct TreeNode),1,fp);
                        }
                        else
                        {
                            fwrite(nullnode,sizeof(struct TreeNode),1,fp);
                        }
                    }
                }
            }
            fseek(fp,10*512,SEEK_SET);
            fwrite(&freenode,sizeof(bool),1000,fp);
            fwrite(&immemblock,sizeof(struct freeblock),1,fp);
            fclose(fp);
            return 1;
        }
        else
        {
            printf("Unrecognized Command Line!\n");
//            fflush(stdin);
        }
        printf("root@song-Vostro-14-5480:%s$",globalcurpath);
        chararrayclear(cmdline,100);
    }
}