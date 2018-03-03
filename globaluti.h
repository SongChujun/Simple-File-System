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
//const int CMDLSIZE=100;
#define CMDLSIZE 100
//const int FILESIZE=1024*1024;
//const int MAXCHILDNUM=50;
#define FILESIZE 1024*1024
#define MAXCHILDNUM 10
//const int MAXFILRNUM=1000;
#define MAXFILENUM 1000
//const int blocksize=512;
#define blocksize 512

struct  TreeNode
{
    int type;//the type of the node,0 stands for file and 1 stands for directory
    struct TreeNode* father;//pointer to the father
    struct TreeNode* childlist[MAXCHILDNUM];
    int ChildNum;//the number of children;
    char name[16];//the name of the node;
    int inodenum;//the number of the inode;
    int filedescriptor;
    int statue;
};
void FuncCd(const char*);
void FuncMkdir(const char*);
void FuncDir(const char*);
void FuncTouch(const char*);
void FuncRm(char*,char*);
void FuncCreat(const char*);
int FuncOpen(const char*,int mode);
void FuncClose(const char*);
void FuncRead(const char*);
void FuncWrite(const char*);
void FuncTouch(const char*);
void creat(char *);
int open(char *, int);
int close(int);
int read(int,void*,int);
int write(int ,void *,int);
int seek(int,int,int);
int fremove(char *);
int dirdelete(struct TreeNode**);
int filedelete(struct TreeNode** );

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
bool freenode[MAXFILENUM];
int freeinodenum;
int computeinodenum();
bool freesystemopenfilesheet[100];
int freesheetnum;
int computefreesheetnum();
struct systemopenfilesheet
{
    int rwflag;
    int refcount;
    struct activeinode* ptrtoactiveinode;
    struct  TreeNode* ptrtotreenode;
    int offset;
};
struct systemopenfilesheet* u_ofile[100];
void formalizecmdline(char *);
void chararrayclear(char *, int);
void intarrayclear(int * intarray,int len);
int* allocblocks(int );
void freeblocks(int *);
struct freeblock
{
    int num;
    int s_free[127];
};
struct freeblock immemblock;
void init();
int calintarraylen(int *intarray);