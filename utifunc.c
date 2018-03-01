//
// Created by song on 3/1/18.
//
#include "globaluti.h"
int computeinodenum()
{
    for(int i=0;i<1000;i++)
    {
        if((!freenode[i])&&(freenode[i+1]))
        {
            return i+20;
        }
    }
    return -1;
}