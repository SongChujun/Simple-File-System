//
// Created by song on 3/1/18.
//
#include "globaluti.h"
int computeinodenum()
{
    for(int i=0;i<1000;i++)
    {
        if(!freenode[i])
        {
            return i;
        }
    }
    return -1;
}
int computefreesheetnum()
{
    for(int i=0;i<100;i++)
    {
        if(!freesystemopenfilesheet[i])
        {
            return i;
            freesystemopenfilesheet[i]=1;
        }
    }
    return -1;
}
void formalizecmdline(char *cmdline)
{
    int len=strlen(cmdline);
    if(cmdline[len-1]!='/')
    {
        strcat(cmdline,"/$");
    }
}
void chararrayclear(char * chararray,int len)
{
    for(int i=0;i<len;i++)
    {
        chararray[i]='\0';
    }
}
void intarrayclear(int * intarray,int len)
{
    for(int i=0;i<len;i++)
    {
        intarray[i]=-1;
    }
}
int calintarraylen(int *intarray)
{
    int i=0;
    for(i=0;intarray[i]!=-1;i++);
    return i;
}
int boolarrayclear(bool* boolarray,int len,int val)
{
    for(int i=0;i<len;i++)
    {
        boolarray[i]=val;
    }
}