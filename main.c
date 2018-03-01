#include <stdio.h>
#include <stdlib.h>
#include "globaluti.h"

int main()
{
    fp=fopen("/home/song/Desktop/File System/DiskSpace","a+b");
    fseek(fp,SEEK_SET,FILESIZE*512);
    fputc(0,fp);
    if(fp==NULL)
    {
        printf("Open file failed!\n");
        return 0;
    }
    char cmdline[CMDLSIZE];
    while(scanf("%s",cmdline)!=EOF)
    {
        if ((cmdline[0]=='c')&&(cmdline[1]=='d'))
        {
            FuncCd(cmdline);
        }
        else if ((cmdline[0]=='m')&&(cmdline[1]=='k'))
        {
            FuncMkdir(cmdline);
        }
        else if ((cmdline[0]=='d')&&(cmdline[1]=='i'))
        {
            FuncDir(cmdline);
        }
        else if ((cmdline[0]=='r')&&(cmdline[1]=='m'))
        {
            FuncRm(cmdline);
        }
        else if ((cmdline[0]=='c')&&(cmdline[1]=='r'))
        {
            FuncCreat(cmdline);
        }
        else if ((cmdline[0]=='o')&&(cmdline[1]=='p'))
        {
            FuncOpen(cmdline);
        }
        else if ((cmdline[0]=='c')&&(cmdline[1]=='l'))
        {
            FuncClose(cmdline);
        }
        else
        {
            printf("Unrecognized Command Line!\n");
            continue;
        }
    }
}