//
// Created by song on 3/2/18.
//
#include "globaluti.h"
int curcontainerblock;
struct freeblock curblock;
void init()
{
    curcontainerblock=-1;
    int i,j,k;
    j=0;
    for(int i=0;i<10000;i++)
    {
        curblock.num=127;
        curblock.s_free[0]=curcontainerblock;
        fseek(fp,SEEK_SET,(30+j)*512);
        curcontainerblock=j++;
        for(k=1;k<127;k++)
        {
            curblock.s_free[k]=j++;
        }
        fwrite(&curblock,sizeof(char),1,fp);
    }
    immemblock.num=127;
    immemblock.s_free[0]=curcontainerblock;
    for(k=1;k<127;k++)
    {
        immemblock.s_free[k]=j++;
    }
}
int* allocblocks(int n)
{
    if(n==0)
        return NULL;
    int* res=(int*)malloc(n*sizeof(int));
    int i=0;
    while(n--)
    {
        if(immemblock.num==1)
        {
            if(immemblock.s_free[0]==-1)
            {
                return NULL;
            }
            fseek(fp,SEEK_SET,30*512+immemblock.s_free[0]*512);
            fread(&immemblock,sizeof(immemblock),1,fp);
        }
        res[i++]=immemblock.s_free[--immemblock.num];
    }
    return res;
}
void freeblocks(int *blockchain)
{
    int len=calintarraylen(blockchain);
    for(int i=0;i<len;i++)
    {
        if(immemblock.num==127)
        {
            fseek(fp,SEEK_SET,(30+blockchain[i])*512);
            fwrite(&immemblock,sizeof(char),1,fp);
            immemblock.num=1;
            immemblock.s_free[0]=blockchain[i];
            i++;
        }
        immemblock.s_free[immemblock.num++]=blockchain[i++]
    }
}