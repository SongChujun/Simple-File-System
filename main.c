#include <stdio.h>
#include <stdlib.h>
#include "globaluti.h"

int main()
{
    init();
    boolarrayclear(freenode,1000,0);
    fp=fopen("/home/song/Desktop/File System/DiskSpace","a+b");
    fseek(fp,SEEK_SET,FILESIZE*512);
    fputc(0,fp);
    if(fp==NULL)
    {
        printf("Open file failed!\n");
        return 0;
    }
    root=(struct TreeNode*)malloc(sizeof(struct TreeNode));
    globalcurnode=root;
    strcpy(root->name,"/");
    root->ChildNum=0;
    root->father=NULL;
    strcpy(globalcurpath,"/");
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
        else
        {
            printf("Unrecognized Command Line!\n");
        }
        printf("root@song-Vostro-14-5480:%s$",globalcurpath);
        chararrayclear(cmdline,100);
    }
}