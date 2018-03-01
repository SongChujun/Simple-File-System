//
// Created by song on 3/1/18.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef FILE_SYSTEM_GLOBALUTI_H
#define FILE_SYSTEM_GLOBALUTI_H

#endif //FILE_SYSTEM_GLOBALUTI_H
FILE *fp;//file pointer of the whole file
const int CMDLSIZE=100;
const int FILESIZE=1024*1024;
const int MAXCHILDNUM=50;
const int MAXFILRNUM=1000;
const int blocksize=512;
void FuncCd(const char*);
void FuncMkdir(const char*);
void FuncDir(const char*);
void FuncTouch(const char*);
void FuncRm(const char*);
void FuncCreat(const char*);
void FuncOpen(const char*);
void FuncClose(const char*);
void FuncRead(const char*);
void FuncWrite(const char*);
void creat(const char *);
int open(const char *);
void close(int);
int read(int,char *,int);
int write(int ,char*,int);
struct  TreeNode
{
    int type;//the type of the node,0 stands for file and 1 stands for directory
    struct TreeNode* father;//pointer to the father
    struct TreeNode* chilelist[MAXCHILDNUM];
    int ChildNum;//the number of children;
    char[16] name;//the name of the node;
    int inodenum;//the number of the inode;
};
struct TreeNode *root;
struct TreeNode *globalcurnode;
char globalcurpath[128];
struct inode
{
    char owner[16];
    char group[16];
    int type;
    char permission[11];
    char lastreadtime[20];
    char lastwritetime[20];
    char nodelastchangetime[20];
    int length;//measured in bytes
    int storetype;
    int i_addr[8];
};
struct activeinode
{
    int activeinodestatue;
    int devicenum;
    int inodenum;
    int refcount;
    int ownerid;
    int type;
    char permission[11];
    int linknum;
    int length;
    int i_addr[8];
};
bool freenode[MAXFILRNUM];
int freeinodenum;
int computeinodenum();
struct systemopenfilesheet
{
    int rwflag;
    int refcount;
    struct activeinode* ptrtoactiveinode;
    int offset;
};
struct systemopenfilesheet u_ofile[100];
